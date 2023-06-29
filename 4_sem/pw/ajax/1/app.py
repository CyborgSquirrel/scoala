import flask
import sqlite3
import json
import random
import contextlib


DATABASE_PATH = "data.db"


with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
    connection.executescript("""
        CREATE TABLE IF NOT EXISTS Route(
              source TEXT
            , destination TEXT
        )
    """)

    if False:
        cities = [
            "București",
            "Iași",
            "Cluj-Napoca",
            "Timișoara",
            "Constanța",
            "Craiova",
            "Brașov",
            "Galați",
            "Ploiești",
            "Oradea",
            "Brăila",
            "Arad",
            "Pitești",
            "Sibiu",
            "Bacău",
            "Târgu Mureș",
            "Baia Mare",
            "Buzău",
            "Botoșani",
            "Satu Mare",
            "Râmnicu Vâlcea",
            "Drobeta-Turnu Severin",
            "Suceava",
            "Piatra Neamț",
            "Târgu Jiu",
            "Târgoviște",
            "Focșani",
            "Bistrița",
            "Tulcea",
        ]

        routes = set()

        for _ in range(400):
            route = random.sample(cities, 2)
            routes.add(tuple(route))
    
        with connection:
            connection.executemany(
                "INSERT INTO Route (source, destination) VALUES (?, ?)",
                routes,
            )

app = flask.Flask(__name__)

@app.route("/request", methods=["POST"])
def request():
    print(flask.request.data)
    data = json.loads(flask.request.data)
    with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
        if "GetSources" in data:
            sources = list(
                connection.execute(
                    "SELECT DISTINCT source FROM Route",
                )
            )
            sources = [ source[0] for source in sources ]
            return flask.jsonify(sources)
        elif "GetDestinationsFromSource" in data:
            destinations = list(
                connection.execute(
                    "SELECT destination FROM Route WHERE source = ?",
                    (data["GetDestinationsFromSource"]["source"],),
                )
            )
            destinations = [ destination[0] for destination in destinations ]
            return flask.jsonify(destinations)
        else:
            assert False
    return None
