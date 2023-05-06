import flask
import sqlite3
import json
import random
import contextlib


DATABASE_PATH = "data.db"


with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
    connection.executescript("""
        CREATE TABLE IF NOT EXISTS User(
              name TEXT
            , surname TEXT
            , phone TEXT
            , email TEXT
        )
    """)

    if False:
        users = [
            ("Aran"    , "Huff"        , "+40 702 046 240", "aran.huff@gmail.com"          ),
            ("Gladys"  , "Parks"       , "+40 702 046 299", "gladys.parks@gmail.com"       ),
            ("Nikita"  , "Bonner"      , "+40 702 046 500", "nikita.bonner@gmail.com"      ),
            ("Kyra"    , "Mullen"      , "+40 702 046 024", "kyra.mullen@gmail.com"        ),
            ("Liam"    , "Kane"        , "+40 702 046 880", "liam.kane@gmail.com"          ),
            ("Mikolaj" , "Farmer"      , "+40 702 046 432", "mikolaj.farmer@gmail.com"     ),
            ("Simon"   , "Carson"      , "+40 702 046 720", "simon.carson@gmail.com"       ),
            ("Haider"  , "Blankenship" , "+40 702 046 786", "haider.blankenship@gmail.com" ),
            ("Aadam"   , "Huffman"     , "+40 702 046 506", "aadam.huffman@gmail.com"      ),
            ("Amanda"  , "Jimenez"     , "+40 702 046 271", "amanda.jimenez@gmail.com"     ),
        ]

        with connection:
            connection.executemany(
                "INSERT INTO User (name, surname, phone, email) VALUES (?, ?, ?, ?)",
                users,
            )

app = flask.Flask(__name__)

@app.route("/request", methods=["POST"])
def request():
    data = json.loads(flask.request.data)
    with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
        if "GetPage" in data:
            index = data["GetPage"]["index"]

            users = list(
                connection.execute(
                    "SELECT name, surname, phone, email FROM User ORDER BY rowid LIMIT 4 OFFSET ?",
                    (index*3,),
                )
            )

            is_last = len(users) <= 3
            if len(users) > 3:
                users.pop()

            response = {
                "isLast": is_last,
                "users": [
                    {
                        "name": user[0],
                        "surname": user[1],
                        "phone": user[2],
                        "email": user[3],
                    }
                    for user in users
                ]
            }
            
            return flask.jsonify(response)
        else:
            assert False
    return None
