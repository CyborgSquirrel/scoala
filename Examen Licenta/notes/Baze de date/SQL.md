- `IIF`
- `IS NULL`
- `NOT`
- `INTERSECT`
- `EXCEPT`

```sql
-- run {"compiler": "sql"}

CREATE TABLE Student(
	id INTEGER PRIMARY KEY,
	cnp TEXT UNIQUE NOT NULL,
	name TEXT,
	is_dingus INTEGER DEFAULT 0,
	wins INTEGER CHECK(wins >= 0),
	CHECK(is_dingus = 0 OR is_dingus != 0 AND wins = 0)
);

ALTER TABLE Student
ADD is_bingus INTEGER;

ALTER TABLE Student
DROP COLUMN is_bingus;

INSERT INTO Student(id, cnp, name, wins)
VALUES (
	1,
	'6040619016506',
	'Ion',
	-5
);

INSERT INTO Student(id, cnp, name, wins)
VALUES (
	1,
	'6040619016506',
	'Ion',
	3
);

INSERT INTO Student(id, cnp, name, wins)
VALUES (
	2,
	'6040619016506',
	'Ion Imposter',
	4
);

INSERT INTO Student(id, cnp, name, is_dingus, wins)
VALUES (
	3,
	'6050619015465',
	'Gion',
	1,
	5
);

INSERT INTO Student(id, cnp, name, is_dingus, wins)
VALUES (
	3,
	'6050619015465',
	'Gion',
	1,
	0
);

.print 'all'
SELECT * FROM Student;

.print 'between'
SELECT * FROM Student WHERE Student.wins BETWEEN 4 AND 5;

.print 'update'
UPDATE Student
SET name = 'Trollster'
WHERE id = 1;

SELECT * FROM Student;

.print 'delete'
DELETE FROM Student WHERE Student.id = 3;

SELECT * FROM Student
```

