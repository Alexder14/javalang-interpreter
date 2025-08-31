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
extern int line_num;
extern int col_num;

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
%type <node> variable_declaration function_declaration parameter_list parameter
%type <node> assignment_statement expression_statement
%type <node> if_statement while_statement for_statement do_while_statement
%type <node> switch_statement case_list case_statement
%type <node> block_statement break_statement continue_statement return_statement
%type <node> expression binary_expression unary_expression primary_expression
%type <node> function_call argument_list
%type <node> array_access array_initialization
%type <node> type_specifier

// Precedencia de operadores (de menor a mayor)
%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQUAL NOT_EQUAL
%left LESS LESS_EQUAL GREATER GREATER_EQUAL
%left LEFT_SHIFT RIGHT_SHIFT
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT BIT_NOT INCREMENT DECREMENT
%left LPAREN LBRACKET DOT

// Símbolo de inicio
%start program

%%

// Reglas de gramática

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
    | PUBLIC STATIC VOID MAIN LPAREN STRING_TYPE LBRACKET RBRACKET IDENTIFIER RPAREN LBRACE statement_list RBRACE {
        $$ = create_main_class_node($12);
        free($9); // liberar nombre del parámetro args
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
    | do_while_statement { $$ = $1; }
    | switch_statement { $$ = $1; }
    | block_statement { $$ = $1; }
    | break_statement { $$ = $1; }
    | continue_statement { $$ = $1; }
    | return_statement { $$ = $1; }
    | function_declaration { $$ = $1; }
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
    | type_specifier LBRACKET RBRACKET IDENTIFIER SEMICOLON {
        $$ = create_var_decl_node($1, $4, NULL, true, 0);
        free($1);
        free($4);
    }
    | type_specifier LBRACKET RBRACKET IDENTIFIER ASSIGN array_initialization SEMICOLON {
        $$ = create_var_decl_node($1, $4, $6, true, 0);
        free($1);
        free($4);
    }
    | FINAL type_specifier IDENTIFIER ASSIGN expression SEMICOLON {
        ASTNode *node = create_var_decl_node($2, $3, $5, false, 0);
        // Marcar como constante (se podría añadir un campo is_const al AST)
        free($2);
        free($3);
        $$ = node;
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
    | type_specifier LBRACKET RBRACKET IDENTIFIER {
        $$ = create_parameter_node($1, $4, true);
        free($1);
        free($4);
    }
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "=", $3);
        free($1);
    }
    | IDENTIFIER PLUS_ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "+=", $3);
        free($1);
    }
    | IDENTIFIER MINUS_ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "-=", $3);
        free($1);
    }
    | IDENTIFIER MULT_ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "*=", $3);
        free($1);
    }
    | IDENTIFIER DIV_ASSIGN expression SEMICOLON {
        ASTNode *var = create_identifier_node($1);
        $$ = create_assignment_node(var, "/=", $3);
        free($1);
    }
    | array_access ASSIGN expression SEMICOLON {
        $$ = create_assignment_node($1, "=", $3);
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
    | FOR LPAREN SEMICOLON expression SEMICOLON expression RPAREN statement {
        $$ = create_for_node(NULL, $4, $6, $8);
    }
    ;

do_while_statement:
    DO statement WHILE LPAREN expression RPAREN SEMICOLON {
        // Crear un nodo do-while (podemos usar while_node con un flag)
        ASTNode *node = create_while_node($5, $2);
        // Marcar como do-while si necesario
        $$ = node;
    }
    ;

switch_statement:
    SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE {
        ASTNode *node = create_node(NODE_SWITCH_STMT, line_num, col_num);
        node->data.switch_stmt.expression = $3;
        node->data.switch_stmt.cases = $6;
        $$ = node;
    }
    ;

case_list:
    case_statement {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | case_list case_statement {
        add_to_list($1, $2);
        $$ = $1;
    }
    ;

case_statement:
    CASE primary_expression COLON statement_list {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = $2;
        node->data.case_stmt.statements = $4;
        $$ = node;
    }
    | DEFAULT COLON statement_list {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = NULL; // default case
        node->data.case_stmt.statements = $3;
        $$ = node;
    }
    ;

block_statement:
    LBRACE statement_list RBRACE {
        $$ = create_block_node();
        // Convertir lista en bloque
        for (int i = 0; i < get_list_size($2); i++) {
            ASTNode *stmt = get_from_list($2, i);
            add_to_list($$, stmt);
        }
    }
    ;

break_statement:
    BREAK SEMICOLON {
        ASTNode *node = create_node(NODE_BREAK_STMT, line_num, col_num);
        $$ = node;
    }
    ;

continue_statement:
    CONTINUE SEMICOLON {
        ASTNode *node = create_node(NODE_CONTINUE_STMT, line_num, col_num);
        $$ = node;
    }
    ;

return_statement:
    RETURN SEMICOLON {
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

expression:
    binary_expression { $$ = $1; }
    | unary_expression { $$ = $1; }
    | primary_expression { $$ = $1; }
    ;

binary_expression:
    expression PLUS expression {
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
    | expression MODULO expression {
        $$ = create_binary_op_node("%", $1, $3);
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
    | expression LESS_EQUAL expression {
        $$ = create_binary_op_node("<=", $1, $3);
    }
    | expression GREATER expression {
        $$ = create_binary_op_node(">", $1, $3);
    }
    | expression GREATER_EQUAL expression {
        $$ = create_binary_op_node(">=", $1, $3);
    }
    | expression AND expression {
        $$ = create_binary_op_node("&&", $1, $3);
    }
    | expression OR expression {
        $$ = create_binary_op_node("||", $1, $3);
    }
    | expression BIT_AND expression {
        $$ = create_binary_op_node("&", $1, $3);
    }
    | expression BIT_OR expression {
        $$ = create_binary_op_node("|", $1, $3);
    }
    | expression BIT_XOR expression {
        $$ = create_binary_op_node("^", $1, $3);
    }
    ;

unary_expression:
    NOT expression {
        $$ = create_unary_op_node("!", $2, true);
    }
    | BIT_NOT expression {
        $$ = create_unary_op_node("~", $2, true);
    }
    | MINUS expression {
        $$ = create_unary_op_node("-", $2, true);
    }
    | PLUS expression {
        $$ = create_unary_op_node("+", $2, true);
    }
    | INCREMENT IDENTIFIER {
        ASTNode *var = create_identifier_node($2);
        $$ = create_unary_op_node("++", var, true);
        free($2);
    }
    | DECREMENT IDENTIFIER {
        ASTNode *var = create_identifier_node($2);
        $$ = create_unary_op_node("--", var, true);
        free($2);
    }
    | IDENTIFIER INCREMENT {
        ASTNode *var = create_identifier_node($1);
        $$ = create_unary_op_node("++", var, false);
        free($1);
    }
    | IDENTIFIER DECREMENT {
        ASTNode *var = create_identifier_node($1);
        $$ = create_unary_op_node("--", var, false);
        free($1);
    }
    ;

primary_expression:
    LPAREN expression RPAREN {
        $$ = $2;
    }
    | IDENTIFIER {
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
    | array_access { $$ = $1; }
    | array_initialization { $$ = $1; }
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

array_access:
    IDENTIFIER LBRACKET expression RBRACKET {
        ASTNode *array = create_identifier_node($1);
        $$ = create_array_access_node(array, $3);
        free($1);
    }
    ;

array_initialization:
    NEW type_specifier LBRACKET expression RBRACKET {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = strdup($2);
        node->data.array_init.size = $4;
        node->data.array_init.values = NULL;
        free($2);
        $$ = node;
    }
    | LBRACE argument_list RBRACE {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = $2;
        $$ = node;
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
        printf("✅ Análisis sintáctico exitoso!\n\n");
        
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
        print_errors();
    }
    
    fclose(file);
    
    if (ast_root) {
        free_ast(ast_root);
    }
    
    return has_syntax_errors ? 1 : 0;
}
#endif