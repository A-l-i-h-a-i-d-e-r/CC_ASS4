%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ast.h"
#include "utils.h"

// Function declarations
int yylex(void);
void yyerror(const char *msg);

// Helper functions
ast_node *make_pair(char *key, ast_node *val, const char *file, int line);
ast_node *append_pair(ast_node *list, ast_node *newpair, const char *file, int line);
ast_node *append_elem(ast_node *list, ast_node *val, const char *file, int line);

// Structure definitions
typedef struct table_schema {
    char *name;
    char *shape;
    char **columns;
    int num_columns;
    int next_id;
    FILE *fp;
} TableSchema;

typedef struct table_list {
    TableSchema *schema;
    struct table_list *next;
} TableList;

// Global variables
ast_node *root = NULL;
int print_ast_flag = 0;
char *output_dir = ".";
TableList *tables = NULL;
int table_count = 0;

// Function prototypes
ast_node* create_node(enum node_type type, const char *file, int line);
void print_ast(ast_node *node, int depth);
void free_ast(ast_node *node);
void process_ast(ast_node *root, char *output_dir);
TableSchema* find_or_create_table(char *table_name, char **scalar_keys, int num_scalar, char **object_keys, int num_object, char *output_dir);
int process_object(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir);
void process_array(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir);
void write_csv_row(FILE *fp, char **values, int num_values);
%}

%locations
%define parse.error verbose

%union {
    char *str;
    ast_node *node;
}

%token LBRACE RBRACE LBRACK RBRACK COLON COMMA
%token <str> STRING NUMBER
%token TRUE FALSE T_NULL
%token YYerror

%type <node> json value object members pair array elems

%start json

%%

/* Grammar rules remain unchanged */
json
  : value                         { debug_log("Parsed json rule", __FILE__, __LINE__); root = $1; }
  ;

value
  : object                        { debug_log("Parsed object value", __FILE__, __LINE__); $$ = $1; }
  | array                         { debug_log("Parsed array value", __FILE__, __LINE__); $$ = $1; }
  | STRING                        { debug_log("Parsed STRING value", __FILE__, __LINE__); $$ = create_node(NODE_STRING, __FILE__, __LINE__); $$->data.string = $1; }
  | NUMBER                        { debug_log("Parsed NUMBER value", __FILE__, __LINE__); $$ = create_node(NODE_NUMBER, __FILE__, __LINE__); $$->data.number = $1; }
  | TRUE                          { debug_log("Parsed TRUE value", __FILE__, __LINE__); $$ = create_node(NODE_TRUE, __FILE__, __LINE__); }
  | FALSE                         { debug_log("Parsed FALSE value", __FILE__, __LINE__); $$ = create_node(NODE_FALSE, __FILE__, __LINE__); }
  | T_NULL                        { debug_log("Parsed NULL value", __FILE__, __LINE__); $$ = create_node(NODE_NULL, __FILE__, __LINE__); }
  ;

object
  : LBRACE RBRACE                 { debug_log("Parsed empty object", __FILE__, __LINE__); $$ = create_node(NODE_OBJECT, __FILE__, __LINE__); $$->data.object.value = NULL; }
  | LBRACE members RBRACE         { debug_log("Parsed object with members", __FILE__, __LINE__); $$ = create_node(NODE_OBJECT, __FILE__, __LINE__); $$->data.object.value = $2; }
  ;

members
  : pair                          { debug_log("Parsed single pair", __FILE__, __LINE__); $$ = $1; }
  | members COMMA pair            { debug_log("Appending pair to members", __FILE__, __LINE__); $$ = append_pair($1, $3, __FILE__, __LINE__); }
  ;

pair
  : STRING COLON value            { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed pair with key: %s", $1);
        debug_log(msg, __FILE__, __LINE__); 
        $$ = make_pair($1, $3, __FILE__, __LINE__); 
    }
  ;

array
  : LBRACK RBRACK                 { 
        debug_log("Parsed empty array", __FILE__, __LINE__); 
        $$ = create_node(NODE_ARRAY, __FILE__, __LINE__); 
        $$->data.array.elements = NULL; 
    }
  | LBRACK elems RBRACK           { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed array with elements, head type: %d", $2 ? $2->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        $$ = create_node(NODE_ARRAY, __FILE__, __LINE__); 
        $$->data.array.elements = $2; 
    }
  ;

