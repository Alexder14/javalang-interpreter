#!/bin/bash

echo "🔧 SOLUCIONANDO DEFINICIONES MÚLTIPLES - SOLUCIÓN DEFINITIVA"
echo "=========================================================="

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
mkdir -p backup_final
cp include/common.h backup_final/
cp include/ast.h backup_final/
cp parser/parser.y backup_final/
print_ok "Backup en backup_final/"

print_step "2. Corrigiendo include/common.h (sin _GNU_SOURCE redundante)..."
cat > include/common.h << 'EOF'
#ifndef COMMON_H
#define COMMON_H

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

// SOLO DECLARACIONES EXTERN (no definiciones)
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

print_step "3. Corrigiendo include/ast.h (sin _GNU_SOURCE redundante)..."
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

// SOLO DECLARACIONES EXTERN (no definiciones)
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

print_step "4. Corrigiendo parser/parser.y (sin definiciones ni _GNU_SOURCE redundante)..."
cat > parser/parser.y << 'EOF'
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "ast.h"

// Funciones externas
extern int yylex();
extern FILE *yyin;

// Función de error
void yyerror(const char *s);

// SOLO DECLARACIONES EXTERN (no definiciones)
// Las variables ya están declaradas en ast.h como extern
// Las definiciones están SOLO en ast.c
%}

// Definir tipos de valores
%union {
    int int_val;
    float float_val;
    char char_val;
    char *str_val;
    struct ASTNode *node;
    bool bool_val;
}

// Tokens del lexer
%token <str_val> IDENTIFIER STRING_LITERAL
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <char_val> CHAR_LITERAL
%token <bool_val> TRUE FALSE

// Palabras reservadas
%token PUBLIC PRIVATE PROTECTED STATIC FINAL VOID MAIN
%token INT FLOAT DOUBLE BOOLEAN CHAR STRING_TYPE
%token IF ELSE SWITCH CASE DEFAULT WHILE FOR DO
%token BREAK CONTINUE RETURN
%token NULL_VAL NEW THIS

// Operadores
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token INCREMENT DECREMENT
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token EQUAL NOT_EQUAL LESS LESS_EQUAL GREATER GREATER_EQUAL
%token AND OR NOT
%token BIT_AND BIT_OR BIT_XOR BIT_NOT LEFT_SHIFT RIGHT_SHIFT

// Delimitadores
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA DOT COLON QUESTION

// Funciones embebidas
%token PRINTLN PRINT PARSE_INT PARSE_FLOAT PARSE_DOUBLE
%token VALUE_OF STRING_JOIN ARRAY_INDEX_OF

// Tipos de nodos no terminales
%type <node> program main_class
%type <node> statement_list statement
%type <node> variable_declaration function_declaration parameter_list parameter
%type <node> assignment_statement expression_statement
%type <node> if_statement while_statement for_statement
%type <node> block_statement
%type <node> expression primary_expression
%type <node> function_call argument_list
%type <str_val> type_specifier

// Precedencia de operadores
%right ASSIGN
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%left LPAREN LBRACKET

%start program

%%

program:
    main_class {
        ast_root = create_program_node($1);
        $$ = ast_root;
    }
    ;

main_class:
    PUBLIC STATIC VOID MAIN LPAREN RPAREN LBRACE statement_list RBRACE {
        $$ = create_main_class_node($8);
    }
    ;

statement_list:
    /* empty */ {
        $$ = create_list_node();
    }
    | statement_list statement {
        if ($2 != NULL) {
            add_to_list($1, $2);
        }
        $$ = $1;
    }
    ;

statement:
    variable_declaration { $$ = $1; }
    | assignment_statement { $$ = $1; }
    | expression_statement { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    | block_statement { $$ = $1; }
    | function_declaration { $$ = $1; }
    | BREAK SEMICOLON { 
        $$ = create_node(NODE_BREAK_STMT, line_num, col_num);
    }
    | CONTINUE SEMICOLON { 
        $$ = create_node(NODE_CONTINUE_STMT, line_num, col_num);
    }
    | RETURN SEMICOLON { 
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = NULL;
        $$ = node;
    }
    | RETURN expression SEMICOLON { 
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = $2;
        $$ = node;
    }
    ;

variable_declaration:
    type_specifier IDENTIFIER SEMICOLON {
        $$ = create_var_decl_node($1, $2, NULL, false, 0);
        free($1);
        free($2);
    }
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = create_var_decl_node($1, $2, $4, false, 0);
        free($1);
        free($2);
    }
    ;

