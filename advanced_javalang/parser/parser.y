%{
#include "../include/javalang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int line_num;
extern int col_num;

void yyerror(const char *s);

ASTNode *ast_root = NULL;
%}

%union {
    int int_val;
    double float_val;
    char *string_val;
    ASTNode *node;
}

%token <string_val> IDENTIFIER STRING_LITERAL
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL

%token PUBLIC STATIC VOID INT FLOAT DOUBLE BOOLEAN STRING
%token CLASS MAIN IF ELSE WHILE FOR SWITCH CASE DEFAULT
%token BREAK CONTINUE RETURN TRUE FALSE NULL_LITERAL PRINTLN
%token LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET
%token SEMICOLON COMMA COLON ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token EQ NE LT LE GT GE AND OR NOT

%type <node> program class_declaration method_list method_declaration
%type <node> parameter_list parameter statement_list statement
%type <node> variable_declaration assignment expression
%type <node> if_statement while_statement for_statement
%type <node> switch_statement case_list case_statement
%type <node> expression_statement return_statement
%type <node> primary_expression binary_expression unary_expression
%type <node> function_call argument_list

%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%right ASSIGN

%%

program:
    class_declaration {
        ast_root = $1;
        $$ = $1;
    }
    ;

class_declaration:
    PUBLIC CLASS IDENTIFIER LBRACE method_list RBRACE {
        $$ = create_node(NODE_CLASS, $3, line_num, col_num);
        add_child($$, $5);
    }
    | PUBLIC CLASS IDENTIFIER LBRACE RBRACE {
        $$ = create_node(NODE_CLASS, $3, line_num, col_num);
    }
    ;

method_list:
    method_list method_declaration {
        $$ = $1;
        add_child($$, $2);
    }
    | method_declaration {
        $$ = create_node(NODE_PROGRAM, "methods", line_num, col_num);
        add_child($$, $1);
    }
    | /* empty */ {
        $$ = create_node(NODE_PROGRAM, "empty_methods", line_num, col_num);
    }
    ;

method_declaration:
    PUBLIC STATIC VOID MAIN LPAREN RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_MAIN_METHOD, "main", line_num, col_num);
        add_child($$, $8);
    }
    | PUBLIC STATIC VOID MAIN LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_MAIN_METHOD, "main", line_num, col_num);
        add_child($$, $6);
        add_child($$, $9);
    }
    | PUBLIC STATIC INT IDENTIFIER LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_METHOD, $4, line_num, col_num);
        add_child($$, $6);
        add_child($$, $9);
    }
    | PUBLIC STATIC VOID IDENTIFIER LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_METHOD, $4, line_num, col_num);
        add_child($$, $6);
        add_child($$, $9);
    }
    ;

parameter_list:
    parameter_list COMMA parameter {
        $$ = $1;
        add_child($$, $3);
    }
    | parameter {
        $$ = create_node(NODE_BLOCK, "parameters", line_num, col_num);
        add_child($$, $1);
    }
    | /* empty */ {
        $$ = create_node(NODE_BLOCK, "empty_params", line_num, col_num);
    }
    ;

parameter:
    INT IDENTIFIER {
        $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
    }
    | STRING LBRACKET RBRACKET IDENTIFIER {
        $$ = create_node(NODE_ARRAY_DECL, $4, line_num, col_num);
    }
    ;

statement_list:
    statement_list statement {
        $$ = $1;
        add_child($$, $2);
    }
    | statement {
        $$ = create_node(NODE_BLOCK, "statements", line_num, col_num);
        add_child($$, $1);
    }
    | /* empty */ {
        $$ = create_node(NODE_BLOCK, "empty_block", line_num, col_num);
    }
    ;

statement:
    variable_declaration SEMICOLON { $$ = $1; }
    | assignment SEMICOLON { $$ = $1; }
    | expression_statement SEMICOLON { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    | switch_statement { $$ = $1; }
    | return_statement SEMICOLON { $$ = $1; }
    | BREAK SEMICOLON {
        $$ = create_node(NODE_BREAK, "break", line_num, col_num);
    }
    | CONTINUE SEMICOLON {
        $$ = create_node(NODE_CONTINUE, "continue", line_num, col_num);
    }
    | LBRACE statement_list RBRACE { $$ = $2; }
    ;

variable_declaration:
    INT IDENTIFIER {
        $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
    }
    | INT IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
        add_child($$, $4);
    }
    | FLOAT IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
        add_child($$, $4);
    }
    | STRING IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
        add_child($$, $4);
    }
    | INT LBRACKET RBRACKET IDENTIFIER {
        $$ = create_node(NODE_ARRAY_DECL, $4, line_num, col_num);
    }
    ;

assignment:
    IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT, $1, line_num, col_num);
        add_child($$, $3);
    }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = create_node(NODE_IF, "if", line_num, col_num);
        add_child($$, $3);
        add_child($$, $5);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_node(NODE_IF, "if", line_num, col_num);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = create_node(NODE_WHILE, "while", line_num, col_num);
        add_child($$, $3);
        add_child($$, $5);
    }
    ;

