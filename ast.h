#ifndef AST_H
#define AST_H

typedef struct ast_node ast_node;

enum node_type {
    NODE_OBJECT,
    NODE_ARRAY,
    NODE_STRING,
    NODE_NUMBER,
    NODE_TRUE,
    NODE_FALSE,
    NODE_NULL
};

struct ast_node {
    enum node_type type;
    union {
        struct { char *key; ast_node *value; } object; // For object key-value pairs
        struct { ast_node *elements; } array;          // For array elements
        char *string;
        char *number;
    } data;
    ast_node *next; // Used for linking elements in arrays or pairs in objects
};

ast_node* create_node(enum node_type type, const char *file, int line);
ast_node* create_pair(char *key, ast_node *value, const char *file, int line);
void append_node(ast_node **list, ast_node *new_node, const char *file, int line);
void free_ast(ast_node *node);
void debug_log(const char *msg, const char *file, int line);

#endif // AST_H