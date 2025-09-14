%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "ast.h"

extern int yylex();
extern FILE *yyin;
extern int line_num;
extern int col_num;
extern ASTNode *ast_root;

void yyerror(const char *s);
%}

%union {
    int int_val;
    float float_val;
    char *str_val;
    ASTNode *node;
    bool bool_val;
}

%token <str_val> IDENTIFIER STRING_LITERAL
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <bool_val> TRUE FALSE

%token PUBLIC STATIC VOID MAIN INT FLOAT STRING_TYPE BOOLEAN
%token IF ELSE WHILE FOR BREAK CONTINUE RETURN
%token PLUS MINUS MULTIPLY DIVIDE ASSIGN EQUAL LESS GREATER
%token AND OR NOT LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA PRINTLN PRINT

%type <node> program main_class statement_list statement
%type <node> variable_declaration assignment_statement expression
%type <node> primary_expression if_statement while_statement
%type <node> data_type print_statement

%start program

%%

program: main_class {
    $$ = create_program_node(NULL);
    add_to_list($$, $1);
    ast_root = $$;
    printf("AST creado\n");
};

main_class: PUBLIC STATIC VOID MAIN LPAREN STRING_TYPE LBRACKET RBRACKET IDENTIFIER RPAREN LBRACE statement_list RBRACE {
    $$ = create_main_class_node($12);
    printf("Main encontrado\n");
};

statement_list: statement_list statement {
    $$ = $1 ? $1 : create_list_node();
    add_to_list($$, $2);
}
| statement {
    $$ = create_list_node();
    add_to_list($$, $1);
}
| /* empty */ {
    $$ = create_list_node();
};

statement: variable_declaration { $$ = $1; }
| assignment_statement { $$ = $1; }
| if_statement { $$ = $1; }
| while_statement { $$ = $1; }
| print_statement { $$ = $1; };

variable_declaration: data_type IDENTIFIER SEMICOLON {
    char *type_name = ($1 && $1->data.type.name) ? $1->data.type.name : "int";
    $$ = create_var_decl_node(type_name, $2, NULL, false, 0);
    printf("Variable %s declarada\n", $2);
}
| data_type IDENTIFIER ASSIGN expression SEMICOLON {
    char *type_name = ($1 && $1->data.type.name) ? $1->data.type.name : "int";
    $$ = create_var_decl_node(type_name, $2, $4, false, 0);
    printf("Variable %s inicializada\n", $2);
};

assignment_statement: IDENTIFIER ASSIGN expression SEMICOLON {
    ASTNode *left = create_identifier_node($1);
    $$ = create_assignment_node(left, "=", $3);
    printf("Asignacion a %s\n", $1);
};

if_statement: IF LPAREN expression RPAREN LBRACE statement_list RBRACE {
    $$ = create_if_node($3, create_block_node(), NULL);
    add_to_list($$->data.if_stmt.then_stmt, $6);
};

while_statement: WHILE LPAREN expression RPAREN LBRACE statement_list RBRACE {
    $$ = create_while_node($3, create_block_node());
    add_to_list($$->data.while_stmt.body, $6);
};

print_statement: PRINTLN LPAREN expression RPAREN SEMICOLON {
    $$ = create_function_call_node("println", $3);
};

data_type: INT {
    $$ = create_node(NODE_TYPE, line_num, col_num);
    $$->data.type.name = strdup("int");
}
| STRING_TYPE {
    $$ = create_node(NODE_TYPE, line_num, col_num);
    $$->data.type.name = strdup("String");
};

expression: primary_expression { $$ = $1; }
| expression PLUS expression { $$ = create_binary_op_node("+", $1, $3); }
| expression MINUS expression { $$ = create_binary_op_node("-", $1, $3); };

primary_expression: IDENTIFIER {
    $$ = create_identifier_node($1);
}
| INT_LITERAL {
    $$ = create_int_literal_node($1);
}
| STRING_LITERAL {
    $$ = create_string_literal_node($1);
};

%%

void yyerror(const char *s) {
    printf("Error: %s en linea %d\n", s, line_num);
}