function_declaration:
    type_specifier IDENTIFIER LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
        $$ = create_function_decl_node($1, $2, $4, $7);
        free($1);
        free($2);
    }
    | type_specifier IDENTIFIER LPAREN RPAREN LBRACE statement_list RBRACE {
        $$ = create_function_decl_node($1, $2, NULL, $6);
        free($1);
        free($2);
    }
    ;

parameter_list:
    parameter {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | parameter_list COMMA parameter {
        add_to_list($1, $3);
        $$ = $1;
    }
    ;

parameter:
    type_specifier IDENTIFIER {
        $$ = create_parameter_node($1, $2, false);
        free($1);
        free($2);
    }
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "=", $3);
        free($1);
    }
    ;

expression_statement:
    expression SEMICOLON { $$ = $1; }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = create_if_node($3, $5, NULL);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_if_node($3, $5, $7);
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = create_while_node($3, $5);
    }
    ;

for_statement:
    FOR LPAREN variable_declaration expression SEMICOLON expression RPAREN statement {
        $$ = create_for_node($3, $4, $6, $8);
    }
    | FOR LPAREN assignment_statement expression SEMICOLON expression RPAREN statement {
        $$ = create_for_node($3, $4, $6, $8);
    }
    ;

block_statement:
    LBRACE statement_list RBRACE {
        $$ = $2;
    }
    ;

expression:
    primary_expression { $$ = $1; }
    | expression PLUS expression {
        $$ = create_binary_op_node("+", $1, $3);
    }
    | expression MINUS expression {
        $$ = create_binary_op_node("-", $1, $3);
    }
    | expression MULTIPLY expression {
        $$ = create_binary_op_node("*", $1, $3);
    }
    | expression DIVIDE expression {
        $$ = create_binary_op_node("/", $1, $3);
    }
    | expression EQUAL expression {
        $$ = create_binary_op_node("==", $1, $3);
    }
    | expression NOT_EQUAL expression {
        $$ = create_binary_op_node("!=", $1, $3);
    }
    | expression LESS expression {
        $$ = create_binary_op_node("<", $1, $3);
    }
    | expression GREATER expression {
        $$ = create_binary_op_node(">", $1, $3);
    }
    | expression AND expression {
        $$ = create_binary_op_node("&&", $1, $3);
    }
    | expression OR expression {
        $$ = create_binary_op_node("||", $1, $3);
    }
    | NOT expression {
        $$ = create_unary_op_node("!", $2, true);
    }
    | MINUS expression {
        $$ = create_unary_op_node("-", $2, true);
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    ;

primary_expression:
    IDENTIFIER {
        $$ = create_identifier_node($1);
        free($1);
    }
    | INT_LITERAL {
        $$ = create_int_literal_node($1);
    }
    | FLOAT_LITERAL {
        $$ = create_float_literal_node($1);
    }
    | STRING_LITERAL {
        $$ = create_string_literal_node($1);
        free($1);
    }
    | CHAR_LITERAL {
        $$ = create_char_literal_node($1);
    }
    | TRUE {
        $$ = create_boolean_literal_node(true);
    }
    | FALSE {
        $$ = create_boolean_literal_node(false);
    }
    | NULL_VAL {
        $$ = create_null_literal_node();
    }
    | function_call { $$ = $1; }
    ;

function_call:
    PRINTLN LPAREN argument_list RPAREN {
        $$ = create_function_call_node("System.out.println", $3);
    }
    | PRINTLN LPAREN RPAREN {
        $$ = create_function_call_node("System.out.println", NULL);
    }
    | IDENTIFIER LPAREN argument_list RPAREN {
        $$ = create_function_call_node($1, $3);
        free($1);
    }
    | IDENTIFIER LPAREN RPAREN {
        $$ = create_function_call_node($1, NULL);
        free($1);
    }
    ;

argument_list:
    expression {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | argument_list COMMA expression {
        add_to_list($1, $3);
        $$ = $1;
    }
    ;

type_specifier:
    INT { $$ = strdup("int"); }
    | FLOAT { $$ = strdup("float"); }
    | DOUBLE { $$ = strdup("double"); }
    | BOOLEAN { $$ = strdup("boolean"); }
    | CHAR { $$ = strdup("char"); }
    | STRING_TYPE { $$ = strdup("String"); }
    | VOID { $$ = strdup("void"); }
    ;

%%

void yyerror(const char *s) {
    has_syntax_errors = true;
    add_error(ERROR_SYNTACTIC, s, "Global", line_num, col_num);
    fprintf(stderr, "Error sintáctico en línea %d, columna %d: %s\n", line_num, col_num, s);
}

#ifdef TEST_PARSER
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.usl>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error al abrir archivo");
        return 1;
    }

    yyin = file;
    line_num = 1;
    col_num = 1;
    
    printf("🔍 Analizando archivo: %s\n", argv[1]);
    printf("==============================\n");

    if (yyparse() == 0 && !has_syntax_errors) {
        printf("✅ ¡ANÁLISIS SINTÁCTICO EXITOSO!\n\n");
        
        if (ast_root) {
            printf("🌳 Árbol de Sintaxis Abstracta:\n");
            printf("================================\n");
            print_ast(ast_root, 0);
            printf("\n");
        }
        
        printf("📊 Estadísticas:\n");
        printf("- Sin errores sintácticos\n");
        printf("- AST generado correctamente\n");
        
    } else {
        printf("❌ Se encontraron errores sintácticos\n");
        if (error_count > 0) {
            print_errors();
        }
    }
    
    fclose(file);
    
    if (ast_root) {
        free_ast(ast_root);
    }
    
    return has_syntax_errors ? 1 : 0;
}
#endif
EOF

