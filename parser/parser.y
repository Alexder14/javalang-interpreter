%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
extern ASTNode *ast_root;
%}

%locations

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
%token AND_ASSIGN OR_ASSIGN XOR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
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
%type <node> top_level_list top_level_item
%type <node> program main_class
%type <node> statement_list statement
%type <node> variable_declaration function_declaration
%type <node> assignment_statement expression_statement
%type <node> for_update
%type <node> if_statement while_statement for_statement do_while_statement
%type <node> switch_statement case_list case_statement
%type <node> block_statement
%type <node> expression primary_expression
%type <node> function_call argument_list
%type <node> array_access array_initialization
%type <node> parameter_list parameter
%type <str_val> type_specifier assignment_operator
%type <int_val> dims
%type <node> array_value dim_exprs array_literal element_list element

// Precedencia de operadores (de menor a mayor)
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
%right NOT BIT_NOT UNARY_MINUS UNARY_PLUS
%right INCREMENT DECREMENT
%left DOT LBRACKET
%left LPAREN

%code {
    /* Copia la posición (línea/columna de inicio) de un símbolo de la gramática al nodo */
    static ASTNode *at(ASTNode *n, YYLTYPE loc) {
        if (n) { n->line = loc.first_line; n->column = loc.first_column; }
        return n;
    }
}

// Símbolo inicial
%start program

%%

program:
    top_level_list {
        ast_root = create_program_node($1);
        $$ = ast_root;
    }
    ;

top_level_list:
    top_level_item {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | top_level_list top_level_item {
        add_to_list($1, $2);
        $$ = $1;
    }
    ;

top_level_item:
    main_class { $$ = $1; }
    | function_declaration { $$ = $1; }
    ;

main_class:
    PUBLIC STATIC VOID MAIN LPAREN RPAREN block_statement {
        $$ = at(create_main_class_node($7), @$);
    }
    | PUBLIC STATIC VOID MAIN LPAREN STRING_TYPE LBRACKET RBRACKET IDENTIFIER RPAREN block_statement {
        $$ = at(create_main_class_node($11), @$);
        free($9); // Liberar nombre del parámetro args
    }
    ;

function_declaration:
    PUBLIC STATIC type_specifier IDENTIFIER LPAREN parameter_list RPAREN block_statement {
        $$ = at(create_function_decl_node($3, $4, $6, $8), @4);
        free($3);
        free($4);
    }
    | PUBLIC STATIC type_specifier IDENTIFIER LPAREN RPAREN block_statement {
        $$ = at(create_function_decl_node($3, $4, NULL, $7), @4);
        free($3);
        free($4);
    }
    | PUBLIC type_specifier IDENTIFIER LPAREN parameter_list RPAREN block_statement {
        $$ = at(create_function_decl_node($2, $3, $5, $7), @3);
        free($2);
        free($3);
    }
    | PUBLIC type_specifier IDENTIFIER LPAREN RPAREN block_statement {
        $$ = at(create_function_decl_node($2, $3, NULL, $6), @3);
        free($2);
        free($3);
    }
    | type_specifier IDENTIFIER LPAREN parameter_list RPAREN block_statement {
        $$ = at(create_function_decl_node($1, $2, $4, $6), @2);
        free($1);
        free($2);
    }
    | type_specifier IDENTIFIER LPAREN RPAREN block_statement {
        $$ = at(create_function_decl_node($1, $2, NULL, $5), @2);
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
        $$ = at(create_parameter_node($1, $2, false), @2);
        free($1);
        free($2);
    }
    | type_specifier dims IDENTIFIER {
        $$ = at(create_parameter_node($1, $3, true), @3);
        $$->data.parameter.dims = $2;
        free($1);
        free($3);
    }
    | type_specifier IDENTIFIER dims {
        $$ = at(create_parameter_node($1, $2, true), @2);
        $$->data.parameter.dims = $3;
        free($1);
        free($2);
    }
    ;

block_statement:
    LBRACE statement_list RBRACE {
        $$ = $2;
    }
    | LBRACE RBRACE {
        $$ = at(create_list_node(), @$);
    }
    ;

statement_list:
    statement {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | statement_list statement {
        add_to_list($1, $2);
        $$ = $1;
    }
    | statement_list function_declaration {
        add_to_list($1, $2);
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
    | BREAK SEMICOLON {
        $$ = at(create_node(NODE_BREAK_STMT, line_num, col_num), @$);
    }
    | CONTINUE SEMICOLON {
        $$ = at(create_node(NODE_CONTINUE_STMT, line_num, col_num), @$);
    }
    | RETURN SEMICOLON {
        ASTNode *node = at(create_node(NODE_RETURN_STMT, line_num, col_num), @$);
        node->data.return_stmt.value = NULL;
        $$ = node;
    }
    | RETURN expression SEMICOLON {
        ASTNode *node = at(create_node(NODE_RETURN_STMT, line_num, col_num), @$);
        node->data.return_stmt.value = $2;
        $$ = node;
    }
    ;

variable_declaration:
    type_specifier IDENTIFIER SEMICOLON {
        $$ = at(create_var_decl_node($1, $2, NULL, false, 0), @2);
        free($1);
        free($2);
    }
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = at(create_var_decl_node($1, $2, $4, false, 0), @2);
        free($1);
        free($2);
    }
    | type_specifier dims IDENTIFIER SEMICOLON {
        $$ = at(create_var_decl_node($1, $3, NULL, true, $2), @3);
        free($1);
        free($3);
    }
    | type_specifier dims IDENTIFIER ASSIGN array_value SEMICOLON {
        $$ = at(create_var_decl_node($1, $3, $5, true, $2), @3);
        free($1);
        free($3);
    }
    | type_specifier IDENTIFIER dims SEMICOLON {
        $$ = at(create_var_decl_node($1, $2, NULL, true, $3), @2);
        free($1);
        free($2);
    }
    | type_specifier IDENTIFIER dims ASSIGN array_value SEMICOLON {
        $$ = at(create_var_decl_node($1, $2, $5, true, $3), @2);
        free($1);
        free($2);
    }
    | FINAL type_specifier IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = at(create_var_decl_node($2, $3, $5, false, 0), @3);
        $$->data.var_decl.is_const = true;
        free($2);
        free($3);
    }
    ;

assignment_statement:
    IDENTIFIER assignment_operator expression SEMICOLON {
        ASTNode *left = at(create_identifier_node($1), @$);
        $$ = at(create_assignment_node(left, $2, $3), @$);
        free($1);
        free($2);
    }
    | array_access assignment_operator expression SEMICOLON {
        $$ = at(create_assignment_node($1, $2, $3), @$);
        free($2);
    }
    ;

assignment_operator:
    ASSIGN { $$ = strdup("="); }
    | PLUS_ASSIGN { $$ = strdup("+="); }
    | MINUS_ASSIGN { $$ = strdup("-="); }
    | MULT_ASSIGN { $$ = strdup("*="); }
    | DIV_ASSIGN { $$ = strdup("/="); }
    | MOD_ASSIGN { $$ = strdup("%="); }
    | AND_ASSIGN { $$ = strdup("&="); }
    | OR_ASSIGN { $$ = strdup("|="); }
    | XOR_ASSIGN { $$ = strdup("^="); }
    | LSHIFT_ASSIGN { $$ = strdup("<<="); }
    | RSHIFT_ASSIGN { $$ = strdup(">>="); }
    ;

expression_statement:
    expression SEMICOLON {
        ASTNode *node = at(create_node(NODE_EXPRESSION_STMT, line_num, col_num), @$);
        node->data.program.body = $1; // Reutilizar campo para expresión
        $$ = node;
    }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = at(create_if_node($3, $5, NULL), @$);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = at(create_if_node($3, $5, $7), @$);
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = at(create_while_node($3, $5), @$);
    }
    ;

