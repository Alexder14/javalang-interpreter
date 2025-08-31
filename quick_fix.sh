#!/bin/bash

echo "🔧 SOLUCIONANDO DEFINICIONES MÚLTIPLES Y PROBLEMAS POSIX"
echo "========================================================"

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_step() { echo -e "${BLUE}$1${NC}"; }
print_ok() { echo -e "${GREEN}✅ $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }

print_step "1. Respaldando archivos actuales..."
mkdir -p backup_before_fix
cp include/common.h backup_before_fix/
cp src/common.c backup_before_fix/
cp include/ast.h backup_before_fix/
cp src/ast.c backup_before_fix/
cp lexer/lexer.l backup_before_fix/
print_ok "Backup creado en backup_before_fix/"

print_step "2. Corrigiendo include/common.h (solo declaraciones extern)..."
cat > include/common.h << 'EOF'
#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Constantes del proyecto
#define MAX_IDENTIFIER_LEN 256
#define MAX_STRING_LEN 1024
#define MAX_ERRORS 100
#define MAX_SYMBOLS 1000

// Tipos de datos del lenguaje JavaLang
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOLEAN,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_ARRAY,
    TYPE_NULL,
    TYPE_UNKNOWN
} DataType;

// Tipos de errores
typedef enum {
    ERROR_LEXICAL,
    ERROR_SYNTACTIC,
    ERROR_SEMANTIC,
    ERROR_RUNTIME
} ErrorType;

// Estructura para manejo de errores
typedef struct {
    ErrorType type;
    char message[MAX_STRING_LEN];
    char scope[MAX_IDENTIFIER_LEN];
    int line;
    int column;
} Error;

// DECLARACIONES EXTERN (no definiciones)
extern int line_num;
extern int col_num;
extern Error errors[MAX_ERRORS];
extern int error_count;
extern bool has_errors;

// Funciones utilitarias
char* data_type_to_string(DataType type);
DataType string_to_data_type(const char* str);
void add_error(ErrorType type, const char* message, const char* scope, int line, int col);
void print_errors(void);
void clear_errors(void);

#endif // COMMON_H
EOF

print_step "3. Corrigiendo src/common.c (definiciones reales)..."
cat > src/common.c << 'EOF'
#include "common.h"

// DEFINICIONES de variables globales (solo aquí)
int line_num = 1;
int col_num = 1;
Error errors[MAX_ERRORS];
int error_count = 0;
bool has_errors = false;

char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_STRING: return "String";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        case TYPE_ARRAY: return "array";
        case TYPE_NULL: return "null";
        default: return "unknown";
    }
}

