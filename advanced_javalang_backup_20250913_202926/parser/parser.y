%{
#include "../include/javalang.h"

extern int yylex();
void yyerror(const char *s);
%}

%union {
    char *str_val;
    int int_val;
    double float_val;
    bool bool_val;
    ASTNode *node;
}

%token <str_val> IDENTIFIER STRING_LITERAL
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <bool_val> TRUE FALSE

%token PUBLIC PRIVATE PROTECTED STATIC FINAL VOID MAIN CLASS IMPORT
%token INT FLOAT DOUBLE BOOLEAN CHAR STRING_TYPE
%token IF ELSE SWITCH CASE DEFAULT WHILE FOR DO
%token BREAK CONTINUE RETURN
%token NULL_VAL NEW
%token PRINTLN PRINT PARSE_INT PARSE_DOUBLE VALUE_OF STRING_JOIN ARRAYS_TOSTRING
%token INCREMENT DECREMENT PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN
%token EQUAL NOT_EQUAL LESS_EQUAL GREATER_EQUAL AND OR
%token PLUS MINUS MULTIPLY DIVIDE MODULO ASSIGN LESS GREATER NOT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET SEMICOLON COMMA DOT

%type <node> program class_declaration method_declaration main_method
%type <node> statement_list statement variable_declaration assignment_statement
%type <node> expression primary_expression if_statement while_statement
%type <node> for_statement switch_statement block_statement
%type <node> function_call parameter_list expression_list
%type <node> data_type

%start program

%%

program: class_declaration {
    $$ = create_node(NODE_PROGRAM, "JavaLang Program", line_num, col_num);
    add_child($$, $1);
    ast_root = $$;
    printf("✅ AST: Programa JavaLang reconocido\n");
};

class_declaration: PUBLIC CLASS IDENTIFIER LBRACE main_method method_list RBRACE {
    $$ = create_node(NODE_CLASS, $3, line_num, col_num);
    add_child($$, $5);
    printf("✅ AST: Clase '%s' procesada\n", $3);
}
| PUBLIC CLASS IDENTIFIER LBRACE main_method RBRACE {
    $$ = create_node(NODE_CLASS, $3, line_num, col_num);
    add_child($$, $5);
    printf("✅ AST: Clase '%s' procesada\n", $3);
};

main_method: PUBLIC STATIC VOID MAIN LPAREN STRING_TYPE LBRACKET RBRACKET IDENTIFIER RPAREN LBRACE statement_list RBRACE {
    $$ = create_node(NODE_MAIN_METHOD, "main", line_num, col_num);
    add_child($$, $12);
    enter_scope();
    printf("✅ AST: Método main procesado\n");
};

method_list: method_list method_declaration {
    $$ = $1;
    add_child($$, $2);
}
| method_declaration {
    $$ = create_node(NODE_PROGRAM, "methods", line_num, col_num);
    add_child($$, $1);
}
| /* empty */ {
    $$ = create_node(NODE_PROGRAM, "empty_methods", line_num, col_num);
};

method_declaration: STATIC data_type IDENTIFIER LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
    $$ = create_node(NODE_METHOD, $3, line_num, col_num);
    add_child($$, $2);
    add_child($$, $5);
    add_child($$, $8);
    printf("✅ Análisis: Método '%s' declarado\n", $3);
}
| STATIC VOID IDENTIFIER LPAREN parameter_list RPAREN LBRACE statement_list RBRACE {
    $$ = create_node(NODE_METHOD, $3, line_num, col_num);
    add_child($$, $5);
    add_child($$, $8);
    printf("✅ Análisis: Método void '%s' declarado\n", $3);
}
| STATIC data_type IDENTIFIER LPAREN RPAREN LBRACE statement_list RBRACE {
    $$ = create_node(NODE_METHOD, $3, line_num, col_num);
    add_child($$, $2);
    add_child($$, $7);
    printf("✅ Análisis: Método '%s' sin parámetros\n", $3);
};

parameter_list: parameter_list COMMA data_type IDENTIFIER {
    $$ = $1;
    ASTNode *param = create_node(NODE_VAR_DECL, $4, line_num, col_num);
    add_child(param, $3);
    add_child($$, param);
}
| data_type IDENTIFIER {
    $$ = create_node(NODE_PROGRAM, "params", line_num, col_num);
    ASTNode *param = create_node(NODE_VAR_DECL, $2, line_num, col_num);
    add_child(param, $1);
    add_child($$, param);
};

