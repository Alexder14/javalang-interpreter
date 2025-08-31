#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINICIONES de variables globales AST (solo aquí)
ASTNode *ast_root = NULL;
bool has_syntax_errors = false;

ASTNode* create_node(NodeType type, int line, int col) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo AST\n");
        exit(1);
    }
    
    node->type = type;
    node->line = line;
    node->column = col;
    node->next = NULL;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

ASTNode* create_program_node(ASTNode *body) {
    ASTNode *node = create_node(NODE_PROGRAM, line_num, col_num);
    node->data.program.body = body;
    return node;
}

ASTNode* create_main_class_node(ASTNode *body) {
    ASTNode *node = create_node(NODE_MAIN_CLASS, line_num, col_num);
    node->data.main_class.body = body;
    return node;
}

ASTNode* create_var_decl_node(const char *type, const char *name, ASTNode *init, bool is_array, int array_size) {
    ASTNode *node = create_node(NODE_VAR_DECL, line_num, col_num);
    node->data.var_decl.data_type = strdup(type);
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.init_value = init;
    node->data.var_decl.is_array = is_array;
    node->data.var_decl.array_size = array_size;
    return node;
}

ASTNode* create_function_decl_node(const char *return_type, const char *name, ASTNode *params, ASTNode *body) {
    ASTNode *node = create_node(NODE_FUNCTION_DECL, line_num, col_num);
    node->data.func_decl.return_type = strdup(return_type);
    node->data.func_decl.name = strdup(name);
    node->data.func_decl.parameters = params;
    node->data.func_decl.body = body;
    return node;
}

ASTNode* create_parameter_node(const char *type, const char *name, bool is_array) {
    ASTNode *node = create_node(NODE_PARAMETER, line_num, col_num);
    node->data.parameter.data_type = strdup(type);
    node->data.parameter.name = strdup(name);
    node->data.parameter.is_array = is_array;
    return node;
}

ASTNode* create_block_node(void) {
    ASTNode *node = create_node(NODE_BLOCK, line_num, col_num);
    node->data.block.statements = NULL;
    node->data.block.count = 0;
    node->data.block.capacity = 0;
    return node;
}

ASTNode* create_if_node(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt) {
    ASTNode *node = create_node(NODE_IF_STMT, line_num, col_num);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_stmt = then_stmt;
    node->data.if_stmt.else_stmt = else_stmt;
    return node;
}

ASTNode* create_while_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = create_node(NODE_WHILE_STMT, line_num, col_num);
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

ASTNode* create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body) {
    ASTNode *node = create_node(NODE_FOR_STMT, line_num, col_num);
    node->data.for_stmt.init = init;
    node->data.for_stmt.condition = condition;
    node->data.for_stmt.update = update;
    node->data.for_stmt.body = body;
    return node;
}

ASTNode* create_assignment_node(ASTNode *left, const char *op, ASTNode *right) {
    ASTNode *node = create_node(NODE_ASSIGNMENT, line_num, col_num);
    node->data.assignment.left = left;
    node->data.assignment.operator = strdup(op);
    node->data.assignment.right = right;
    return node;
}

ASTNode* create_binary_op_node(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY_OP, line_num, col_num);
    node->data.binary_op.operator = strdup(op);
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode* create_unary_op_node(const char *op, ASTNode *operand, bool is_prefix) {
    ASTNode *node = create_node(NODE_UNARY_OP, line_num, col_num);
    node->data.unary_op.operator = strdup(op);
    node->data.unary_op.operand = operand;
    node->data.unary_op.is_prefix = is_prefix;
    return node;
}

ASTNode* create_function_call_node(const char *name, ASTNode *args) {
    ASTNode *node = create_node(NODE_FUNCTION_CALL, line_num, col_num);
    node->data.func_call.name = strdup(name);
    node->data.func_call.arguments = args;
    return node;
}

ASTNode* create_array_access_node(ASTNode *array, ASTNode *index) {
    ASTNode *node = create_node(NODE_ARRAY_ACCESS, line_num, col_num);
    node->data.array_access.array = array;
    node->data.array_access.index = index;
    return node;
}

ASTNode* create_int_literal_node(int value) {
    ASTNode *node = create_node(NODE_INT_LITERAL, line_num, col_num);
    node->data.int_literal.value = value;
    return node;
}

ASTNode* create_float_literal_node(float value) {
    ASTNode *node = create_node(NODE_FLOAT_LITERAL, line_num, col_num);
    node->data.float_literal.value = value;
    return node;
}

ASTNode* create_string_literal_node(const char *value) {
    ASTNode *node = create_node(NODE_STRING_LITERAL, line_num, col_num);
    node->data.string_literal.value = strdup(value);
    return node;
}

ASTNode* create_char_literal_node(char value) {
    ASTNode *node = create_node(NODE_CHAR_LITERAL, line_num, col_num);
    node->data.char_literal.value = value;
    return node;
}

ASTNode* create_boolean_literal_node(bool value) {
    ASTNode *node = create_node(NODE_BOOLEAN_LITERAL, line_num, col_num);
    node->data.boolean_literal.value = value;
    return node;
}

ASTNode* create_null_literal_node(void) {
    return create_node(NODE_NULL_LITERAL, line_num, col_num);
}

ASTNode* create_identifier_node(const char *name) {
    ASTNode *node = create_node(NODE_IDENTIFIER, line_num, col_num);
    node->data.identifier.name = strdup(name);
    return node;
}

