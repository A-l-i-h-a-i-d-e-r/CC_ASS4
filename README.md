JSON to Relational CSV Converter
Overview
This project implements a tool that converts a JSON file into relational CSV tables, following the specifications outlined in the assignment. The tool uses Flex for lexical analysis, Yacc/Bison for parsing, and C for building an Abstract Syntax Tree (AST), performing semantic analysis, and generating CSV files. It supports JSON files up to 30 MiB, creates relational tables with primary and foreign keys, and streams CSV output to avoid large memory buffers.
The tool adheres to the following conversion rules:

R1: Objects with the same keys are grouped into a single table.
R2: Arrays of objects create child tables with foreign keys to the parent.
R3: Arrays of scalars create junction tables with parent_id, index, and value columns.
R4: Scalars become columns; JSON null is represented as empty.
R5: Every row has an id primary key; foreign keys are named <parent>_id.
R6: Each table is written to a .csv file with a header row.

Features

Handles any valid JSON input up to 30 MiB.
Builds and maintains an AST until program termination.
Supports command-line options:
--print-ast: Prints the AST to stdout in an indented format.
--out-dir DIR: Specifies the output directory for CSV files (default: current directory).


Generates one CSV file per table with appropriate headers and data.
Reports the first error with line and column numbers, exiting with a non-zero status on invalid JSON.
Memory-safe with no leaks, verified with Valgrind.

Prerequisites
To build and run the project, you need:

GCC: C compiler (e.g., gcc).
Flex: Lexical analyzer generator (version 2.6 or later).
Bison: Parser generator (version 3.0 or later).
Make: Optional, for using the provided Makefile.
Valgrind: Optional, for memory leak checking.

On Ubuntu/Debian, install dependencies with:
sudo apt-get install gcc flex bison make valgrind

Project Structure
The project consists of the following files:

scanner.l: Flex specification for tokenizing JSON input (e.g., strings, numbers, punctuation).
parser.y: Yacc/Bison specification for parsing JSON and building the AST.
ast.h: Header file defining the AST node structure and related functions.
utils.h: Header file for utility functions (e.g., debug logging).
utils.c: Implementation of utility functions.
Makefile: Optional build automation script.

Build Instructions

Clone or extract the project directory.

Navigate to the project root directory:
cd path/to/project


Build the project using the provided Makefile:
make

Alternatively, compile manually:
bison -d parser.y
flex scanner.l
gcc -o json2relcsv parser.tab.c lex.yy.c utils.c -lfl



This generates the executable json2relcsv.
Run Instructions
Run the tool with the following command:
./json2relcsv < input.json [--print-ast] [--out-dir DIR]


< input.json: Provide the JSON input via stdin.
--print-ast: Optional flag to print the AST to stdout.
--out-dir DIR: Optional flag to specify the output directory for CSV files (default: .).

Example:
./json2relcsv < test_cases/test1.json --out-dir output

This processes test1.json and writes CSV files (e.g., people.csv) to the output directory.
To test with a specific test case:
cat test_cases/test1.json | ./json2relcsv --print-ast

Design Notes
Lexing (scanner.l)

Tokenizes JSON into punctuation ({, }, [, ], :, ,), strings, numbers, and keywords (true, false, null).
Supports Unicode escapes (e.g., \u1234) and standard escape sequences (e.g., \n).
Tracks line and column numbers for error reporting using YY_USER_ACTION.
Ignores whitespace and reports invalid characters as errors.

Parsing (parser.y)

Defines a grammar for JSON, building an AST with nodes for objects, arrays, strings, numbers, and keywords.
Uses Bison's %locations for precise error reporting.
Creates AST nodes dynamically, linked as lists for object pairs and array elements.
Handles errors by reporting the first lexical or syntax error with line and column.

AST and Semantic Analysis

The AST is defined in ast.h with a union to store different node types (e.g., NODE_OBJECT, NODE_STRING).
The process_ast function traverses the AST to generate table schemas based on object shapes.
Objects with the same keys are grouped into a single table, identified by a shape string (e.g., scalar:id,name,age;object:).
Primary keys (id) and foreign keys (<parent>_id) are assigned automatically.
Arrays of objects create child tables with a seq column for ordering; arrays of scalars create junction tables.

CSV Generation

The write_csv_row function streams rows to CSV files, avoiding large memory buffers.
Headers are written without quotes; string values are quoted, and numbers/booleans are unquoted.
Each table is written to a separate .csv file in the specified output directory.
File names are derived from JSON keys (e.g., items.csv) or generic names for root objects (e.g., people.csv).

Error Handling

Lexical errors (e.g., unclosed strings) are caught in scanner.l.
Syntax errors (e.g., missing commas) are reported by Bison with line and column.
Semantic errors (e.g., null pointers) are checked in C code, with appropriate error messages.
Memory is freed carefully to prevent leaks, verified with Valgrind.

Memory Management

All dynamically allocated memory (AST nodes, strings, table schemas) is freed in free_ast and the main cleanup loop.
The program is Valgrind-clean, with no memory leaks or invalid accesses.

Test Cases
The test_cases directory includes five JSON files and their expected CSV outputs:

test1.json: Flat object, produces people.csv.
test2.json: Scalar array, produces movies.csv and genres.csv.
test3.json: Object array, produces orders.csv and items.csv.
test4.json: Nested objects, produces posts.csv, users.csv, and comments.csv.
test5.json: Root-level array, produces people.csv.

To run a test case:
./json2relcsv < test_cases/test1.json --out-dir output

Compare the output CSVs in output/ with the expected files in test_cases/.

