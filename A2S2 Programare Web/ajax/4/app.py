import flask
import json
import random
import contextlib
import typing
import itertools


class InvalidMoveException(Exception):
    pass


class Game:
    def __init__(self):
        self.__cells = [
            [
                None
                for _ in range(3)
            ]
            for _ in range(3)
        ]
        self.__move_index = 0

        self.__row_count = {"X": [0] * 3, "O": [0] * 3}
        self.__col_count = {"X": [0] * 3, "O": [0] * 3}
        self.__diag1_count = {"X": 0, "O": 0}
        self.__diag2_count = {"X": 0, "O": 0}

    def __get_mover(self) -> str:
        if self.__move_index % 2 == 0:
            return "X"
        else:
            return "O"

    def get_winner(self) -> typing.Optional[str]:
        for player in ["X", "O"]:
            counts = itertools.chain(
                self.__row_count[player],
                self.__col_count[player],
                [
                    self.__diag1_count[player],
                    self.__diag2_count[player],
                ],
            )

            for count in counts:
                if count == 3:
                    return player
        
        return None
    
    def is_finished(self) -> bool:
        return self.__move_index >= 9 or self.get_winner() is not None
    
    def make_move(self, row: int, col: int):
        if (
            self.__cells[row][col] is not None
            or
            self.is_finished()
        ):
            raise InvalidMoveException()

        mover = self.__get_mover()
        self.__move_index += 1
        self.__cells[row][col] = mover

        self.__row_count[mover][row] += 1
        self.__col_count[mover][col] += 1
        if row == col:
            self.__diag1_count[mover] += 1
        if row == 2-col:
            self.__diag2_count[mover] += 1

    def get_cells(self) -> list[list[typing.Optional[str]]]:
        return self.__cells


def make_ai_move(game: Game):
    available_positions = []
    
    cells = game.get_cells()
    for row in range(3):
        for col in range(3):
            if cells[row][col] is None:
                available_positions.append((row, col))
    
    position = random.choice(available_positions)

    game.make_move(position[0], position[1])

game = None

def restart_game():
    global game
    game = Game()
    if random.random() > 0.50:
        # ai start
        make_ai_move(game)
   
app = flask.Flask(__name__)

@app.route("/request", methods=["POST"])
def request():
    data = json.loads(flask.request.data)

    if "GetGame" in data:
        response = {
            "cells": game.get_cells(),
            "winner": game.get_winner(),
        }
        
        return flask.jsonify(response)
    elif "MakeMove" in data:
        try:
            game.make_move(
                data["MakeMove"]["row"],
                data["MakeMove"]["col"],
            )
            if not game.is_finished():
                make_ai_move(game)
        except InvalidMoveException:
            pass

        response = {}

        return flask.jsonify(response)
    elif "Restart" in data:
        restart_game()

        response = {}

        return flask.jsonify(response)
    else:
        assert False

    return None
