%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "common.h"

// Funciones externas
extern int yylex();
extern FILE *yyin;

// Función de error
void yyerror(const char *s);

// Variables globales
ASTNode *ast_root = NULL;
bool has_syntax_errors = false;
%}

// Definir tipos de valores
%union {
    int int_val;
    float float_val;
    char char_val;
    char *str_val;
    ASTNode *node;
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
%type <node> variable_declaration 
%type <node> assignment_statement expression_statement
%type <node> if_statement while_statement for_statement
%type <node> block_statement
%type <node> expression primary_expression
%type <node> function_call argument_list
%type <node> type_specifier

// Precedencia de operadores (de menor a mayor)
%right ASSIGN
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%left LPAREN LBRACKET

// Símbolo de inicio
%start program

%%

// Reglas de gramática simplificadas

program:
    main_class {
        ast_root = create_program_node($1);
        $$ = ast_root;
        printf("✅ Programa parseado correctamente\n");
    }
    ;

main_class:
    PUBLIC STATIC VOID MAIN LPAREN RPAREN LBRACE statement_list RBRACE {
        $$ = create_main_class_node($8);
        printf("✅ Función main parseada\n");
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
        printf("✅ Variable declarada: %s %s\n", $1, $2);
    }
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = create_var_decl_node($1, $2, $4, false, 0);
        free($1);
        free($2);
        printf("✅ Variable con inicialización: %s %s\n", $1, $2);
    }
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "=", $3);
        free($1);
        printf("✅ Asignación: %s = ...\n", $1);
    }
    ;

expression_statement:
    expression SEMICOLON { 
        $$ = $1; 
    }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = create_if_node($3, $5, NULL);
        printf("✅ Sentencia if parseada\n");
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_if_node($3, $5, $7);
        printf("✅ Sentencia if-else parseada\n");
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = create_while_node($3, $5);
        printf("✅ Bucle while parseado\n");
    }
    ;

for_statement:
    FOR LPAREN variable_declaration expression SEMICOLON expression RPAREN statement {
        $$ = create_for_node($3, $4, $6, $8);
        printf("✅ Bucle for parseado\n");
    }
    | FOR LPAREN assignment_statement expression SEMICOLON expression RPAREN statement {
        $$ = create_for_node($3, $4, $6, $8);
        printf("✅ Bucle for parseado\n");
    }
    ;

block_statement:
    LBRACE statement_list RBRACE {
        $$ = $2;
        printf("✅ Bloque parseado\n");
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
        $$ = create_function_call_node("println", $3);
        printf("✅ Llamada a println parseada\n");
    }
    | PRINTLN LPAREN RPAREN {
        $$ = create_function_call_node("println", NULL);
        printf("✅ Llamada a println() parseada\n");
    }
    | IDENTIFIER LPAREN argument_list RPAREN {
        $$ = create_function_call_node($1, $3);
        free($1);
        printf("✅ Llamada a función parseada\n");
    }
    | IDENTIFIER LPAREN RPAREN {
        $$ = create_function_call_node($1, NULL);
        free($1);
        printf("✅ Llamada a función sin argumentos parseada\n");
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
    fprintf(stderr, "❌ Error sintáctico en línea %d, columna %d: %s\n", line_num, col_num, s);
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
        printf("\n✅ ¡ANÁLISIS SINTÁCTICO EXITOSO!\n\n");
        
        if (ast_root) {
            printf("🌳 Árbol de Sintaxis Abstracta:\n");
            printf("================================\n");
            print_ast(ast_root, 0);
            printf("\n");
        }
        
        printf("📊 Estadísticas:\n");
        printf("- Sin errores sintácticos\n");
        printf("- AST generado correctamente\n");
        printf("- Archivo parseado: %s\n", argv[1]);
        
    } else {
        printf("\n❌ SE ENCONTRARON ERRORES SINTÁCTICOS\n");
        if (error_count > 0) {
            print_errors();
        }
        fclose(file);
        return 1;
    }
    
    fclose(file);
    
    if (ast_root) {
        free_ast(ast_root);
    }
    
    return 0;
}
#endif