data_type: INT {
    $$ = create_node(NODE_IDENTIFIER, "int", line_num, col_num);
}
| FLOAT {
    $$ = create_node(NODE_IDENTIFIER, "float", line_num, col_num);
}
| DOUBLE {
    $$ = create_node(NODE_IDENTIFIER, "double", line_num, col_num);
}
| STRING_TYPE {
    $$ = create_node(NODE_IDENTIFIER, "String", line_num, col_num);
}
| BOOLEAN {
    $$ = create_node(NODE_IDENTIFIER, "boolean", line_num, col_num);
}
| data_type LBRACKET RBRACKET {
    $$ = $1; // Tipo array
};

statement_list: statement_list statement {
    $$ = $1 ? $1 : create_node(NODE_BLOCK, "statements", line_num, col_num);
    if ($2) add_child($$, $2);
}
| statement {
    $$ = create_node(NODE_BLOCK, "statements", line_num, col_num);
    if ($1) add_child($$, $1);
}
| /* empty */ {
    $$ = create_node(NODE_BLOCK, "empty", line_num, col_num);
};

statement: variable_declaration { $$ = $1; }
| assignment_statement { $$ = $1; }
| if_statement { $$ = $1; }
| while_statement { $$ = $1; }
| for_statement { $$ = $1; }
| switch_statement { $$ = $1; }
| block_statement { $$ = $1; }
| function_call SEMICOLON { $$ = $1; }
| BREAK SEMICOLON { $$ = create_node(NODE_BREAK, "break", line_num, col_num); }
| CONTINUE SEMICOLON { $$ = create_node(NODE_CONTINUE, "continue", line_num, col_num); }
| RETURN expression SEMICOLON { 
    $$ = create_node(NODE_RETURN, "return", line_num, col_num); 
    add_child($$, $2);
}
| RETURN SEMICOLON { $$ = create_node(NODE_RETURN, "return", line_num, col_num); };

variable_declaration: data_type IDENTIFIER SEMICOLON {
    $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
    add_child($$, $1);
    
    // Análisis semántico
    DataType dt = TYPE_INT; // simplificado
    if ($1 && $1->value) {
        if (strcmp($1->value, "String") == 0) dt = TYPE_STRING;
        else if (strcmp($1->value, "double") == 0) dt = TYPE_DOUBLE;
        else if (strcmp($1->value, "boolean") == 0) dt = TYPE_BOOLEAN;
    }
    add_symbol($2, dt, false);
}
| data_type IDENTIFIER ASSIGN expression SEMICOLON {
    $$ = create_node(NODE_VAR_DECL, $2, line_num, col_num);
    add_child($$, $1);
    add_child($$, $4);
    
    DataType dt = TYPE_INT;
    if ($1 && $1->value) {
        if (strcmp($1->value, "String") == 0) dt = TYPE_STRING;
        else if (strcmp($1->value, "double") == 0) dt = TYPE_DOUBLE;
        else if (strcmp($1->value, "boolean") == 0) dt = TYPE_BOOLEAN;
    }
    add_symbol($2, dt, false);
    printf("✅ Análisis: Variable '%s' declarada e inicializada\n", $2);
}
| data_type LBRACKET RBRACKET IDENTIFIER ASSIGN NEW data_type LBRACKET RBRACKET LBRACE expression_list RBRACE SEMICOLON {
    $$ = create_node(NODE_ARRAY_DECL, $4, line_num, col_num);
    add_child($$, $1);
    add_child($$, $11);
    add_symbol($4, TYPE_ARRAY, true);
    printf("✅ Análisis: Array '%s' declarado\n", $4);
};

assignment_statement: IDENTIFIER ASSIGN expression SEMICOLON {
    $$ = create_node(NODE_ASSIGNMENT, $1, line_num, col_num);
    add_child($$, $3);
    check_variable_usage($1, line_num);
}
| IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON {
    $$ = create_node(NODE_ASSIGNMENT, $1, line_num, col_num);
    add_child($$, $3);
    add_child($$, $6);
    check_variable_usage($1, line_num);
};

if_statement: IF LPAREN expression RPAREN statement {
    $$ = create_node(NODE_IF, "if", line_num, col_num);
    add_child($$, $3);
    add_child($$, $5);
}
| IF LPAREN expression RPAREN statement ELSE statement {
    $$ = create_node(NODE_IF, "if_else", line_num, col_num);
    add_child($$, $3);
    add_child($$, $5);
    add_child($$, $7);
};

while_statement: WHILE LPAREN expression RPAREN statement {
    $$ = create_node(NODE_WHILE, "while", line_num, col_num);
    add_child($$, $3);
    add_child($$, $5);
};

