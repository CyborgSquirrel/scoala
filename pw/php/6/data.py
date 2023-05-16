#!/usr/bin/env python3

import sqlite3
import contextlib
import os


DATABASE_PATH = "data.db"


if os.path.exists(DATABASE_PATH):
    os.remove(DATABASE_PATH)


with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
    connection.executescript("""
        CREATE TABLE IF NOT EXISTS Comment(
              id INTEGER PRIMARY KEY ASC AUTOINCREMENT
            , name TEXT
            , content TEXT
            , approval_state INTEGER
        );
    """)
