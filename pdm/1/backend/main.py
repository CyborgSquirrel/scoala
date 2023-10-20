import sqlite3
import contextlib
import flask
import time
import json
import flask_socketio
from http import HTTPStatus as status


CORS_ALLOWED_ORIGINS = [
    "http://localhost:8100"
]


def get_conn():
    return contextlib.closing(sqlite3.connect("data.db"))


def make_response(response=None, status=None) -> flask.Response:
    return flask.Response(
        response,
        status,
        # headers={
        #     "Access-Control-Allow-Origin": cors_allowed_origin
        #     for cors_allowed_origin in CORS_ALLOWED_ORIGINS
        # }
        headers={
            "Access-Control-Allow-Origin": "*"
        }
    )


# flask stuff
app = flask.Flask(__name__)
socketio = flask_socketio.SocketIO(
    app,
    cors_allowed_origins="*",
)

with get_conn() as conn:
    conn.executescript("""
        CREATE TABLE IF NOT EXISTS Book(
            id INTEGER PRIMARY KEY,
            read INTEGER,
            title TEXT,
            rating INTEGER,
            date_added INTEGER
        );
    """)


@app.route("/book", methods=["GET"])
def get_books():
    with get_conn() as conn:
        cursor = conn.execute("SELECT id, title, rating, date_added, read FROM Book ORDER BY id")
        response = [
            dict(
                id=row[0],
                title=row[1],
                rating=row[2],
                date_added=row[3],
                read=bool(row[4]),
            )
            for row in cursor
        ]
    return make_response(json.dumps(response), status.OK)


@app.route("/book", methods=["POST"])
def post_book():
    request = json.loads(flask.request.data)
    if (   request is None
        or "title"      not in request or not isinstance(request["title"],      str )
        or "rating"     not in request or not isinstance(request["rating"],     int )
        or "date_added" not in request or not isinstance(request["date_added"], int )
        or "read"       not in request or not isinstance(request["read"],       bool)
    ):
        return make_response(None, status.BAD_REQUEST)

    book = request

    with get_conn() as conn:
        with conn:
            cursor = conn.execute(
                "INSERT INTO Book (title, rating, date_added, read)"
                "VALUES (?, ?, ?, ?) RETURNING id"
                ,
                (
                    book["title"],
                    book["rating"],
                    book["date_added"],
                    int(book["read"])
                ),
            )
            row = next(cursor)
            book["id"] = row[0]

    socketio.emit("post_book", book)

    return make_response(None, status.OK)


if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0")
    # app.run(host="0.0.0.0")