print_step "5. Corrigiendo lexer/lexer.l (sin _GNU_SOURCE redundante)..."
cat > lexer/lexer.l << 'EOF'
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parser.tab.h"

/* Funciones auxiliares */
void update_column();
void print_token(const char* token_type, const char* lexeme);

/* Contador de tokens para estadísticas */
int token_count = 0;

/* Función para actualizar columna */
void update_column() {
    col_num += yyleng;
}

/* Función para imprimir tokens (solo en modo debug) */
void print_token(const char* token_type, const char* lexeme) {
    #ifdef DEBUG_LEXER
    printf("TOKEN: %-15s | LEXEME: %-20s | LINE: %d | COL: %d\n", 
           token_type, lexeme, line_num, col_num - yyleng);
    #endif
    token_count++;
}
%}

%option noyywrap
%option yylineno

/* Expresiones regulares básicas */
DIGIT       [0-9]
LETTER      [a-zA-Z]
UNDERSCORE  _
ID_START    ({LETTER}|{UNDERSCORE})
ID_CHAR     ({LETTER}|{DIGIT}|{UNDERSCORE})
IDENTIFIER  {ID_START}{ID_CHAR}*

/* Literales numéricos */
INTEGER     {DIGIT}+
DECIMAL     {DIGIT}+\.{DIGIT}+
FLOAT       {DECIMAL}[fF]?

/* Literales de caracteres y cadenas */
CHAR_CONTENT    [^'\\]|\\['"\\nrtbf]|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2}
CHAR_LITERAL    '{CHAR_CONTENT}'
STRING_CONTENT  [^"\\]|\\['"\\nrtbf]|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2}
STRING_LITERAL  \"{STRING_CONTENT}*\"

/* Espacios en blanco */
WHITESPACE  [ \t]+
NEWLINE     \r?\n

/* Comentarios */
LINE_COMMENT        \/\/.*
BLOCK_COMMENT_START \/\*

%%

    /* === PALABRAS RESERVADAS === */
"public"        { update_column(); return PUBLIC; }
"static"        { update_column(); return STATIC; }
"void"          { update_column(); return VOID; }
"main"          { update_column(); return MAIN; }
"int"           { update_column(); return INT; }
"float"         { update_column(); return FLOAT; }
"double"        { update_column(); return DOUBLE; }
"boolean"       { update_column(); return BOOLEAN; }
"char"          { update_column(); return CHAR; }
"String"        { update_column(); return STRING_TYPE; }
"if"            { update_column(); return IF; }
"else"          { update_column(); return ELSE; }
"while"         { update_column(); return WHILE; }
"for"           { update_column(); return FOR; }
"break"         { update_column(); return BREAK; }
"continue"      { update_column(); return CONTINUE; }
"return"        { update_column(); return RETURN; }
"null"          { update_column(); return NULL_VAL; }
"true"          { update_column(); yylval.bool_val = true; return TRUE; }
"false"         { update_column(); yylval.bool_val = false; return FALSE; }

    /* === OPERADORES === */
"+"             { update_column(); return PLUS; }
"-"             { update_column(); return MINUS; }
"*"             { update_column(); return MULTIPLY; }
"/"             { update_column(); return DIVIDE; }
"%"             { update_column(); return MODULO; }
"="             { update_column(); return ASSIGN; }
"=="            { update_column(); return EQUAL; }
"!="            { update_column(); return NOT_EQUAL; }
"<"             { update_column(); return LESS; }
">"             { update_column(); return GREATER; }
"<="            { update_column(); return LESS_EQUAL; }
">="            { update_column(); return GREATER_EQUAL; }
"&&"            { update_column(); return AND; }
"||"            { update_column(); return OR; }
"!"             { update_column(); return NOT; }

    /* === DELIMITADORES === */
