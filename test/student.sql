/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "student" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "student_SEQ"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
END;
/

CREATE TABLE "student" (
  "ID" NUMBER(10) NOT NULL PRIMARY KEY,
  "NAME" VARCHAR2(512) NULL);

CREATE SEQUENCE "student_SEQ"
  START WITH 1 INCREMENT BY 1;

EXIT;