DataType string_to_data_type(const char* str) {
    if (strcmp(str, "int") == 0) return TYPE_INT;
    if (strcmp(str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(str, "boolean") == 0) return TYPE_BOOLEAN;
    if (strcmp(str, "String") == 0) return TYPE_STRING;
    if (strcmp(str, "char") == 0) return TYPE_CHAR;
    if (strcmp(str, "void") == 0) return TYPE_VOID;
    return TYPE_UNKNOWN;
}

void add_error(ErrorType type, const char* message, const char* scope, int line, int col) {
    if (error_count < MAX_ERRORS) {
        errors[error_count].type = type;
        strncpy(errors[error_count].message, message, MAX_STRING_LEN - 1);
        errors[error_count].message[MAX_STRING_LEN - 1] = '\0';
        strncpy(errors[error_count].scope, scope, MAX_IDENTIFIER_LEN - 1);
        errors[error_count].scope[MAX_IDENTIFIER_LEN - 1] = '\0';
        errors[error_count].line = line;
        errors[error_count].column = col;
        error_count++;
        has_errors = true;
    }
}

void print_errors(void) {
    printf("\n=== REPORTE DE ERRORES ===\n");
    printf("No. | Descripción | Ámbito | Línea | Columna\n");
    printf("----|-------------|--------|-------|--------\n");
    
    for (int i = 0; i < error_count; i++) {
        printf("%3d | %s | %s | %5d | %7d\n",
               i + 1,
               errors[i].message,
               errors[i].scope,
               errors[i].line,
               errors[i].column);
    }
    printf("\nTotal de errores: %d\n", error_count);
}

void clear_errors(void) {
    error_count = 0;
    has_errors = false;
}
EOF

print_step "4. Corrigiendo include/ast.h (solo declaraciones extern)..."
cat > include/ast.h << 'EOF'
#ifndef AST_H
#define AST_H

#include "common.h"
#include <stdbool.h>

// Tipos de nodos del AST
typedef enum {
    NODE_PROGRAM,
    NODE_MAIN_CLASS,
    NODE_VAR_DECL,
    NODE_CONST_DECL,
    NODE_FUNCTION_DECL,
    NODE_PARAMETER,
    NODE_BLOCK,
    NODE_EXPRESSION_STMT,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_DO_WHILE_STMT,
    NODE_SWITCH_STMT,
    NODE_CASE_STMT,
    NODE_BREAK_STMT,
    NODE_CONTINUE_STMT,
    NODE_RETURN_STMT,
    NODE_ASSIGNMENT,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNCTION_CALL,
    NODE_ARRAY_ACCESS,
    NODE_ARRAY_INIT,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_STRING_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_BOOLEAN_LITERAL,
    NODE_NULL_LITERAL,
    NODE_IDENTIFIER,
    NODE_TYPE,
    NODE_STATEMENT_LIST,
    NODE_EXPRESSION_LIST,
    NODE_PARAMETER_LIST
} NodeType;

// Forward declaration
struct ASTNode;

typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    
    union {
        struct { struct ASTNode *body; } program;
        struct { struct ASTNode *body; } main_class;
        struct {
            char *data_type;
            char *name;
            struct ASTNode *init_value;
            bool is_array;
            int array_size;
        } var_decl;
        struct {
            char *return_type;
            char *name;
            struct ASTNode *parameters;
            struct ASTNode *body;
        } func_decl;
        struct {
            char *data_type;
            char *name;
            bool is_array;
        } parameter;
        struct {
            struct ASTNode **statements;
            int count;
            int capacity;
        } block;
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_stmt;
            struct ASTNode *else_stmt;
        } if_stmt;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;
        struct {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_stmt;
        struct {
            struct ASTNode *expression;
            struct ASTNode *cases;
        } switch_stmt;
        struct {
            struct ASTNode *value;
            struct ASTNode *statements;
        } case_stmt;
        struct {
            struct ASTNode *value;
        } return_stmt;
        struct {
            struct ASTNode *left;
            char *operator;
            struct ASTNode *right;
        } assignment;
        struct {
            char *operator;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        struct {
            char *operator;
            struct ASTNode *operand;
            bool is_prefix;
        } unary_op;
        struct {
            char *name;
            struct ASTNode *arguments;
        } func_call;
        struct {
            struct ASTNode *array;
            struct ASTNode *index;
        } array_access;
        struct {
            char *type;
            struct ASTNode *size;
            struct ASTNode *values;
        } array_init;
        struct { int value; } int_literal;
        struct { float value; } float_literal;
        struct { char *value; } string_literal;
        struct { char value; } char_literal;
        struct { bool value; } boolean_literal;
        struct { char *name; } identifier;
        struct {
            char *name;
            bool is_array;
            int array_dimensions;
        } type;
        struct {
            struct ASTNode **items;
            int count;
            int capacity;
        } list;
    } data;
    
    struct ASTNode *next;
} ASTNode;

// DECLARACIONES EXTERN (no definiciones)
extern ASTNode *ast_root;
extern bool has_syntax_errors;

// Prototipos de funciones
ASTNode* create_node(NodeType type, int line, int col);
ASTNode* create_program_node(ASTNode *body);
ASTNode* create_main_class_node(ASTNode *body);
ASTNode* create_var_decl_node(const char *type, const char *name, ASTNode *init, bool is_array, int array_size);
ASTNode* create_function_decl_node(const char *return_type, const char *name, ASTNode *params, ASTNode *body);
ASTNode* create_parameter_node(const char *type, const char *name, bool is_array);
ASTNode* create_block_node(void);
ASTNode* create_if_node(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt);
ASTNode* create_while_node(ASTNode *condition, ASTNode *body);
ASTNode* create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body);
ASTNode* create_assignment_node(ASTNode *left, const char *op, ASTNode *right);
ASTNode* create_binary_op_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode* create_unary_op_node(const char *op, ASTNode *operand, bool is_prefix);
ASTNode* create_function_call_node(const char *name, ASTNode *args);
ASTNode* create_array_access_node(ASTNode *array, ASTNode *index);
ASTNode* create_int_literal_node(int value);
ASTNode* create_float_literal_node(float value);
ASTNode* create_string_literal_node(const char *value);
ASTNode* create_char_literal_node(char value);
ASTNode* create_boolean_literal_node(bool value);
ASTNode* create_null_literal_node(void);
ASTNode* create_identifier_node(const char *name);
ASTNode* create_list_node(void);

