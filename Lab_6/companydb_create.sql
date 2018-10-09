CREATE DATABASE companydb;
USE companydb;

create table department(
dname varchar(30) NOT NULL,
dnumber smallint,
mgr_ssn char(6),
mgr_start_date date,
constraint pk_department PRIMARY KEY (dnumber)
);

create table employee(
fname varchar(30) NOT NULL,
minit varchar(30),
lname varchar(30),
ssn char(6),
b_date char(7),
address varchar(100),
sex char(1),
salary smallint,
super_ssn char(6),
dno smallint,
constraint pk_employee PRIMARY KEY (SSN)
);

create table dept_locations(
dnumber smallint,
dlocation varchar(30),
constraint pk_dept_locations PRIMARY KEY (dnumber, dlocation)
);

create table project(
pname varchar(30) NOT NULL,
pnumber smallint,
plocation varchar(30),
dnum smallint,
constraint pk_project PRIMARY KEY (pnumber)
);

create table works_on(
essn char(6),
pno smallint,
hours smallint,
constraint pk_project PRIMARY KEY (essn, pno)
);

create table dependent(
essn char(6),
dependent_name varchar(30),
sex char(1),
b_date char(7),
relationship varchar(30),
constraint pk_employee PRIMARY KEY (essn, dependent_name)
);
