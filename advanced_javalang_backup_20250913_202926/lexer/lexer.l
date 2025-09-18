%{
#include "../include/javalang.h"
#include "../parser/parser.tab.h"

void update_position();
void count_line();
%}

%option noyywrap

%%

"public"        { update_position(); return PUBLIC; }
"private"       { update_position(); return PRIVATE; }
"protected"     { update_position(); return PROTECTED; }
"static"        { update_position(); return STATIC; }
"final"         { update_position(); return FINAL; }
"void"          { update_position(); return VOID; }
"main"          { update_position(); return MAIN; }
"class"         { update_position(); return CLASS; }
"import"        { update_position(); return IMPORT; }

"int"           { update_position(); return INT; }
"float"         { update_position(); return FLOAT; }
"double"        { update_position(); return DOUBLE; }
"boolean"       { update_position(); return BOOLEAN; }
"char"          { update_position(); return CHAR; }
"String"        { update_position(); return STRING_TYPE; }

"if"            { update_position(); return IF; }
"else"          { update_position(); return ELSE; }
"switch"        { update_position(); return SWITCH; }
"case"          { update_position(); return CASE; }
"default"       { update_position(); return DEFAULT; }
"while"         { update_position(); return WHILE; }
"for"           { update_position(); return FOR; }
"do"            { update_position(); return DO; }

"break"         { update_position(); return BREAK; }
"continue"      { update_position(); return CONTINUE; }
"return"        { update_position(); return RETURN; }

"true"          { update_position(); yylval.bool_val = 1; return TRUE; }
"false"         { update_position(); yylval.bool_val = 0; return FALSE; }
"null"          { update_position(); return NULL_VAL; }
"new"           { update_position(); return NEW; }

"System.out.println" { update_position(); return PRINTLN; }
"System.out.print"   { update_position(); return PRINT; }
"Integer.parseInt"   { update_position(); return PARSE_INT; }
"Double.parseDouble" { update_position(); return PARSE_DOUBLE; }
"String.valueOf"     { update_position(); return VALUE_OF; }
"String.join"        { update_position(); return STRING_JOIN; }
"Arrays.toString"    { update_position(); return ARRAYS_TOSTRING; }

"++"            { update_position(); return INCREMENT; }
"--"            { update_position(); return DECREMENT; }
"+="            { update_position(); return PLUS_ASSIGN; }
"-="            { update_position(); return MINUS_ASSIGN; }
"*="            { update_position(); return MULT_ASSIGN; }
"/="            { update_position(); return DIV_ASSIGN; }

"=="            { update_position(); return EQUAL; }
"!="            { update_position(); return NOT_EQUAL; }
"<="            { update_position(); return LESS_EQUAL; }
">="            { update_position(); return GREATER_EQUAL; }
"&&"            { update_position(); return AND; }
"||"            { update_position(); return OR; }

"+"             { update_position(); return PLUS; }
"-"             { update_position(); return MINUS; }
"*"             { update_position(); return MULTIPLY; }
"/"             { update_position(); return DIVIDE; }
"%"             { update_position(); return MODULO; }
"="             { update_position(); return ASSIGN; }
"<"             { update_position(); return LESS; }
">"             { update_position(); return GREATER; }
"!"             { update_position(); return NOT; }

"("             { update_position(); return LPAREN; }
")"             { update_position(); return RPAREN; }
"{"             { update_position(); return LBRACE; }
"}"             { update_position(); return RBRACE; }
"["             { update_position(); return LBRACKET; }
"]"             { update_position(); return RBRACKET; }
";"             { update_position(); return SEMICOLON; }
","             { update_position(); return COMMA; }
"."             { update_position(); return DOT; }

[0-9]+          { update_position(); yylval.int_val = atoi(yytext); total_tokens++; return INT_LITERAL; }
[0-9]+\.[0-9]+  { update_position(); yylval.float_val = atof(yytext); total_tokens++; return FLOAT_LITERAL; }
\"([^\"\\]|\\.)*\"  { update_position(); yylval.str_val = strdup(yytext); total_tokens++; return STRING_LITERAL; }
[a-zA-Z][a-zA-Z0-9_]* { update_position(); yylval.str_val = strdup(yytext); total_tokens++; return IDENTIFIER; }

[ \t]+          { col_num += strlen(yytext); }
\n              { count_line(); }
"//".*          { /* comentarios */ }
"/*"([^*]|"*"[^/])*"*/" { /* comentarios multilínea */ }

.               { col_num++; }

%%

void update_position() {
    col_num += strlen(yytext);
    total_tokens++;
}

void count_line() {
    line_num++; 
    col_num = 1; 
    total_lines++;
}
