/*
Develop a query language that can be used to perform CRUD operations on a database, similar to SQL.

## Examples

| SQL:                             | Equivalent in QQL:             |
|----------------------------------|--------------------------------|
| select * from database.table     | if id = 1 then:                |
| where id = 1;                    | get database.table->*          |
|                                  | end                            |
| ---                              | ---                            |
| create table database.table (    | generate database.table (      |
| id int,                          | id int,                        |
| name varchar(255),               | name string,                   |
| age int                          | age int                        |
| );                               | )                              |
| ---                              | ---                            |
| insert into database.table (     | append database.table (        |
| id, name, age                    | id, name, age                  |
| ) values (                       | )->(                           |
| 1, "John", 30                    | 1, "John", 30                  |
| );                               | )                              |
| ---                              | ---                            |
| delete from database.table       | delete database.table (        |
| where id = 1;                    | id = 1                         |
|                                  | )                              |
| ---                              | ---                            |
| update database.table set (      | change database.table (        |
| id = 1,                          | id = 1,                        |
| name = "John",                   | name = "John",                 |
| age = 30                         | age = 30                       |
| );                               | )                              |
| ---                              | ---                            |
| drop table database.table;       | delete database.table          |
| ---                              | ---                            |
| drop column database.table.name; | delete database.table->name    |
| ---                              | ---                            |
| select age from database.table   | if regexp(name) = "^J.*" then: |
| where name regexp "^J.*"         | if id > 20 then:               |
| and id > 20;                     | get database.table->age        |
|                                  | end                            |
|                                  | end                            |
| ---                              | ---                            |
| create function database.func    | generate database.func         |
| (a int, b int)                   | (a int, b int)                 |
| returns int                      | begin                          |
| begin                            | c int = a + b                  |
| declare c int;                   | return c                       |
| set c = a + b;                   | end                            |
| return c;                        |                                |
| end;                             |                                |
| ---                              | ---                            |
| select database.func(1, 2);      | get database.func(1, 2)        |
| ---                              | ---                            |

## Operators

| SQL: | Equivalent in QQL: |
|------|--------------------|
| =    | =                  |
| !=   | !=                 |
| <    | <                  |
| >    | >                  |
| <=   | <=                 |
| >=   | >=                 |
| and  | and                |
| or   | or                 |
| not  | !                  |

## Data Types

| SQL:                                      | Equivalent in QQL: |
|-------------------------------------------|--------------------|
| int, tinyint, smallint, mediumint, bigint | int                |
| float, double, decimal, numeric           | float              |
| char, varchar, text                       | string             |
| date                                      | date               |
| time                                      | time               |
| datetime, timestamp                       | datetime           |
| year                                      | year               |
| binary, varbinary, blob                   | object             |
| enum                                      | enum               |
| set                                       | set                |
| json                                      | json               |
| boolean, bool                             | bool               |
| null                                      | empty              |

## Functions

> These are implemented in QQL itself.
> Usage is given in the examples above.

## Example Code:
# Hi
# This is a comment
append database.table (id, name) -> (1, 'test')

Expected result: table `database.table` doesn't exist.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class QQL
{
public:
    QQL() = default;
    ~QQL() = default;

    void parse(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string token;

            if (token == "#")
            {
                std::string comment;
                std::getline(iss, comment, ' ');
                std::cout << "comment " << comment << std::endl;
            }

            while (std::getline(iss, token, ' '))
            {
                if (token == "append")
                {
                    std::string table;
                    std::string columns;
                    std::string values;
                    std::getline(iss, table, ' ');
                    std::getline(iss, columns, '(');
                    std::getline(iss, columns, ')');
                    std::getline(iss, values, '(');
                    std::getline(iss, values, ')');
                    std::cout << "append " << table << " (" << columns << ") -> (" << values << ")" << std::endl;
                } else if (token == "generate")
                {
                    std::string table;
                    std::string columns;
                    std::getline(iss, table, ' ');
                    std::getline(iss, columns, '(');
                    std::getline(iss, columns, ')');
                    std::cout << "generate " << table << " (" << columns << ")" << std::endl;
                } else if (token == "delete")
                {
                    std::string table;
                    std::getline(iss, table, ' ');
                    std::cout << "delete " << table << std::endl;
                } else if (token == "change")
                {
                    std::string table;
                    std::string columns;
                    std::getline(iss, table, ' ');
                    std::getline(iss, columns, '(');
                    std::getline(iss, columns, ')');
                    std::cout << "change " << table << " (" << columns << ")" << std::endl;
                } else if (token == "get")
                {
                    std::string table;
                    std::string columns;
                    std::getline(iss, table, ' ');
                    std::getline(iss, columns, '(');
                    std::getline(iss, columns, ')');
                    std::cout << "get " << table << " (" << columns << ")" << std::endl;
                }
            }
        }
    }
};

int main(int argc, char** argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Show this help message and exit")
            ("file,f", po::value<std::string>(), "Input file to parse");

    po::parsed_options options = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();

    po::variables_map vm;
    po::store(options, vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    for (const auto &argument: options.options)
        if (argument.unregistered)
        {
            std::cerr << "Unrecognized option: " << argument.string_key << std::endl;
            return EXIT_FAILURE;
        }

    if (!vm.count("file") || vm["file"].as<std::string>().empty())
    {
        std::cerr << "No input file provided" << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("file"))
    {
        QQL qql;
        qql.parse(vm["file"].as<std::string>());
    }

    return EXIT_SUCCESS;
}

