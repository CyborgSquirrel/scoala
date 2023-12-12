import argparse
import dataclasses
import datetime
import hashlib
import json as jsonlib
import os
import pathlib
import secrets
from http import HTTPStatus as status

import dacite
import flask
import flask_cors
import flask_jwt_extended as flask_jwt
import flask_socketio
import sqlalchemy
import sqlalchemy.orm

import db


@dataclasses.dataclass
class PostBook:
    read: bool
    title: str
    rating: int
    date_added: int
    lat: float
    lng: float


# global stuff
app = flask.Flask(__name__)
flask_cors.CORS(app)  # farewell, cors
socketio = flask_socketio.SocketIO(
    app,
    cors_allowed_origins="*",
)
socketio_sid_to_user_id = dict()


@dataclasses.dataclass
class PostUser:
    name: str
    password: str


@app.post("/user")
def post_user():
    request_user = jsonlib.loads(flask.request.data)
    try:
        request_user = dacite.from_dict(data_class=PostUser, data=request_user)
    except dacite.DaciteError:
        return ("", status.BAD_REQUEST)

    with sqlalchemy.orm.Session(engine) as session:
        password_salt = secrets.token_bytes(256//8)
        password_hash = hashlib.sha256(
            request_user.password.encode() + password_salt
        ).digest()
        
        user = db.User(
            name=request_user.name,
            password_hash=password_hash,
            password_salt=password_salt,
        )
        session.add(user)
        session.commit()

    return ("", status.OK)


@dataclasses.dataclass
class PostUserLogin:
    name: str
    password: str


@app.post("/user/login")
def post_user_login():
    request_user = jsonlib.loads(flask.request.data)
    try:
        request_user = dacite.from_dict(data_class=PostUserLogin, data=request_user)
    except dacite.DaciteError:
        return ("", status.BAD_REQUEST)

    with sqlalchemy.orm.Session(engine) as session:
        user = session.scalar(
            (sqlalchemy.select(db.User)
                .where(db.User.name.__eq__(request_user.name)))
        )

    if user is None:
        return ("", status.UNAUTHORIZED)

    password_hash = hashlib.sha256(
        request_user.password.encode() + user.password_salt
    ).digest()

    if password_hash != user.password_hash:
        return ("", status.UNAUTHORIZED)

    access_token = flask_jwt.create_access_token(identity=user.id)
    return flask.jsonify(dict(access_token=access_token, id=user.id))


@app.get("/book")
@flask_jwt.jwt_required()
def get_books():
    # offset
    offset = flask.request.args.get("offset")
    if offset is None:
        offset = 0
    else:
        try:
            offset = int(offset)
        except ValueError:
            return ("", status.BAD_REQUEST)

    # size
    size = flask.request.args.get("size")
    if size is None:
        size = 10
    else:
        try:
            size = int(size)
        except ValueError:
            return ("", status.BAD_REQUEST)
    
    # filter
    filter = flask.request.args.get("filter")

    # is_read
    is_read = flask.request.args.get("is_read")
    if is_read is not None:
        is_read = bool(int(is_read))
    
    user_id = flask_jwt.get_jwt_identity()
    with sqlalchemy.orm.Session(engine) as session:
        books_query = (
            sqlalchemy.select(db.Book)
            .where(db.Book.user_id == user_id)
            .order_by(db.Book.id)
            .offset(offset)
            .limit(size)
        )

        if filter is not None:
            books_query = books_query.where(db.Book.title.icontains(filter))

        if is_read is not None:
            books_query = books_query.where(db.Book.read == is_read)
        
        books = list(session.scalars(books_query))
    books = [book.to_jsonable() for book in books]
    return flask.jsonify(books)


@app.get("/book/image/<int:id>")
@flask_jwt.jwt_required()
def get_book_image(id: int):
    return flask.send_from_directory(str(book_image_dir), str(id))


@app.put("/book/image/<int:id>")
@flask_jwt.jwt_required()
def put_book_image(id: int):
    print(flask.request.files)
    image = flask.request.files["image"]
    image.save(book_image_dir / str(id))
    return ("", status.OK)


@app.post("/book")
@flask_jwt.jwt_required()
def post_book():
    user_id = flask_jwt.get_jwt_identity()
    request_book = jsonlib.loads(flask.request.data)

    try:
        request_book = dacite.from_dict(data_class=PostBook, data=request_book)
    except dacite.DaciteError:
        return ("", status.BAD_REQUEST)

    db_book = dataclasses.asdict(request_book)
    db_book["date_added"] = datetime.datetime.fromtimestamp(db_book["date_added"])
    db_book["user_id"] = user_id
    with sqlalchemy.orm.Session(engine) as session:
        db_book = db.Book(**db_book)
        session.add(db_book)
        session.commit()

        response_book = db_book.to_jsonable()
    
    socketio.emit("post_book", response_book, room=str(user_id))

    return flask.jsonify(dict(id=response_book["id"]))


@dataclasses.dataclass
class PutBook:
    read: bool
    title: str
    rating: int


@app.put("/book/<int:id>")
@flask_jwt.jwt_required()
def put_book(id: int):
    user_id = flask_jwt.get_jwt_identity()
    request_book = jsonlib.loads(flask.request.data)

    try:
        request_book = dacite.from_dict(data_class=PutBook, data=request_book)
    except dacite.DaciteError:
        return ("", status.BAD_REQUEST)

    with sqlalchemy.orm.Session(engine) as session:
        session.execute(
            sqlalchemy.update(db.Book)
                .filter_by(id=id)
                .values(
                    read=request_book.read,
                    title=request_book.title,
                    rating=request_book.rating,
                )
        )
        session.commit()
    
    # TODO: fix this maybe?
    # socketio.emit("put_book", response_book, room=str(user_id))

    return ("", status.OK)


@dataclasses.dataclass
class SocketioAuth:
    jwt_token: str


@socketio.on("auth")
def test_auth(message):
    sid = flask.request.sid
    try:
        message = dacite.from_dict(data_class=SocketioAuth, data=message)
    except dacite.DaciteError:
        return ("", status.BAD_REQUEST)

    jwt_decoded = flask_jwt.decode_token(message.jwt_token)
    user_id = jwt_decoded[flask_jwt.config.config.identity_claim_key]
    socketio_sid_to_user_id[sid] = user_id
    flask_socketio.join_room(str(socketio_sid_to_user_id[sid]), sid)


@socketio.on("disconnect")
def test_disconnect():
    sid = flask.request.sid
    if sid not in socketio_sid_to_user_id:
        return

    flask_socketio.leave_room(str(socketio_sid_to_user_id[sid]), sid)
    del socketio_sid_to_user_id[sid]


if __name__ == "__main__":
    data_dir = pathlib.Path("data")
    os.makedirs(data_dir, exist_ok=True)
    
    book_image_dir = data_dir / "book_image"
    os.makedirs(book_image_dir, exist_ok=True)
    
    # database stuff
    data_path = data_dir / "data.db"
    engine = sqlalchemy.create_engine(f"sqlite:///{data_path}")
    db.Base.metadata.create_all(engine)

    # cli args
    argparser = argparse.ArgumentParser()
    argparser.add_argument("config_path")
    args = argparser.parse_args()

    # config
    with open(args.config_path) as f:
        config = jsonlib.load(f)

    # jwt
    app.config["JWT_SECRET_KEY"] = config["jwt_secret_key"]
    jwt = flask_jwt.JWTManager(app)
    
    # socketio
    socketio.run(app, host="0.0.0.0", debug=True, use_reloader=False)