elems
  : value                         { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed single element of type: %d", $1 ? $1->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        $$ = append_elem(NULL, $1, __FILE__, __LINE__); 
    }
  | elems COMMA value             { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Appending element of type %d to elements list of type %d", 
                 $3 ? $3->type : -1, $1 ? $1->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        $$ = append_elem($1, $3, __FILE__, __LINE__); 
    }
  ;

%%

int main(int argc, char *argv[]) {
    debug_log("Starting main", __FILE__, __LINE__);
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--print-ast") == 0) {
            print_ast_flag = 1;
        } else if (strcmp(argv[i], "--out-dir") == 0 && i + 1 < argc) {
            output_dir = argv[i + 1];
            i++;
        }
    }

    if (yyparse() == 0) {
        debug_log("Parsing successful", __FILE__, __LINE__);
        if (print_ast_flag && root) {
            debug_log("Printing AST", __FILE__, __LINE__);
            printf("AST:\n");
            print_ast(root, 0);
        }
        debug_log("Processing AST", __FILE__, __LINE__);
        process_ast(root, output_dir);
    } else {
        debug_log("Parsing failed", __FILE__, __LINE__);
        exit(1);
    }

    debug_log("Freeing AST", __FILE__, __LINE__);
    free_ast(root);
    TableList *current = tables;
    while (current) {
        TableList *next = current->next;
        if (current->schema->fp) fclose(current->schema->fp);
        for (int i = 0; i < current->schema->num_columns; i++) {
            free(current->schema->columns[i]);
        }
        free(current->schema->columns);
        free(current->schema->name);
        free(current->schema->shape);
        free(current->schema);
        free(current);
        current = next;
    }
    debug_log("Exiting main", __FILE__, __LINE__);
    return 0;
}

void yyerror(const char *msg) {
    fprintf(stderr, "[ERROR %s:%d] %s at line %d, column %d\n",
            __FILE__, __LINE__, msg, yylloc.first_line, yylloc.first_column);
    exit(1);
}

ast_node* create_node(enum node_type type, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Creating node of type %d", type);
    debug_log(msg, file, line);
    ast_node *node = (ast_node*)malloc(sizeof(ast_node));
    if (!node) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for node\n", file, line);
        exit(1);
    }
    node->type = type;
    node->next = NULL;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

ast_node *make_pair(char *key, ast_node *val, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Creating pair with key: %s", key ? key : "NULL");
    debug_log(msg, file, line);
    if (!key || !val) {
        fprintf(stderr, "[ERROR %s:%d] Null key or value in make_pair\n", file, line);
        exit(1);
    }
    ast_node *n = create_node(NODE_OBJECT, file, line);
    n->data.object.key = key;
    n->data.object.value = val;
    n->next = NULL;
    return n;
}

ast_node *append_pair(ast_node *list, ast_node *newpair, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Appending pair, list: %p, newpair: %p", list, newpair);
    debug_log(msg, file, line);
    if (!newpair) {
        fprintf(stderr, "[ERROR %s:%d] Null newpair in append_pair\n", file, line);
        exit(1);
    }
    if (!list) return newpair;
    ast_node *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = newpair;
    newpair->next = NULL;
    return list;
}

ast_node *append_elem(ast_node *list, ast_node *val, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Appending element, list: %p, val: %p, type: %d", list, val, val ? val->type : -1);
    debug_log(msg, file, line);
    if (!val) {
        fprintf(stderr, "[ERROR %s:%d] Null value in append_elem\n", file, line);
        exit(1);
    }
    val->next = NULL;
    if (!list) {
        return val;
    }
    ast_node *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = val;
    return list;
}