for_statement:
    FOR LPAREN assignment_statement expression SEMICOLON for_update RPAREN statement {
        $$ = at(create_for_node($3, $4, $6, $8), @$);
    }
    | FOR LPAREN variable_declaration expression SEMICOLON for_update RPAREN statement {
        $$ = at(create_for_node($3, $4, $6, $8), @$);
    }
    | FOR LPAREN type_specifier IDENTIFIER COLON expression RPAREN statement {
        $$ = at(create_foreach_node($3, $4, 0, $6, $8), @$);
        free($3);
        free($4);
    }
    | FOR LPAREN type_specifier dims IDENTIFIER COLON expression RPAREN statement {
        $$ = at(create_foreach_node($3, $5, $4, $7, $9), @$);
        free($3);
        free($5);
    }
    ;

for_update:
    IDENTIFIER assignment_operator expression {
        ASTNode *left = at(create_identifier_node($1), @$);
        $$ = at(create_assignment_node(left, $2, $3), @$);
        free($1);
        free($2);
    }
    | array_access assignment_operator expression {
        $$ = at(create_assignment_node($1, $2, $3), @$);
        free($2);
    }
    | expression { $$ = $1; }
    ;

do_while_statement:
    DO statement WHILE LPAREN expression RPAREN SEMICOLON {
        ASTNode *node = at(create_node(NODE_DO_WHILE_STMT, line_num, col_num), @$);
        node->data.while_stmt.body = $2;
        node->data.while_stmt.condition = $5;
        $$ = node;
    }
    ;

