Building a database

Our program is able to get, set, add, and delete data in a database

The database can be viewed as:

	entry1: field:value, field:value, field:value

	entry2: field:value, field:value, field:value

GET adds data to an entry holding

SET sets fields in the entry holding to a value

ADD adds data to the database and entry holding

FILTER removes data from the entry holding that doesn't match the field:value

DELETE removes data from the entry holding and database

GETALL grabs every data from the database and adds it to the entry holding

CLEAR removes everything from the entry holding

CLOSE exits the program

Examples:
---------
./ft_db

ADD name:foo
	
	name: foo color: 

ADD name:bar

	name: foo color:
	name: bar color:

SET color:red

	name: foo color: red
	name: bar color: red

CLEAR

	(no held entries)

GET name:foo
	
	name: foo color: red

GET name:bar

	name: foo color: red
	name: bar color: red

FILTER name:foo
	
	name: foo color: red

DELETE name:foo

	(no held entries)

GETALL
	
	name: bar color: red

CLOSE