void print_ast(ast_node *node, int depth) {
    if (!node) {
        debug_log("Printing empty node", __FILE__, __LINE__);
        for (int i = 0; i < depth; i++) printf("  ");
        printf("Empty\n");
        return;
    }
    char msg[128];
    snprintf(msg, sizeof(msg), "Printing node of type %d", node->type);
    debug_log(msg, __FILE__, __LINE__);
    for (int i = 0; i < depth; i++) printf("  ");
    switch (node->type) {
        case NODE_OBJECT:
            if (node->data.object.key) {
                printf("\"%s\":\n", node->data.object.key);
                print_ast(node->data.object.value, depth + 1);
            } else {
                printf("Object:\n");
                for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
                    if (!pair) {
                        fprintf(stderr, "[ERROR %s:%d] Null pair in object\n", __FILE__, __LINE__);
                        exit(1);
                    }
                    if (!pair->data.object.key) {
                        fprintf(stderr, "[ERROR %s:%d] Null key in object pair\n", __FILE__, __LINE__);
                        exit(1);
                    }
                    for (int i = 0; i < depth + 1; i++) printf("  ");
                    printf("\"%s\":\n", pair->data.object.key);
                    print_ast(pair->data.object.value, depth + 2);
                }
            }
            break;
        case NODE_ARRAY:
            printf("Array:\n");
            for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
                if (!elem) {
                    fprintf(stderr, "[ERROR %s:%d] Null element in array\n", __FILE__, __LINE__);
                    exit(1);
                }
                print_ast(elem, depth + 1);
            }
            break;
        case NODE_STRING:
            printf("String: \"%s\"\n", node->data.string ? node->data.string : "");
            break;
        case NODE_NUMBER:
            printf("Number: %s\n", node->data.number ? node->data.number : "");
            break;
        case NODE_TRUE:
            printf("True\n");
            break;
        case NODE_FALSE:
            printf("False\n");
            break;
        case NODE_NULL:
            printf("Null\n");
            break;
    }
}

void free_ast(ast_node *node) {
    if (!node) return;
    char msg[128];
    snprintf(msg, sizeof(msg), "Freeing node of type %d", node->type);
    debug_log(msg, __FILE__, __LINE__);
    switch (node->type) {
        case NODE_OBJECT:
            if (node->data.object.key) {
                free(node->data.object.key);
                free_ast(node->data.object.value);
            } else {
                ast_node *pair = node->data.object.value;
                while (pair) {
                    ast_node *next = pair->next;
                    free(pair->data.object.key);
                    free_ast(pair->data.object.value);
                    free(pair);
                    pair = next;
                }
            }
            free(node);
            break;
        case NODE_ARRAY:
            ast_node *elem = node->data.array.elements;
            while (elem) {
                ast_node *next = elem->next;
                free_ast(elem);
                elem = next;
            }
            free(node);
            break;
        case NODE_STRING:
            free(node->data.string);
            free(node);
            break;
        case NODE_NUMBER:
            free(node->data.number);
            free(node);
            break;
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NULL:
            free(node);
            break;
    }
}

void process_ast(ast_node *root, char *output_dir) {
    debug_log("Processing AST", __FILE__, __LINE__);
    if (!root) {
        fprintf(stderr, "[ERROR %s:%d] Null root in process_ast\n", __FILE__, __LINE__);
        return;
    }
    if (root->type == NODE_OBJECT) {
        process_object(root, NULL, 0, "root", output_dir);
    } else if (root->type == NODE_ARRAY) {
        process_array(root, NULL, 0, "root", output_dir);
    }
}

TableSchema* find_or_create_table(char *table_name, char **scalar_keys, int num_scalar, char **object_keys, int num_object, char *output_dir) {
    debug_log("Finding or creating table", __FILE__, __LINE__);
    char shape[1024] = {0};
    strcat(shape, "scalar:");
    for (int i = 0; i < num_scalar; i++) {
        strcat(shape, scalar_keys[i]);
        if (i < num_scalar - 1) strcat(shape, ",");
    }
    strcat(shape, ";object:");
    for (int i = 0; i < num_object; i++) {
        strcat(shape, object_keys[i]);
        if (i < num_object - 1) strcat(shape, ",");
    }

    for (TableList *current = tables; current; current = current->next) {
        if (strcmp(current->schema->shape, shape) == 0) {
            return current->schema;
        }
    }

    TableSchema *table = (TableSchema*)malloc(sizeof(TableSchema));
    if (!table) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table schema\n", __FILE__, __LINE__);
        exit(1);
    }
    table->name = strdup(table_name);
    table->shape = strdup(shape);
    table->num_columns = 1 + num_scalar + num_object;
    table->columns = (char**)malloc(sizeof(char*) * table->num_columns);
    if (!table->columns) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table columns\n", __FILE__, __LINE__);
        exit(1);
    }
    table->columns[0] = strdup("id");
    for (int i = 0; i < num_scalar; i++) {
        table->columns[1 + i] = strdup(scalar_keys[i]);
    }
    for (int i = 0; i < num_object; i++) {
        char fk_column[64];
        snprintf(fk_column, sizeof(fk_column), "%s_id", object_keys[i]);
        table->columns[1 + num_scalar + i] = strdup(fk_column);
    }
    table->next_id = 1;

    char filename[256];
    snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table->name);
    table->fp = fopen(filename, "w");
    if (!table->fp) {
        fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
        exit(1);
    }
    write_csv_row(table->fp, table->columns, table->num_columns);

    TableList *new_table = (TableList*)malloc(sizeof(TableList));
    if (!new_table) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table list\n", __FILE__, __LINE__);
        exit(1);
    }
    new_table->schema = table;
    new_table->next = tables;
    tables = new_table;
    return table;
}

