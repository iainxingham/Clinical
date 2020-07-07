/*
 * File to create the test.sqlite database
 *
 * cat test1.sql | sqlite3 test1.sqlite
 *
 * Put test1.sqlite in `Database` directory of build folder
 */

CREATE TABLE `pats` (
        `id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `rxr`	TEXT UNIQUE,
        `nhs`	TEXT
);
