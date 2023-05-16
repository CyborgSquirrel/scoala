#!/usr/bin/env python3

import sqlite3
import contextlib
import os


DATABASE_PATH = "data.db"


if os.path.exists(DATABASE_PATH):
    os.remove(DATABASE_PATH)


with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
    connection.executescript("""
        CREATE TABLE IF NOT EXISTS Teacher(
              id INTEGER PRIMARY KEY ASC AUTOINCREMENT
            , name TEXT
            , password TEXT
        );
        CREATE TABLE IF NOT EXISTS Student(
              id INTEGER PRIMARY KEY ASC AUTOINCREMENT
            , name TEXT
        );
        CREATE TABLE IF NOT EXISTS Subject(
              id INTEGER PRIMARY KEY ASC AUTOINCREMENT
            , name TEXT
        );
        CREATE TABLE IF NOT EXISTS Grade(
              student_id INTEGER
            , subject_id INTEGER
            , value INTEGER
            , FOREIGN KEY(student_id) REFERENCES Student(id)
            , FOREIGN KEY(subject_id) REFERENCES Subject(id)
            , PRIMARY KEY(student_id, subject_id)
        );
    """)

    with connection:
        # Teacher
        connection.executemany(
            "INSERT INTO Teacher (name, password) VALUES (?, ?)",
            [
                ('John', '123'),
                ('Mary', '456'),
                ('David', '789'),
            ],
        )

        # Student
        connection.executemany(
            "INSERT INTO Student (name) VALUES (?)",
            [
                ('Alice',),
                ('Bob',),
                ('Charlie',),
                ('Dave',),
                ('Eve',),
                ('Frank',),
                ('Grace',),
                ('Harry',),
                ('Ivy',),
                ('Jane',),
            ],
        )

        # Subject
        connection.executemany(
            "INSERT INTO Subject (name) VALUES (?)",
            [
                ('Math',),
                ('Science',),
                ('English',),
                ('History',)
            ],
        )