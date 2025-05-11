JSON to Relational CSV Converter
Overview
This project implements a tool that converts a JSON file into relational CSV tables, following the specifications outlined in the assignment. The tool uses Flex for lexical analysis, Yacc/Bison for parsing, and C for building an Abstract Syntax Tree (AST), performing semantic analysis, and generating CSV files. It supports JSON files up to 30 MiB, creates relational tables with primary and foreign keys, and streams CSV output to avoid large memory buffers.

The tool adheres to the following conversion rules:
- R1: Objects with the same keys are grouped into a single table.
- R2: Arrays of objects create child tables with foreign keys to the parent.
- R3: Arrays of scalars create junction tables with parent_id, index, and value columns.
- R4: Scalars become columns; JSON null is represented as empty.
- R5: Every row has an id primary key; foreign keys are named <parent>_id.
- R6: Each table is written to a .csv file with a header row.
Features
- Handles any valid JSON input up to 30 MiB.
- Builds and maintains an AST until program termination.
- Supports command-line options:
- --print-ast: Prints the AST to stdout in an indented format.
- --out-dir DIR: Specifies the output directory for CSV files (default: current directory).
- Generates one CSV file per table with appropriate headers and data.
- Reports the first error with line and column numbers, exiting with a non-zero status on invalid JSON.
- Memory-safe with no leaks, verified with Valgrind.
Prerequisites
To build and run the project, you need:
- GCC: C compiler (e.g., gcc)
- Flex: Lexical analyzer generator (version 2.6 or later)
- Bison: Parser generator (version 3.0 or later)
- Make: Optional, for using the provided Makefile
- Valgrind: Optional, for memory leak checking

To install on Ubuntu/Debian:
sudo apt-get install gcc flex bison make valgrind
Project Structure
- scanner.l: Flex specification for tokenizing JSON input (e.g., strings, numbers, punctuation)
- parser.y: Yacc/Bison specification for parsing JSON and building the AST
- ast.h: Header file defining the AST node structure and related functions
- utils.h: Header file for utility functions (e.g., debug logging)
- utils.c: Implementation of utility functions
- Makefile: Optional build automation script
Build Instructions
1. Clone or extract the project directory.
2. Navigate to the project root directory:
cd path/to/project
3. Build the project using the provided Makefile:
make
Or compile manually:
bison -d parser.y
flex scanner.l
gcc -o json2relcsv parser.tab.c lex.yy.c utils.c -lfl

This generates the executable json2relcsv.
Run Instructions
Run the tool with the following command:
./json2relcsv < input.json --print-ast --out-dir output
Or, using make:
make test TEST_FILE=test1.json

Where:
- < input.json: Provides the JSON input via stdin
- --print-ast: Optional flag to print the AST
- --out-dir DIR: Optional output directory (default: current directory)

Example:
./json2relcsv < test_cases/test1.json --out-dir output

To test and print the AST:
cat test_cases/test1.json | ./json2relcsv --print-ast
Design Notes
Lexing (scanner.l)
- Tokenizes JSON punctuation, strings, numbers, and keywords.
- Supports Unicode and escape sequences.
- Tracks line/column numbers for error messages.
- Ignores whitespace and invalid characters.

Parsing (parser.y)
- Defines JSON grammar, constructs AST dynamically.
- Uses Bison’s %locations for precise error reporting.
- Handles objects and arrays as linked node lists.

AST and Semantic Analysis
- AST defined in ast.h, using a union for node types.
- Tables identified by shape strings (e.g., scalar:id,name).
- Foreign keys and IDs are generated automatically.
- Arrays of objects → child tables; arrays of scalars → junction tables.

CSV Generation
- Streams rows to disk with no large memory buffers.
- Values formatted per type: strings quoted, others not.
- Each table written to a separate .csv file with headers.

Error Handling
- Lexical and syntax errors reported with line/column numbers.
- Semantic errors checked during AST traversal.
- All memory freed properly to avoid leaks.

Memory Management
- AST nodes, strings, and table data are freed in cleanup.
- Valgrind confirms no leaks or invalid accesses.
Test Cases
The test_cases directory includes:
- test1.json: Flat object → people.csv
- test2.json: Scalar array → movies.csv and genres.csv
- test3.json: Object array → orders.csv and items.csv
- test4.json: Nested objects → posts.csv, users.csv, and comments.csv
- test5.json: Root-level array → people.csv

To run a test case:
./json2relcsv < test_cases/test1.json --out-dir output
Or:
make test TEST_FILE=test1.json

