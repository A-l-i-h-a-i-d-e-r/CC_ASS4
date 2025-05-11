# Makefile for json2relcsv
# Builds the program and supports testing with JSON files from tests/ directory

# Compiler and tools
CC = gcc
FLEX = flex
BISON = bison

# Output executable
TARGET = json2relcsv

# Source files
SOURCES = lex.yy.c parser.tab.c
HEADERS = parser.tab.h ast.h
FLEX_SRC = scanner.l
BISON_SRC = parser.y

# Default output directory for CSV files
OUT_DIR = outputs

# Default test directory
TEST_DIR = tests

# Build the program
all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -o $(TARGET) $(SOURCES) utils.c -lfl

lex.yy.c: $(FLEX_SRC) parser.tab.h
	$(FLEX) $(FLEX_SRC)

parser.tab.c parser.tab.h: $(BISON_SRC)
	$(BISON) -d $(BISON_SRC)

# Clean generated files
clean:
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h

# Test a specific JSON file
# Usage: make test TEST_FILE=test1.json
test: $(TARGET)
	@if [ -z "$(TEST_FILE)" ]; then \
		echo "Error: Please specify a test file, e.g., make test TEST_FILE=test1.json"; \
		exit 1; \
	fi
	@if [ ! -f "$(TEST_DIR)/$(TEST_FILE)" ]; then \
		echo "Error: Test file $(TEST_DIR)/$(TEST_FILE) not found"; \
		exit 1; \
	fi
	@mkdir -p $(OUT_DIR)/$(TEST_FILE:.json=)
	@echo "Running test: $(TEST_FILE)"
	./$(TARGET) --print-ast --out-dir $(OUT_DIR)/$(TEST_FILE:.json=) < $(TEST_DIR)/$(TEST_FILE) > $(OUT_DIR)/$(TEST_FILE:.json=)/ast.txt 2> $(OUT_DIR)/$(TEST_FILE:.json=)/error.txt; \
	if [ $$? -eq 0 ]; then \
		echo "Test successful. CSV files in $(OUT_DIR)/$(TEST_FILE:.json=)"; \
		ls -l $(OUT_DIR)/$(TEST_FILE:.json=)/*.csv 2>/dev/null || echo "No CSV files generated"; \
		echo "AST output in $(OUT_DIR)/$(TEST_FILE:.json=)/ast.txt"; \
	else \
		echo "Test failed. See $(OUT_DIR)/$(TEST_FILE:.json=)/error.txt"; \
		cat $(OUT_DIR)/$(TEST_FILE:.json=)/error.txt; \
	fi

# Test all JSON files in tests/ directory
# Usage: make test-all
test-all: $(TARGET)
	@for test_file in $(TEST_DIR)/*.json; do \
		base_name=$$(basename $$test_file .json); \
		$(MAKE) test TEST_FILE=$$base_name.json; \
	done

.PHONY: all clean test test-all