ASTNode* create_list_node(void) {
    ASTNode *node = create_node(NODE_STATEMENT_LIST, line_num, col_num);
    node->data.list.items = NULL;
    node->data.list.count = 0;
    node->data.list.capacity = 0;
    return node;
}

void add_to_list(ASTNode *list, ASTNode *item) {
    if (!list || !item) return;
    
    if (list->data.list.count >= list->data.list.capacity) {
        list->data.list.capacity = list->data.list.capacity == 0 ? 8 : list->data.list.capacity * 2;
        list->data.list.items = realloc(list->data.list.items, 
                                       list->data.list.capacity * sizeof(ASTNode*));
        if (!list->data.list.items) {
            fprintf(stderr, "Error: No se pudo asignar memoria para la lista\n");
            exit(1);
        }
    }
    
    list->data.list.items[list->data.list.count++] = item;
}

ASTNode* get_from_list(ASTNode *list, int index) {
    if (!list || index < 0 || index >= list->data.list.count) {
        return NULL;
    }
    return list->data.list.items[index];
}

int get_list_size(ASTNode *list) {
    return list ? list->data.list.count : 0;
}

void print_ast(ASTNode *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("PROGRAM\n");
            print_ast(node->data.program.body, depth + 1);
            break;
        case NODE_MAIN_CLASS:
            printf("MAIN_CLASS\n");
            print_ast(node->data.main_class.body, depth + 1);
            break;
        case NODE_VAR_DECL:
            printf("VAR_DECL: %s %s", 
                   node->data.var_decl.data_type,
                   node->data.var_decl.name);
            if (node->data.var_decl.is_array) printf("[]");
            printf("\n");
            if (node->data.var_decl.init_value) {
                print_ast(node->data.var_decl.init_value, depth + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n", node->data.assignment.operator);
            print_ast(node->data.assignment.left, depth + 1);
            print_ast(node->data.assignment.right, depth + 1);
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP: %s\n", node->data.binary_op.operator);
            print_ast(node->data.binary_op.left, depth + 1);
            print_ast(node->data.binary_op.right, depth + 1);
            break;
        case NODE_FUNCTION_CALL:
            printf("FUNCTION_CALL: %s\n", node->data.func_call.name);
            if (node->data.func_call.arguments) {
                print_ast(node->data.func_call.arguments, depth + 1);
            }
            break;
        case NODE_INT_LITERAL:
            printf("INT_LITERAL: %d\n", node->data.int_literal.value);
            break;
        case NODE_FLOAT_LITERAL:
            printf("FLOAT_LITERAL: %.2f\n", node->data.float_literal.value);
            break;
        case NODE_STRING_LITERAL:
            printf("STRING_LITERAL: \"%s\"\n", node->data.string_literal.value);
            break;
        case NODE_CHAR_LITERAL:
            printf("CHAR_LITERAL: '%c'\n", node->data.char_literal.value);
            break;
        case NODE_BOOLEAN_LITERAL:
            printf("BOOLEAN_LITERAL: %s\n", node->data.boolean_literal.value ? "true" : "false");
            break;
        case NODE_NULL_LITERAL:
            printf("NULL_LITERAL\n");
            break;
        case NODE_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.identifier.name);
            break;
        case NODE_IF_STMT:
            printf("IF_STMT\n");
            print_ast(node->data.if_stmt.condition, depth + 1);
            print_ast(node->data.if_stmt.then_stmt, depth + 1);
            if (node->data.if_stmt.else_stmt) {
                print_ast(node->data.if_stmt.else_stmt, depth + 1);
            }
            break;
        case NODE_STATEMENT_LIST:
        case NODE_EXPRESSION_LIST:
        case NODE_PARAMETER_LIST:
            printf("LIST (%d items)\n", node->data.list.count);
            for (int i = 0; i < node->data.list.count; i++) {
                print_ast(node->data.list.items[i], depth + 1);
            }
            break;
        default:
            printf("UNKNOWN_NODE_TYPE: %d\n", node->type);
            break;
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            free_ast(node->data.program.body);
            break;
        case NODE_MAIN_CLASS:
            free_ast(node->data.main_class.body);
            break;
        case NODE_VAR_DECL:
            free(node->data.var_decl.data_type);
            free(node->data.var_decl.name);
            free_ast(node->data.var_decl.init_value);
            break;
        case NODE_ASSIGNMENT:
            free_ast(node->data.assignment.left);
            free(node->data.assignment.operator);
            free_ast(node->data.assignment.right);
            break;
        case NODE_BINARY_OP:
            free_ast(node->data.binary_op.left);
            free(node->data.binary_op.operator);
            free_ast(node->data.binary_op.right);
            break;
        case NODE_FUNCTION_CALL:
            free(node->data.func_call.name);
            free_ast(node->data.func_call.arguments);
            break;
        case NODE_STRING_LITERAL:
            free(node->data.string_literal.value);
            break;
        case NODE_IDENTIFIER:
            free(node->data.identifier.name);
            break;
        case NODE_STATEMENT_LIST:
        case NODE_EXPRESSION_LIST:
        case NODE_PARAMETER_LIST:
            for (int i = 0; i < node->data.list.count; i++) {
                free_ast(node->data.list.items[i]);
            }
            free(node->data.list.items);
            break;
        default:
            break;
    }
    
    free(node);
}
