"""
Make a query language that can access databases, similar to sql.

Examples:							Equivalent in SQL:
if id = 1 then:					    select * from database.table
    get database.table->*				where id = 1;
generate database.table (			create table database.table (
    id int,							    id int,
    name string,						name varchar(255),
    age int							    age int
)	 								);
append database.table (			    insert into database.table (
    id, name, age					   	id, name, age
)->(								) values (
    1, "John", 30						1, "John", 30
)									);
delete database.table (			    delete from database.table
    id = 1							    where id = 1;
)
change database.table (			    update database.table set (
    id = 1,							    id = 1,
    name = "John",					    name = "John",
    age = 30							age = 30
)									);
delete database.table				drop table database.table;
delete database.table->name		    drop column database.table.name;
if regexp(name, "^J.*") then:		select age from database.table
   get database.table->age			where regexp(name, "^J.*");

Operators: = < > <= >= != + - * / % and or !
Punctuation: ( ) [ ] { } , ; : .
Functions: count, total, avrg, min, max, group, sort, asc, desc, limit
Statements: if, elsif, else, while, for, do, stop, pass, return, quit, generate, append, delete, change, help, regexp
Datatypes: int, float, string, boolean, date, time, datetime, timestamp, blob, empty (null), array, object, table, database, func (function), proc (procedure), class, enum, union

print(f"In file '{self.filename}', at line {str(self.line)}:")
print(self.contents[self.pos:])
print(f"[ErrSyntax]: Unknown character '{char}' at line {self.line}")
sys.exit(1)

"""

import os
import sys

__version__ = "1.0.0"

from compiler import Compiler


def main():
    if len(sys.argv) == 1:
        print(f"QQL - Version {__version__}")
        print("A quick query language for databases, similar to SQL.")
        usage()
        return
    elif sys.argv[1] in ["-h", "--help"]:
        usage()
        return
    elif sys.argv[1] in ["-v", "--version"]:
        print(f"QQL - Version {__version__}")
        return
    elif os.path.isfile(sys.argv[1]):
        with open(sys.argv[1], "r") as file:
            if not os.path.exists(sys.argv[1]):
                raise Exception("[ErrCmd]: File not found.")
            elif not os.path.isfile(sys.argv[1]):
                raise Exception("[ErrCmd]: Not a file.")
            elif not os.access(sys.argv[1], os.R_OK):
                raise Exception("[ErrCmd]: File cannot be read.")
            else:
                contents = file.read()
                if contents == "":
                    sys.exit(0)

                lexer = Lexer(contents, sys.argv[1])
                print(lexer.lex())
    else:
        usage()
        raise Exception(f"[ErrCmd]: Unknown command {sys.argv[1]}")


def usage():
    print("Usage:")
    print(f"{sys.argv[0]} [commands] <filename> [args]")
    print("Commands:")
    print("-h | --help: Show this help message")
    print("-v | --version: Show the version of the compiler")


if __name__ == "__main__":
    main()
