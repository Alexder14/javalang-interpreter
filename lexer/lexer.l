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

