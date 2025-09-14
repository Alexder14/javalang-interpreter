%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "parser.tab.h"

extern int line_num;
extern int col_num;

void update_position(char *text) {
    col_num += strlen(text);
}
%}

%option noyywrap

%%

"public"        { update_position(yytext); return PUBLIC; }
"private"       { update_position(yytext); return PRIVATE; }
"protected"     { update_position(yytext); return PROTECTED; }
"static"        { update_position(yytext); return STATIC; }
"final"         { update_position(yytext); return FINAL; }
"void"          { update_position(yytext); return VOID; }
"main"          { update_position(yytext); return MAIN; }

"int"           { update_position(yytext); return INT; }
"float"         { update_position(yytext); return FLOAT; }
"double"        { update_position(yytext); return DOUBLE; }
"boolean"       { update_position(yytext); return BOOLEAN; }
"char"          { update_position(yytext); return CHAR; }
"String"        { update_position(yytext); return STRING_TYPE; }

"if"            { update_position(yytext); return IF; }
"else"          { update_position(yytext); return ELSE; }
"switch"        { update_position(yytext); return SWITCH; }
"case"          { update_position(yytext); return CASE; }
"default"       { update_position(yytext); return DEFAULT; }
"while"         { update_position(yytext); return WHILE; }
"for"           { update_position(yytext); return FOR; }
"do"            { update_position(yytext); return DO; }

"break"         { update_position(yytext); return BREAK; }
"continue"      { update_position(yytext); return CONTINUE; }
"return"        { update_position(yytext); return RETURN; }

"null"          { update_position(yytext); return NULL_VAL; }
"new"           { update_position(yytext); return NEW; }
"this"          { update_position(yytext); return THIS; }
"true"          { update_position(yytext); yylval.bool_val = 1; return TRUE; }
"false"         { update_position(yytext); yylval.bool_val = 0; return FALSE; }

"println"       { update_position(yytext); return PRINTLN; }
"print"         { update_position(yytext); return PRINT; }
"parseInt"      { update_position(yytext); return PARSE_INT; }
"parseFloat"    { update_position(yytext); return PARSE_FLOAT; }
"parseDouble"   { update_position(yytext); return PARSE_DOUBLE; }
"valueOf"       { update_position(yytext); return VALUE_OF; }
"join"          { update_position(yytext); return STRING_JOIN; }
"indexOf"       { update_position(yytext); return ARRAY_INDEX_OF; }

"++"            { update_position(yytext); return INCREMENT; }
"--"            { update_position(yytext); return DECREMENT; }
"+="            { update_position(yytext); return PLUS_ASSIGN; }
"-="            { update_position(yytext); return MINUS_ASSIGN; }
"*="            { update_position(yytext); return MULT_ASSIGN; }
"/="            { update_position(yytext); return DIV_ASSIGN; }
"%="            { update_position(yytext); return MOD_ASSIGN; }

"=="            { update_position(yytext); return EQUAL; }
"!="            { update_position(yytext); return NOT_EQUAL; }
"<="            { update_position(yytext); return LESS_EQUAL; }
">="            { update_position(yytext); return GREATER_EQUAL; }
"&&"            { update_position(yytext); return AND; }
"||"            { update_position(yytext); return OR; }
"<<"            { update_position(yytext); return LEFT_SHIFT; }
">>"            { update_position(yytext); return RIGHT_SHIFT; }

"+"             { update_position(yytext); return PLUS; }
"-"             { update_position(yytext); return MINUS; }
"*"             { update_position(yytext); return MULTIPLY; }
"/"             { update_position(yytext); return DIVIDE; }
"%"             { update_position(yytext); return MODULO; }
"="             { update_position(yytext); return ASSIGN; }
"<"             { update_position(yytext); return LESS; }
">"             { update_position(yytext); return GREATER; }
"!"             { update_position(yytext); return NOT; }
"&"             { update_position(yytext); return BIT_AND; }
"|"             { update_position(yytext); return BIT_OR; }
"^"             { update_position(yytext); return BIT_XOR; }
"~"             { update_position(yytext); return BIT_NOT; }

"("             { update_position(yytext); return LPAREN; }
")"             { update_position(yytext); return RPAREN; }
"{"             { update_position(yytext); return LBRACE; }
"}"             { update_position(yytext); return RBRACE; }
"["             { update_position(yytext); return LBRACKET; }
"]"             { update_position(yytext); return RBRACKET; }
";"             { update_position(yytext); return SEMICOLON; }
","             { update_position(yytext); return COMMA; }
"."             { update_position(yytext); return DOT; }
":"             { update_position(yytext); return COLON; }
"?"             { update_position(yytext); return QUESTION; }

[0-9]+          { 
    update_position(yytext); 
    yylval.int_val = atoi(yytext); 
    return INT_LITERAL; 
}

[0-9]+\.[0-9]+  { 
    update_position(yytext); 
    yylval.float_val = atof(yytext); 
    return FLOAT_LITERAL; 
}

\"([^\"\\]|\\.)*\"  { 
    update_position(yytext); 
    int len = strlen(yytext);
    yylval.str_val = malloc(len - 1);
    strncpy(yylval.str_val, yytext + 1, len - 2);
    yylval.str_val[len - 2] = '\0';
    return STRING_LITERAL; 
}

\'([^\'\\]|\\.)?\'  { 
    update_position(yytext); 
    yylval.char_val = yytext[1]; 
    return CHAR_LITERAL; 
}

[a-zA-Z][a-zA-Z0-9_]* { 
    update_position(yytext); 
    yylval.str_val = strdup(yytext); 
    return IDENTIFIER; 
}

[ \t]+          { col_num += strlen(yytext); }

\n              { line_num++; col_num = 1; }

"//".*          { /* comentarios de línea */ }

"/*"            { 
    int c;
    while ((c = input()) != 0) {
        if (c == '\n') line_num++;
        else if (c == '*') {
            if ((c = input()) == '/') break;
            else unput(c);
        }
    }
}

.               { 
    printf("Carácter no reconocido: '%s' en línea %d\n", yytext, line_num);
    col_num++; 
}

%%