void add_to_list(ASTNode *list, ASTNode *item);
ASTNode* get_from_list(ASTNode *list, int index);
int get_list_size(ASTNode *list);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

#endif // AST_H
EOF

print_step "5. Corrigiendo src/ast.c (definiciones reales de variables AST)..."
cat > src/ast.c << 'EOF'
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
EOF

print_step "6. Corrigiendo lexer/lexer.l (remover definiciones duplicadas)..."
# Agregar define al inicio y remover definiciones de variables
sed -i '1i#define _GNU_SOURCE' lexer/lexer.l
sed -i 's/int line_num = 1;//g' lexer/lexer.l
sed -i 's/int col_num = 1;//g' lexer/lexer.l

print_step "7. Limpiando archivos generados anteriormente..."
rm -f test_parser parser/parser.tab.* lexer/lex.yy.c

print_step "8. Compilando con flags correctos para POSIX..."
# Flags específicos para solucionar strdup y fileno
CFLAGS="-DTEST_PARSER -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -std=gnu99 -Wall -g"
INCLUDES="-Iinclude -Iparser"
SOURCES="parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c"

# Generar parser
if bison -d -o parser/parser.tab.c parser/parser.y; then
    print_ok "Parser generado"
else
    print_error "Error generando parser"
    exit 1
fi

# Generar lexer
if flex -o lexer/lex.yy.c lexer/lexer.l; then
    print_ok "Lexer generado"
else
    print_error "Error generando lexer"
    exit 1
fi

# Compilar
echo "Comando: gcc $CFLAGS $INCLUDES -o test_parser $SOURCES -lfl"
if gcc $CFLAGS $INCLUDES -o test_parser $SOURCES -lfl 2>compile.log; then
    print_ok "¡COMPILACIÓN EXITOSA CON LIBFL!"
elif gcc $CFLAGS $INCLUDES -o test_parser $SOURCES 2>compile.log; then
    print_ok "¡COMPILACIÓN EXITOSA SIN LIBFL!"
else
    print_error "Error de compilación"
    echo "Log de errores:"
    cat compile.log
    exit 1
fi

print_step "9. Creando archivo de prueba..."
cat > test_fix.usl << 'EOF'
public static void main() {
    int numero = 42;
    String texto = "Hola mundo";
    boolean flag = true;
    
    println("Prueba de compilación exitosa!");
    println(texto);
    
    if (numero > 0) {
        println("El número es positivo");
    }
}
EOF

print_step "10. Probando compilación..."
if ./test_parser test_fix.usl; then
    print_ok "¡PRUEBA EXITOSA!"
    echo ""
    echo "🎉 PROBLEMA SOLUCIONADO COMPLETAMENTE"
    echo ""
    echo "✅ Definiciones múltiples: CORREGIDAS"
    echo "✅ Problemas POSIX/GNU: CORREGIDOS" 
    echo "✅ Compilación: EXITOSA"
    echo "✅ AST: GENERADO CORRECTAMENTE"
    echo ""
    echo "🎯 Ahora puedes usar:"
    echo "   ./test_parser archivo.usl"
else
    print_error "La prueba falló"
    exit 1
fi

# Limpiar archivos temporales
rm -f compile.log test_fix.usl

print_ok "¡SOLUCIÓN APLICADA CON ÉXITO!"
EOF

print_ok "Script de solución creado"

print_step "Ejecutando solución automática..."
chmod +x quick_fix.sh
./quick_fix.sh