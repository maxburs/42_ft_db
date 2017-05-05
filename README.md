Building a database

Our program is able to get, set, add, and delete data in a database

The database can be viewed as:

	entry1: field:value, field:value, field:value

	entry2: field:value, field:value, field:value

The user may GET data which is displayed and added to a holding

The user can then SET fields in the holding to a value

The user can also ADD their own entries with a field and a value

CLEAR resets the entry holding

CLOSE exits the program

Examples:
---------

1. GET

	./ft_db

	GET name:foo

	foobar

2. SET

	./ft_db

	GET name:foo

	foobar

	SET foo:red

	foored

3. ADD

	./ft_db

	ADD a:1

	a:1

4. CLEAR

	./ft_db

	CLEAR


5. CLOSE

	./ft_db

	CLOSE

	(program closes)