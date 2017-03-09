--
-- 	Database Table Creation
--
--		This file will create the tables for use with the book 
--  Database Management Systems by Raghu Ramakrishnan and Johannes Gehrke.
--  It is run automatically by the installation script.
--
--	Version 0.1.0.0 2002/04/05 by: David Warden.
--	Copyright (C) 2002 McGraw-Hill Companies Inc. All Rights Reserved.
--
--  First drop any existing tables. Any errors are ignored.
--
/*
drop table student cascade constraints;
drop table faculty cascade constraints;
drop table class cascade constraints;
drop table enrolled cascade constraints;
drop table emp cascade constraints;
drop table works cascade constraints;
drop table dept cascade constraints;
drop table flights cascade constraints;
drop table aircraft cascade constraints;
drop table certified cascade constraints;
drop table employees cascade constraints;
drop table suppliers cascade constraints;
drop table parts cascade constraints;
drop table catalog cascade constraints;
drop table sailors cascade constraints;*/
--
-- Now, add each table.
--
create table student(
	snum INT primary key,
	sname varchar(30),
	major varchar(25),
	standing varchar(2),
	age INT
	)ENGINE = INNODB;
create table faculty(
	fid INT primary key,
	fname varchar(30),
	deptid INT
	)ENGINE = INNODB;
create table class(
	name varchar(40) primary key,
	meets_at varchar(20),
	room varchar(10),
	fid INT,
	foreign key(fid) references faculty(fid)
	)ENGINE = INNODB;
create table enrolled(
	snum INT,
	cname varchar(40),
	primary key(snum,cname),
	foreign key(snum) references student(snum),
	foreign key(cname) references class(name)
	)ENGINE = INNODB;
/*
create table emp(
	eid INT primary key,
	ename varchar(30),
	age number(3,0),
	salary number(10,2)
	);
create table dept(
	did number(2,0) primary key,
	dname varchar(20),
	budget number(10,2),
	managerid INT,
	foreign key(managerid) references emp(eid)
	);
create table works(
	eid INT,
	did number(2,0),
	pct_time number(3,0),
	primary key(eid,did),
	foreign key(eid) references emp,
	foreign key(did) references dept
	);
create table flights(
	flno number(4,0) primary key,
	origin varchar(20),
	destination varchar(20),
	distance number(6,0),
	departs date,
	arrives date,
	price number(7,2)
	);
create table aircraft(
	aid INT primary key,
	aname varchar(30),
	crusingrange number(6,0)
	);
create table employees(
	eid INT primary key,
	ename varchar(30),
	salary number(10,2)
	);
create table certified(
	eid INT,
	aid INT,
	primary key(eid,aid),
	foreign key(eid) references employees,
	foreign key(aid) references aircraft
	);
create table suppliers(
	sid INT primary key,
	sname varchar(30),
	address varchar(40)
	);
create table parts(
	pid INT primary key,
	pname varchar(40),
	color varchar(15)
	);
create table catalog(
	sid INT,
	pid INT,
	cost number(10,2),
	primary key(sid,pid),
	foreign key(sid) references suppliers,
	foreign key(pid) references parts
	);
create table sailors(
	sid INT primary key,
	sname varchar(30),
	rating INT,
	age number(4,1)
	);*/
--
-- Exit the Script.
--
quit;
