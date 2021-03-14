# pre-requirements:

**use draw.io to open UML.xml for uml graph**

in postgresql:

**login as user postgres**

psql -U postgres

**create database and tables**

CREATE DATABASE regie;

CREATE TABLE accounts (
        user_id serial PRIMARY KEY,
        username VARCHAR ( 50 ) UNIQUE NOT NULL,
        password VARCHAR ( 50 ) NOT NULL,
        role VARCHAR(1) NOT NULL
);

CREATE TABLE courses (
        course_id serial PRIMARY KEY,
        course_name VARCHAR (100) UNIQUE NOT NULL,
        capacity INT NOT NULL,
        instructor VARCHAR(50) NOT NULL
);

**populate some pre-saved database info**

insert into accounts(username,password,role) values('yifeix','yifeix','A');

insert into accounts(username,password,role) values('terry','terry','T');


# Iteration 1:

Identified bounded context problem domains.
1. account manager that operates on user information, such as validate_credential(login), add/delete/modify user info, register/drop course for a specific user, etc.

2. course manager that operates on courses information, such as add/modify/delete/find/list course info, etc.

3. a role(or user) interface defines which role the current user is, what permissions the current role(user) has etc.

4. a database interface class that relates all operations performed through database.

5. a controller class that serves as a information exchange hub for the above objects to easily communicate with each other without tightly coupled.

#Iteration 2:

Use Liskov substitution principle and Open–closed principle to create the User Interface, and use factory method to ensure the concrete class type which will be initialized is depended on which role type it is told by account_manager. Thus role/permissions will be decided on run-time by which concreate instance is initilized (Please check UML.xml for detailed structure). each concrete type is bounded by its available permissions, but extensible if another role extends it.

added concrete class account_manager and course_manager, use Single-responsibility principle to define each class's functionality.

#Iteration 3:

added database_access_Interface which relates database access operations. Use Interface segregation principle that database_access_Interface is implemented by course_tables_access and account_tables_access. course_tables_access relates database operations only regarding courses table, and account_tables_access relates database operations onlu regarding accounts table. Thus account_manager class will composite an account_tables_access instance. and course_manager class will composite a course_tables_access instance. Thus each client is only exposed to database operations delegates with their own context.