int process_object(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Processing object with key: %s", key);
    debug_log(msg, __FILE__, __LINE__);
    if (!node) {
        fprintf(stderr, "[ERROR %s:%d] Null node in process_object\n", __FILE__, __LINE__);
        return 0;
    }
    char *scalar_keys[32];
    int num_scalar = 0;
    char *object_keys[32];
    int num_object = 0;
    char *array_keys[32];
    int num_array = 0;

    for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
        if (!pair->data.object.value) {
            fprintf(stderr, "[ERROR %s:%d] Null value in object pair\n", __FILE__, __LINE__);
            continue;
        }
        ast_node *value = pair->data.object.value;
        if (value->type == NODE_STRING || value->type == NODE_NUMBER ||
            value->type == NODE_TRUE || value->type == NODE_FALSE || value->type == NODE_NULL) {
            scalar_keys[num_scalar++] = pair->data.object.key;
        } else if (value->type == NODE_OBJECT) {
            object_keys[num_object++] = pair->data.object.key;
        } else if (value->type == NODE_ARRAY) {
            array_keys[num_array++] = pair->data.object.key;
        }
    }

    char table_name[64];
    if (strcmp(key, "root") == 0) {
        snprintf(table_name, sizeof(table_name), "table%d", table_count);
    } else {
        snprintf(table_name, sizeof(table_name), "%s", key);
    }
    TableSchema *table = find_or_create_table(table_name, scalar_keys, num_scalar, object_keys, num_object, output_dir);
    int id = table->next_id++;

    char **values = (char**)malloc(sizeof(char*) * table->num_columns);
    if (!values) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for values\n", __FILE__, __LINE__);
        exit(1);
    }
    char id_str[16];
    snprintf(id_str, sizeof(id_str), "%d", id);
    values[0] = id_str;
    for (int i = 0; i < num_scalar; i++) {
        values[1 + i] = "";
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, scalar_keys[i]) == 0) {
                ast_node *value = pair->data.object.value;
                switch (value->type) {
                    case NODE_STRING: values[1 + i] = value->data.string; break;
                    case NODE_NUMBER: values[1 + i] = value->data.number; break;
                    case NODE_TRUE: values[1 + i] = "true"; break;
                    case NODE_FALSE: values[1 + i] = "false"; break;
                    case NODE_NULL: values[1 + i] = ""; break;
                    default: values[1 + i] = "";
                }
                break;
            }
        }
    }
    for (int i = 0; i < num_object; i++) {
        values[1 + num_scalar + i] = "";
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, object_keys[i]) == 0) {
                int child_id = process_object(pair->data.object.value, table, id, object_keys[i], output_dir);
                char *fk_value = (char*)malloc(16);
                snprintf(fk_value, 16, "%d", child_id);
                values[1 + num_scalar + i] = fk_value;
                break;
            }
        }
    }

    write_csv_row(table->fp, values, table->num_columns);

    for (int i = 0; i < num_array; i++) {
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, array_keys[i]) == 0) {
                process_array(pair->data.object.value, table, id, array_keys[i], output_dir);
                break;
            }
        }
    }

    for (int i = 1 + num_scalar; i < table->num_columns; i++) {
        if (values[i] && values[i] != "" && values[i] != "true" && values[i] != "false") {
            free(values[i]);
        }
    }
    free(values);
    return id;
}

