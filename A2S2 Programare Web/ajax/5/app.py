import flask
import json
import random
import contextlib
import typing
import itertools
import pathlib
import os
import os.path


app = flask.Flask(__name__)

@app.route("/request", methods=["POST"])
def request():
    data = json.loads(flask.request.data)

    if "GetDirectory" in data:
        path = data["GetDirectory"]["path"]
        with os.scandir(path) as direntries:
            response = [
                {
                    "name": direntry.name,
                    "isDir": direntry.is_dir(),
                }
                for direntry in direntries
            ]
        
        return flask.jsonify(response)
    elif "GetFile" in data:
        path = data["GetFile"]["path"]
        with open(path) as file:
            contents = file.read()

        response = {
            "contents": contents
        }
        return flask.jsonify(response)
    else:
        assert False

    return None