for_statement:
    FOR LPAREN assignment SEMICOLON expression SEMICOLON assignment RPAREN statement {
        $$ = create_node(NODE_FOR, "for", line_num, col_num);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
        add_child($$, $9);
    }
    ;

switch_statement:
    SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE {
        $$ = create_node(NODE_SWITCH, "switch", line_num, col_num);
        add_child($$, $3);
        add_child($$, $6);
    }
    ;

case_list:
    case_list case_statement {
        $$ = $1;
        add_child($$, $2);
    }
    | case_statement {
        $$ = create_node(NODE_BLOCK, "cases", line_num, col_num);
        add_child($$, $1);
    }
    | case_list DEFAULT COLON statement_list {
        $$ = $1;
        ASTNode *def = create_node(NODE_DEFAULT, "default", line_num, col_num);
        add_child(def, $4);
        add_child($$, def);
    }
    ;

case_statement:
    CASE INT_LITERAL COLON statement_list {
        $$ = create_node(NODE_CASE, "case", line_num, col_num);
        ASTNode *val = create_node(NODE_INT_LITERAL, "", line_num, col_num);
        val->int_val = $2;
        add_child($$, val);
        add_child($$, $4);
    }
    ;

expression_statement:
    expression { $$ = $1; }
    ;

return_statement:
    RETURN expression {
        $$ = create_node(NODE_RETURN, "return", line_num, col_num);
        add_child($$, $2);
    }
    | RETURN {
        $$ = create_node(NODE_RETURN, "return", line_num, col_num);
    }
    ;

expression:
    binary_expression { $$ = $1; }
    | unary_expression { $$ = $1; }
    | primary_expression { $$ = $1; }
    ;

binary_expression:
    expression PLUS expression {
        $$ = create_node(NODE_BINARY_OP, "+", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression MINUS expression {
        $$ = create_node(NODE_BINARY_OP, "-", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression MULTIPLY expression {
        $$ = create_node(NODE_BINARY_OP, "*", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression DIVIDE expression {
        $$ = create_node(NODE_BINARY_OP, "/", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression EQ expression {
        $$ = create_node(NODE_BINARY_OP, "==", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression NE expression {
        $$ = create_node(NODE_BINARY_OP, "!=", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression LT expression {
        $$ = create_node(NODE_BINARY_OP, "<", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    | expression GT expression {
        $$ = create_node(NODE_BINARY_OP, ">", line_num, col_num);
        add_child($$, $1);
        add_child($$, $3);
    }
    ;

unary_expression:
    NOT expression {
        $$ = create_node(NODE_UNARY_OP, "!", line_num, col_num);
        add_child($$, $2);
    }
    | MINUS expression {
        $$ = create_node(NODE_UNARY_OP, "-", line_num, col_num);
        add_child($$, $2);
    }
    ;

primary_expression:
    IDENTIFIER {
        $$ = create_node(NODE_IDENTIFIER, $1, line_num, col_num);
    }
    | INT_LITERAL {
        $$ = create_node(NODE_INT_LITERAL, "", line_num, col_num);
        $$->int_val = $1;
    }
    | FLOAT_LITERAL {
        $$ = create_node(NODE_FLOAT_LITERAL, "", line_num, col_num);
        $$->float_val = $1;
    }
    | STRING_LITERAL {
        $$ = create_node(NODE_STRING_LITERAL, $1, line_num, col_num);
    }
    | TRUE {
        $$ = create_node(NODE_BOOLEAN_LITERAL, "true", line_num, col_num);
        $$->bool_val = true;
    }
    | FALSE {
        $$ = create_node(NODE_BOOLEAN_LITERAL, "false", line_num, col_num);
        $$->bool_val = false;
    }
    | NULL_LITERAL {
        $$ = create_node(NODE_NULL_LITERAL, "null", line_num, col_num);
    }
    | function_call { $$ = $1; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

function_call:
    PRINTLN LPAREN argument_list RPAREN {
        $$ = create_node(NODE_FUNCTION_CALL, "println", line_num, col_num);
        add_child($$, $3);
    }
    | IDENTIFIER LPAREN argument_list RPAREN {
        $$ = create_node(NODE_FUNCTION_CALL, $1, line_num, col_num);
        add_child($$, $3);
    }
    ;

argument_list:
    argument_list COMMA expression {
        $$ = $1;
        add_child($$, $3);
    }
    | expression {
        $$ = create_node(NODE_BLOCK, "arguments", line_num, col_num);
        add_child($$, $1);
    }
    | /* empty */ {
        $$ = create_node(NODE_BLOCK, "empty_args", line_num, col_num);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error en línea %d, columna %d: %s\n", line_num, col_num, s);
}