void process_array(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Processing array with key: %s", key);
    debug_log(msg, __FILE__, __LINE__);
    if (!node || !node->data.array.elements) {
        fprintf(stderr, "[ERROR %s:%d] Null node or empty array in process_array\n", __FILE__, __LINE__);
        return;
    }
    ast_node *first = node->data.array.elements;

    if (first->type == NODE_STRING || first->type == NODE_NUMBER ||
        first->type == NODE_TRUE || first->type == NODE_FALSE || first->type == NODE_NULL) {
        char table_name[64];
        snprintf(table_name, sizeof(table_name), "%s", key);
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table_name);
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
            exit(1);
        }
        char *header[] = {"parent_id", "index", "value"};
        write_csv_row(fp, header, 3);

        int index = 0;
        for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
            char parent_id_str[16], index_str[16], *value_str;
            snprintf(parent_id_str, sizeof(parent_id_str), "%d", parent_id);
            snprintf(index_str, sizeof(index_str), "%d", index++);
            switch (elem->type) {
                case NODE_STRING: value_str = elem->data.string; break;
                case NODE_NUMBER: value_str = elem->data.number; break;
                case NODE_TRUE: value_str = "true"; break;
                case NODE_FALSE: value_str = "false"; break;
                case NODE_NULL: value_str = ""; break;
                default: value_str = "";
            }
            char *row[] = {parent_id_str, index_str, value_str};
            write_csv_row(fp, row, 3);
        }
        fclose(fp);
    } else if (first->type == NODE_OBJECT) {
        char table_name[64];
        snprintf(table_name, sizeof(table_name), "%s", key);
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table_name);
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
            exit(1);
        }

        char *scalar_keys[32];
        int num_scalar = 0;
        for (ast_node *pair = first->data.object.value; pair; pair = pair->next) {
            ast_node *value = pair->data.object.value;
            if (value->type == NODE_STRING || value->type == NODE_NUMBER ||
                value->type == NODE_TRUE || value->type == NODE_FALSE || value->type == NODE_NULL) {
                scalar_keys[num_scalar++] = pair->data.object.key;
            }
        }

        char **header = (char**)malloc(sizeof(char*) * (2 + num_scalar));
        if (!header) {
            fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for header\n", __FILE__, __LINE__);
            exit(1);
        }
        char parent_id_col[64];
        snprintf(parent_id_col, sizeof(parent_id_col), "%s_id", parent_schema->name);
        header[0] = strdup(parent_id_col);
        header[1] = strdup("seq");
        for (int i = 0; i < num_scalar; i++) {
            header[2 + i] = strdup(scalar_keys[i]);
        }
        write_csv_row(fp, header, 2 + num_scalar);

        int seq = 0;
        for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
            char **values = (char**)malloc(sizeof(char*) * (2 + num_scalar));
            if (!values) {
                fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for values\n", __FILE__, __LINE__);
                exit(1);
            }
            char parent_id_str[16], seq_str[16];
            snprintf(parent_id_str, sizeof(parent_id_str), "%d", parent_id);
            snprintf(seq_str, sizeof(seq_str), "%d", seq++);
            values[0] = parent_id_str;
            values[1] = seq_str;
            for (int i = 0; i < num_scalar; i++) {
                values[2 + i] = "";
                for (ast_node *pair = elem->data.object.value; pair; pair = pair->next) {
                    if (strcmp(pair->data.object.key, scalar_keys[i]) == 0) {
                        ast_node *value = pair->data.object.value;
                        switch (value->type) {
                            case NODE_STRING: values[2 + i] = value->data.string; break;
                            case NODE_NUMBER: values[2 + i] = value->data.number; break;
                            case NODE_TRUE: values[2 + i] = "true"; break;
                            case NODE_FALSE: values[2 + i] = "false"; break;
                            case NODE_NULL: values[2 + i] = ""; break;
                            default: values[2 + i] = "";
                        }
                        break;
                    }
                }
            }
            write_csv_row(fp, values, 2 + num_scalar);
            free(values);
        }
        for (int i = 0; i < 2 + num_scalar; i++) {
            free(header[i]);
        }
        free(header);
        fclose(fp);
    }
}

void write_csv_row(FILE *fp, char **values, int num_values) {
    debug_log("Writing CSV row", __FILE__, __LINE__);
    for (int i = 0; i < num_values; i++) {
        if (i > 0) fprintf(fp, ",");
        if (!values[i] || strlen(values[i]) == 0) {
            // Empty for null
        } else if (strcmp(values[i], "true") == 0 || strcmp(values[i], "false") == 0) {
            fprintf(fp, "%s", values[i]);
        } else if (strspn(values[i], "-0123456789.") == strlen(values[i])) {
            fprintf(fp, "%s", values[i]);
        } else {
            fprintf(fp, "\"");
            for (char *c = values[i]; *c; c++) {
                if (*c == '"') fprintf(fp, "\"");
                fprintf(fp, "%c", *c);
            }
            fprintf(fp, "\"");
        }
    }
    fprintf(fp, "\n");
}