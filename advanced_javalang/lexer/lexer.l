%{
#include "../include/javalang.h"
#include "../parser/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
int col_num = 1;

void update_position(char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            line_num++;
            col_num = 1;
        } else {
            col_num++;
        }
    }
}
%}

%option noyywrap

%%
"public"        { update_position(yytext); return PUBLIC; }
"static"        { update_position(yytext); return STATIC; }
"void"          { update_position(yytext); return VOID; }
"int"           { update_position(yytext); return INT; }
"float"         { update_position(yytext); return FLOAT; }
"double"        { update_position(yytext); return DOUBLE; }
"boolean"       { update_position(yytext); return BOOLEAN; }
"String"        { update_position(yytext); return STRING; }
"class"         { update_position(yytext); return CLASS; }
"main"          { update_position(yytext); return MAIN; }
"if"            { update_position(yytext); return IF; }
"else"          { update_position(yytext); return ELSE; }
"while"         { update_position(yytext); return WHILE; }
"for"           { update_position(yytext); return FOR; }
"switch"        { update_position(yytext); return SWITCH; }
"case"          { update_position(yytext); return CASE; }
"default"       { update_position(yytext); return DEFAULT; }
"break"         { update_position(yytext); return BREAK; }
"continue"      { update_position(yytext); return CONTINUE; }
"return"        { update_position(yytext); return RETURN; }
"true"          { update_position(yytext); return TRUE; }
"false"         { update_position(yytext); return FALSE; }
"null"          { update_position(yytext); return NULL_LITERAL; }
"System.out.println" { update_position(yytext); return PRINTLN; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    update_position(yytext); 
    yylval.string_val = strdup(yytext); 
    return IDENTIFIER; 
}

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

\"([^"\\]|\\.)*\" { 
    update_position(yytext); 
    yylval.string_val = strdup(yytext); 
    return STRING_LITERAL; 
}

"{"             { update_position(yytext); return LBRACE; }
"}"             { update_position(yytext); return RBRACE; }
"("             { update_position(yytext); return LPAREN; }
")"             { update_position(yytext); return RPAREN; }
"["             { update_position(yytext); return LBRACKET; }
"]"             { update_position(yytext); return RBRACKET; }
";"             { update_position(yytext); return SEMICOLON; }
","             { update_position(yytext); return COMMA; }
":"             { update_position(yytext); return COLON; }
"="             { update_position(yytext); return ASSIGN; }
"+"             { update_position(yytext); return PLUS; }
"-"             { update_position(yytext); return MINUS; }
"*"             { update_position(yytext); return MULTIPLY; }
"/"             { update_position(yytext); return DIVIDE; }
"%"             { update_position(yytext); return MODULO; }
"=="            { update_position(yytext); return EQ; }
"!="            { update_position(yytext); return NE; }
"<"             { update_position(yytext); return LT; }
"<="            { update_position(yytext); return LE; }
">"             { update_position(yytext); return GT; }
">="            { update_position(yytext); return GE; }
"&&"            { update_position(yytext); return AND; }
"||"            { update_position(yytext); return OR; }
"!"             { update_position(yytext); return NOT; }

[ \t\r]+        { update_position(yytext); }
\n              { update_position(yytext); }

"//".*          { update_position(yytext); }
"/*"([^*]|\*+[^*/])*\*+"/" { update_position(yytext); }

.               { update_position(yytext); }

%%