switch_statement:
    SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE {
        ASTNode *node = at(create_node(NODE_SWITCH_STMT, line_num, col_num), @$);
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
    CASE expression COLON statement_list {
        ASTNode *node = at(create_node(NODE_CASE_STMT, line_num, col_num), @$);
        node->data.case_stmt.value = $2;
        node->data.case_stmt.statements = $4;
        $$ = node;
    }
    | DEFAULT COLON statement_list {
        ASTNode *node = at(create_node(NODE_CASE_STMT, line_num, col_num), @$);
        node->data.case_stmt.value = NULL;  // NULL indica default
        node->data.case_stmt.statements = $3;
        $$ = node;
    }
    ;

expression:
    primary_expression { $$ = $1; }
    | expression PLUS expression {
        $$ = at(create_binary_op_node("+", $1, $3), @$);
    }
    | expression MINUS expression {
        $$ = at(create_binary_op_node("-", $1, $3), @$);
    }
    | expression MULTIPLY expression {
        $$ = at(create_binary_op_node("*", $1, $3), @$);
    }
    | expression DIVIDE expression {
        $$ = at(create_binary_op_node("/", $1, $3), @$);
    }
    | expression MODULO expression {
        $$ = at(create_binary_op_node("%", $1, $3), @$);
    }
    | expression EQUAL expression {
        $$ = at(create_binary_op_node("==", $1, $3), @$);
    }
    | expression NOT_EQUAL expression {
        $$ = at(create_binary_op_node("!=", $1, $3), @$);
    }
    | expression LESS expression {
        $$ = at(create_binary_op_node("<", $1, $3), @$);
    }
    | expression LESS_EQUAL expression {
        $$ = at(create_binary_op_node("<=", $1, $3), @$);
    }
    | expression GREATER expression {
        $$ = at(create_binary_op_node(">", $1, $3), @$);
    }
    | expression GREATER_EQUAL expression {
        $$ = at(create_binary_op_node(">=", $1, $3), @$);
    }
    | expression AND expression {
        $$ = at(create_binary_op_node("&&", $1, $3), @$);
    }
    | expression OR expression {
        $$ = at(create_binary_op_node("||", $1, $3), @$);
    }
    | expression BIT_AND expression {
        $$ = at(create_binary_op_node("&", $1, $3), @$);
    }
    | expression BIT_OR expression {
        $$ = at(create_binary_op_node("|", $1, $3), @$);
    }
    | expression BIT_XOR expression {
        $$ = at(create_binary_op_node("^", $1, $3), @$);
    }
    | expression LEFT_SHIFT expression {
        $$ = at(create_binary_op_node("<<", $1, $3), @$);
    }
    | expression RIGHT_SHIFT expression {
        $$ = at(create_binary_op_node(">>", $1, $3), @$);
    }
    | LPAREN type_specifier RPAREN expression %prec UNARY_MINUS {
        char op[32];
        snprintf(op, sizeof(op), "(%s)", $2);
        $$ = at(create_unary_op_node(op, $4, true), @$);
        free($2);
    }
    | expression DOT IDENTIFIER %prec DOT {
        $$ = at(create_member_access_node($1, $3), @$);
        free($3);
    }
    | expression DOT IDENTIFIER LPAREN RPAREN {
        $$ = at(create_method_call_node($1, $3, NULL), @$);
        free($3);
    }
    | expression DOT IDENTIFIER LPAREN argument_list RPAREN {
        $$ = at(create_method_call_node($1, $3, $5), @$);
        free($3);
    }
    | NOT expression {
        $$ = at(create_unary_op_node("!", $2, true), @$);
    }
    | BIT_NOT expression {
        $$ = at(create_unary_op_node("~", $2, true), @$);
    }
    | MINUS expression %prec UNARY_MINUS {
        $$ = at(create_unary_op_node("-", $2, true), @$);
    }
    | PLUS expression %prec UNARY_PLUS {
        $$ = at(create_unary_op_node("+", $2, true), @$);
    }
    | IDENTIFIER INCREMENT {
        ASTNode *id = at(create_identifier_node($1), @$);
        $$ = at(create_unary_op_node("++", id, false), @$);
        free($1);
    }
    | IDENTIFIER DECREMENT {
        ASTNode *id = at(create_identifier_node($1), @$);
        $$ = at(create_unary_op_node("--", id, false), @$);
        free($1);
    }
    | INCREMENT IDENTIFIER {
        ASTNode *id = at(create_identifier_node($2), @$);
        $$ = at(create_unary_op_node("++", id, true), @$);
        free($2);
    }
    | DECREMENT IDENTIFIER {
        ASTNode *id = at(create_identifier_node($2), @$);
        $$ = at(create_unary_op_node("--", id, true), @$);
        free($2);
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    | function_call { $$ = $1; }
    | array_access { $$ = $1; }
    ;

primary_expression:
    IDENTIFIER {
        $$ = at(create_identifier_node($1), @$);
        free($1);
    }
    | INT_LITERAL {
        $$ = at(create_int_literal_node($1), @$);
    }
    | FLOAT_LITERAL {
        $$ = at(create_float_literal_node($1), @$);
    }
    | STRING_LITERAL {
        $$ = at(create_string_literal_node($1), @$);
        free($1);
    }
    | CHAR_LITERAL {
        $$ = at(create_char_literal_node($1), @$);
    }
    | TRUE {
        $$ = at(create_boolean_literal_node(true), @$);
    }
    | FALSE {
        $$ = at(create_boolean_literal_node(false), @$);
    }
    | NULL_VAL {
        $$ = at(create_null_literal_node(), @$);
    }
    ;

function_call:
    PRINTLN LPAREN argument_list RPAREN {
        $$ = at(create_function_call_node("System.out.println", $3), @$);
    }
    | PRINTLN LPAREN RPAREN {
        $$ = at(create_function_call_node("System.out.println", NULL), @$);
    }
    | PRINT LPAREN argument_list RPAREN {
        $$ = at(create_function_call_node("System.out.print", $3), @$);
    }
    | PRINT LPAREN RPAREN {
        $$ = at(create_function_call_node("System.out.print", NULL), @$);
    }
    | IDENTIFIER LPAREN argument_list RPAREN {
        $$ = at(create_function_call_node($1, $3), @$);
        free($1);
    }
    | IDENTIFIER LPAREN RPAREN {
        $$ = at(create_function_call_node($1, NULL), @$);
        free($1);
    }
    | PARSE_INT LPAREN expression RPAREN {
        $$ = at(create_function_call_node("Integer.parseInt", $3), @$);
    }
    | PARSE_FLOAT LPAREN expression RPAREN {
        $$ = at(create_function_call_node("Float.parseFloat", $3), @$);
    }
    | PARSE_DOUBLE LPAREN expression RPAREN {
        $$ = at(create_function_call_node("Double.parseDouble", $3), @$);
    }
    | VALUE_OF LPAREN expression RPAREN {
        $$ = at(create_function_call_node("String.valueOf", $3), @$);
    }
    | STRING_JOIN LPAREN argument_list RPAREN {
        $$ = at(create_function_call_node("String.join", $3), @$);
    }
    | ARRAY_INDEX_OF LPAREN argument_list RPAREN {
        $$ = at(create_function_call_node("Arrays.indexOf", $3), @$);
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
        ASTNode *array = at(create_identifier_node($1), @$);
        $$ = at(create_array_access_node(array, $3), @$);
        free($1);
    }
    | array_access LBRACKET expression RBRACKET {
        $$ = at(create_array_access_node($1, $3), @$);
    }
    ;

array_value:
    array_initialization { $$ = $1; }
    | expression { $$ = $1; }
    ;

array_initialization:
    NEW type_specifier dim_exprs {
        ASTNode *node = at(create_node(NODE_ARRAY_INIT, line_num, col_num), @$);
        node->data.array_init.type = $2;
        node->data.array_init.size = $3;
        node->data.array_init.values = NULL;
        $$ = node;
    }
    | array_literal { $$ = $1; }
    ;

dim_exprs:
    LBRACKET expression RBRACKET {
        ASTNode *list = create_list_node();
        add_to_list(list, $2);
        $$ = list;
    }
    | dim_exprs LBRACKET expression RBRACKET {
        add_to_list($1, $3);
        $$ = $1;
    }
    ;

array_literal:
    LBRACE RBRACE {
        ASTNode *node = at(create_node(NODE_ARRAY_INIT, line_num, col_num), @$);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = create_list_node();
        $$ = node;
    }
    | LBRACE element_list RBRACE {
        ASTNode *node = at(create_node(NODE_ARRAY_INIT, line_num, col_num), @$);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = $2;
        $$ = node;
    }
    ;

element_list:
    element {
        ASTNode *list = create_list_node();
        add_to_list(list, $1);
        $$ = list;
    }
    | element_list COMMA element {
        add_to_list($1, $3);
        $$ = $1;
    }
    ;

element:
    expression { $$ = $1; }
    | array_literal { $$ = $1; }
    ;

dims:
    LBRACKET RBRACKET { $$ = 1; }
    | dims LBRACKET RBRACKET { $$ = $1 + 1; }
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
    fprintf(stderr, "Error sintáctico en línea %d, columna %d: %s\n", line_num, col_num, s);
    add_error(ERROR_SYNTACTIC, s, "Global", line_num, col_num);
}