for_statement: FOR LPAREN variable_declaration expression SEMICOLON assignment_statement RPAREN statement {
    $$ = create_node(NODE_FOR, "for", line_num, col_num);
    add_child($$, $3);
    add_child($$, $4);
    add_child($$, $6);
    add_child($$, $8);
    enter_scope();
}
| FOR LPAREN assignment_statement expression SEMICOLON assignment_statement RPAREN statement {
    $$ = create_node(NODE_FOR, "for", line_num, col_num);
    add_child($$, $3);
    add_child($$, $4);
    add_child($$, $6);
    add_child($$, $8);
}
| FOR LPAREN data_type IDENTIFIER ASSIGN expression SEMICOLON expression SEMICOLON IDENTIFIER INCREMENT RPAREN statement {
    $$ = create_node(NODE_FOR, "for_classic", line_num, col_num);
    printf("✅ Análisis: For clásico procesado\n");
};

switch_statement: SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE {
    $$ = create_node(NODE_SWITCH, "switch", line_num, col_num);
    add_child($$, $3);
    add_child($$, $6);
};

case_list: case_list case_statement {
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
};

case_statement: CASE INT_LITERAL COLON statement_list {
    $$ = create_node(NODE_CASE, "case", line_num, col_num);
    ASTNode *val = create_node(NODE_INT_LITERAL, NULL, line_num, col_num);
    val->int_val = $2;
    add_child($$, val);
    add_child($$, $4);
};

block_statement: LBRACE statement_list RBRACE {
    $$ = create_node(NODE_BLOCK, "block", line_num, col_num);
    add_child($$, $2);
    enter_scope();
};

expression: expression PLUS expression {
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
| expression EQUAL expression {
    $$ = create_node(NODE_BINARY_OP, "==", line_num, col_num);
    add_child($$, $1);
    add_child($$, $3);
}
| expression AND expression {
    $$ = create_node(NODE_BINARY_OP, "&&", line_num, col_num);
    add_child($$, $1);
    add_child($$, $3);
}
| expression OR expression {
    $$ = create_node(NODE_BINARY_OP, "||", line_num, col_num);
    add_child($$, $1);
    add_child($$, $3);
}
| NOT expression {
    $$ = create_node(NODE_UNARY_OP, "!", line_num, col_num);
    add_child($$, $2);
}
| primary_expression { $$ = $1; };

primary_expression: IDENTIFIER {
    $$ = create_node(NODE_IDENTIFIER, $1, line_num, col_num);
    check_variable_usage($1, line_num);
}
| INT_LITERAL {
    $$ = create_node(NODE_INT_LITERAL, NULL, line_num, col_num);
    $$->int_val = $1;
}
| FLOAT_LITERAL {
    $$ = create_node(NODE_FLOAT_LITERAL, NULL, line_num, col_num);
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
| LPAREN expression RPAREN { $$ = $2; }
| IDENTIFIER LBRACKET expression RBRACKET {
    $$ = create_node(NODE_ARRAY_ACCESS, $1, line_num, col_num);
    add_child($$, $3);
    check_variable_usage($1, line_num);
}
| function_call { $$ = $1; };

function_call: PRINTLN LPAREN expression_list RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, "println", line_num, col_num);
    add_child($$, $3);
    process_println($3);
}
| IDENTIFIER LPAREN expression_list RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, $1, line_num, col_num);
    add_child($$, $3);
    printf("✅ Análisis: Llamada a función '%s'\n", $1);
}
| IDENTIFIER LPAREN RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, $1, line_num, col_num);
    printf("✅ Análisis: Llamada a función '%s' sin argumentos\n", $1);
}
| PARSE_INT LPAREN expression RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, "parseInt", line_num, col_num);
    add_child($$, $3);
    process_parseInt($3);
}
| VALUE_OF LPAREN expression RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, "valueOf", line_num, col_num);
    add_child($$, $3);
    process_valueOf($3);
}
| STRING_JOIN LPAREN expression COMMA expression RPAREN {
    $$ = create_node(NODE_FUNCTION_CALL, "join", line_num, col_num);
    add_child($$, $3);
    add_child($$, $5);
    process_join($$);
};

expression_list: expression_list COMMA expression {
    $$ = $1 ? $1 : create_node(NODE_BLOCK, "expressions", line_num, col_num);
    add_child($$, $3);
}
| expression {
    $$ = create_node(NODE_BLOCK, "expressions", line_num, col_num);
    add_child($$, $1);
}
| /* empty */ {
    $$ = create_node(NODE_BLOCK, "empty_expr", line_num, col_num);
};

%%

void yyerror(const char *s) {
    printf("⚠️ Advertencia sintáctica en línea %d: %s\n", line_num, s);
}