"("             { update_column(); return LPAREN; }
")"             { update_column(); return RPAREN; }
"{"             { update_column(); return LBRACE; }
"}"             { update_column(); return RBRACE; }
"["             { update_column(); return LBRACKET; }
"]"             { update_column(); return RBRACKET; }
";"             { update_column(); return SEMICOLON; }
","             { update_column(); return COMMA; }

    /* === FUNCIONES EMBEBIDAS === */
"println"       { update_column(); return PRINTLN; }

    /* === LITERALES === */
{INTEGER}       { 
                    update_column(); 
                    yylval.int_val = atoi(yytext); 
                    return INT_LITERAL; 
                }

{FLOAT}         { 
                    update_column(); 
                    yylval.float_val = atof(yytext); 
                    return FLOAT_LITERAL; 
                }

{CHAR_LITERAL}  { 
                    update_column(); 
                    yylval.char_val = yytext[1]; 
                    return CHAR_LITERAL; 
                }

{STRING_LITERAL} { 
                    update_column(); 
                    int len = strlen(yytext);
                    char *str = malloc(len - 1);
                    if (str) {
                        strncpy(str, yytext + 1, len - 2);
                        str[len - 2] = '\0';
                    }
                    yylval.str_val = str; 
                    return STRING_LITERAL; 
                }

{IDENTIFIER}    { 
                    update_column(); 
                    yylval.str_val = strdup(yytext); 
                    return IDENTIFIER; 
                }

    /* === MANEJO DE ESPACIOS Y COMENTARIOS === */
{WHITESPACE}    { col_num += yyleng; }
{NEWLINE}       { line_num++; col_num = 1; }
{LINE_COMMENT}  { col_num += yyleng; }

{BLOCK_COMMENT_START} { 
                    col_num += yyleng; 
                    int c;
                    int prev_c = 0;
                    
                    while ((c = input()) != EOF) {
                        if (c == '\n') {
                            line_num++;
                            col_num = 1;
                        } else {
                            col_num++;
                        }
                        
                        if (prev_c == '*' && c == '/') {
                            break;
                        }
                        prev_c = c;
                    }
                }

.               { 
                    update_column(); 
                    printf("ERROR: Carácter no reconocido '%c' en línea %d, columna %d\n", 
                           yytext[0], line_num, col_num - 1);
                }

%%

EOF

print_step "6. Limpiando y compilando..."
rm -f test_parser parser/parser.tab.* lexer/lex.yy.c

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

# Compilar (usando -D_GNU_SOURCE solo en la línea de comandos, sin redundancia)
CFLAGS="-DTEST_PARSER -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -std=gnu99 -Wall -g"
INCLUDES="-Iinclude -Iparser"
SOURCES="parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c"

print_step "Compilando sin redundancia de _GNU_SOURCE..."
if gcc $CFLAGS $INCLUDES -o test_parser $SOURCES -lfl 2>final_compile.log; then
    print_ok "¡COMPILACIÓN EXITOSA CON LIBFL!"
elif gcc $CFLAGS $INCLUDES -o test_parser $SOURCES 2>final_compile.log; then
    print_ok "¡COMPILACIÓN EXITOSA SIN LIBFL!"
else
    print_error "Error de compilación final"
    echo "Log de errores:"
    cat final_compile.log
    exit 1
fi

print_step "7. Probando con archivo de ejemplo..."
cat > test_success.usl << 'EOF'
public static void main() {
    int numero = 100;
    String mensaje = "¡Parser completado!";
    boolean terminado = true;
    
    println("=== PRUEBA EXITOSA ===");
    println(mensaje);
    
    if (numero > 50) {
        println("Número grande detectado");
    }
    
    if (terminado) {
        println("🎉 ¡Fase 3 finalizada con éxito!");
    }
}
EOF

if ./test_parser test_success.usl; then
    print_ok "🎉 ¡PROBLEMA COMPLETAMENTE SOLUCIONADO!"
    echo ""
    echo "✅ Definiciones múltiples: ELIMINADAS"
    echo "✅ _GNU_SOURCE redundante: CORREGIDO"  
    echo "✅ Variables extern/definiciones: ORGANIZADAS"
    echo "✅ Compilación: EXITOSA"
    echo "✅ Parser funcionando: CORRECTAMENTE"
    echo "✅ AST generado: CORRECTAMENTE"
    echo ""
    echo "🎯 ¡FASE 3 COMPLETADA AL 100%!"
    echo ""
    echo "Usa: ./test_parser archivo.usl"
else
    print_error "Prueba final falló"
    exit 1
fi

# Limpiar archivos temporales
rm -f test_success.usl final_compile.log

print_ok "¡SOLUCIÓN APLICADA EXITOSAMENTE!"
EOF