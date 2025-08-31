#define _GNU_SOURCE
%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parser.tab.h"  // Incluir tokens de Bison

/* Variables globales para manejo de posición */



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
BLOCK_COMMENT_END   \*\/

%%

    /* === PALABRAS RESERVADAS === */
"public"        { update_column(); print_token("PUBLIC", yytext); return PUBLIC; }
"private"       { update_column(); print_token("PRIVATE", yytext); return PRIVATE; }
"protected"     { update_column(); print_token("PROTECTED", yytext); return PROTECTED; }
"static"        { update_column(); print_token("STATIC", yytext); return STATIC; }
"final"         { update_column(); print_token("FINAL", yytext); return FINAL; }
"void"          { update_column(); print_token("VOID", yytext); return VOID; }
"main"          { update_column(); print_token("MAIN", yytext); return MAIN; }

    /* Tipos de datos */
"int"           { update_column(); print_token("INT", yytext); return INT; }
"float"         { update_column(); print_token("FLOAT", yytext); return FLOAT; }
"double"        { update_column(); print_token("DOUBLE", yytext); return DOUBLE; }
"boolean"       { update_column(); print_token("BOOLEAN", yytext); return BOOLEAN; }
"char"          { update_column(); print_token("CHAR", yytext); return CHAR; }
"String"        { update_column(); print_token("STRING_TYPE", yytext); return STRING_TYPE; }

    /* Estructuras de control */
"if"            { update_column(); print_token("IF", yytext); return IF; }
"else"          { update_column(); print_token("ELSE", yytext); return ELSE; }
"switch"        { update_column(); print_token("SWITCH", yytext); return SWITCH; }
"case"          { update_column(); print_token("CASE", yytext); return CASE; }
"default"       { update_column(); print_token("DEFAULT", yytext); return DEFAULT; }
"while"         { update_column(); print_token("WHILE", yytext); return WHILE; }
"for"           { update_column(); print_token("FOR", yytext); return FOR; }
"do"            { update_column(); print_token("DO", yytext); return DO; }

    /* Sentencias de control */
"break"         { update_column(); print_token("BREAK", yytext); return BREAK; }
"continue"      { update_column(); print_token("CONTINUE", yytext); return CONTINUE; }
"return"        { update_column(); print_token("RETURN", yytext); return RETURN; }

    /* Otros */
"null"          { update_column(); print_token("NULL_VAL", yytext); return NULL_VAL; }
"new"           { update_column(); print_token("NEW", yytext); return NEW; }
"this"          { update_column(); print_token("THIS", yytext); return THIS; }
"true"          { update_column(); print_token("TRUE", yytext); yylval.bool_val = true; return TRUE; }
"false"         { update_column(); print_token("FALSE", yytext); yylval.bool_val = false; return FALSE; }

    /* === OPERADORES === */
    
    /* Operadores aritméticos */
"+"             { update_column(); print_token("PLUS", yytext); return PLUS; }
"-"             { update_column(); print_token("MINUS", yytext); return MINUS; }
"*"             { update_column(); print_token("MULTIPLY", yytext); return MULTIPLY; }
"/"             { update_column(); print_token("DIVIDE", yytext); return DIVIDE; }
"%"             { update_column(); print_token("MODULO", yytext); return MODULO; }

    /* Operadores de incremento/decremento */
"++"            { update_column(); print_token("INCREMENT", yytext); return INCREMENT; }
"--"            { update_column(); print_token("DECREMENT", yytext); return DECREMENT; }

    /* Operadores de asignación */
"="             { update_column(); print_token("ASSIGN", yytext); return ASSIGN; }
"+="            { update_column(); print_token("PLUS_ASSIGN", yytext); return PLUS_ASSIGN; }
"-="            { update_column(); print_token("MINUS_ASSIGN", yytext); return MINUS_ASSIGN; }
"*="            { update_column(); print_token("MULT_ASSIGN", yytext); return MULT_ASSIGN; }
"/="            { update_column(); print_token("DIV_ASSIGN", yytext); return DIV_ASSIGN; }
"%="            { update_column(); print_token("MOD_ASSIGN", yytext); return MOD_ASSIGN; }

    /* Operadores de comparación */
"=="            { update_column(); print_token("EQUAL", yytext); return EQUAL; }
"!="            { update_column(); print_token("NOT_EQUAL", yytext); return NOT_EQUAL; }
"<"             { update_column(); print_token("LESS", yytext); return LESS; }
"<="            { update_column(); print_token("LESS_EQUAL", yytext); return LESS_EQUAL; }
">"             { update_column(); print_token("GREATER", yytext); return GREATER; }
">="            { update_column(); print_token("GREATER_EQUAL", yytext); return GREATER_EQUAL; }

    /* Operadores lógicos */
"&&"            { update_column(); print_token("AND", yytext); return AND; }
"||"            { update_column(); print_token("OR", yytext); return OR; }
"!"             { update_column(); print_token("NOT", yytext); return NOT; }

    /* Operadores bitwise */
"&"             { update_column(); print_token("BIT_AND", yytext); return BIT_AND; }
"|"             { update_column(); print_token("BIT_OR", yytext); return BIT_OR; }
"^"             { update_column(); print_token("BIT_XOR", yytext); return BIT_XOR; }
"~"             { update_column(); print_token("BIT_NOT", yytext); return BIT_NOT; }
"<<"            { update_column(); print_token("LEFT_SHIFT", yytext); return LEFT_SHIFT; }
">>"            { update_column(); print_token("RIGHT_SHIFT", yytext); return RIGHT_SHIFT; }

    /* === DELIMITADORES === */
"("             { update_column(); print_token("LPAREN", yytext); return LPAREN; }
")"             { update_column(); print_token("RPAREN", yytext); return RPAREN; }
"{"             { update_column(); print_token("LBRACE", yytext); return LBRACE; }
"}"             { update_column(); print_token("RBRACE", yytext); return RBRACE; }
"["             { update_column(); print_token("LBRACKET", yytext); return LBRACKET; }
"]"             { update_column(); print_token("RBRACKET", yytext); return RBRACKET; }
";"             { update_column(); print_token("SEMICOLON", yytext); return SEMICOLON; }
","             { update_column(); print_token("COMMA", yytext); return COMMA; }
"."             { update_column(); print_token("DOT", yytext); return DOT; }
":"             { update_column(); print_token("COLON", yytext); return COLON; }
"?"             { update_column(); print_token("QUESTION", yytext); return QUESTION; }

    /* === FUNCIONES EMBEBIDAS === */
"println"       { update_column(); print_token("PRINTLN", yytext); return PRINTLN; }
"print"         { update_column(); print_token("PRINT", yytext); return PRINT; }
"parseInt"      { update_column(); print_token("PARSE_INT", yytext); return PARSE_INT; }
"parseFloat"    { update_column(); print_token("PARSE_FLOAT", yytext); return PARSE_FLOAT; }
"parseDouble"   { update_column(); print_token("PARSE_DOUBLE", yytext); return PARSE_DOUBLE; }
"valueOf"       { update_column(); print_token("VALUE_OF", yytext); return VALUE_OF; }
"join"          { update_column(); print_token("STRING_JOIN", yytext); return STRING_JOIN; }
"indexOf"       { update_column(); print_token("ARRAY_INDEX_OF", yytext); return ARRAY_INDEX_OF; }

    /* === LITERALES === */

    /* Literales enteros */
{INTEGER}       { 
                    update_column(); 
                    print_token("INT_LITERAL", yytext); 
                    yylval.int_val = atoi(yytext); 
                    return INT_LITERAL; 
                }

    /* Literales de punto flotante */
{FLOAT}         { 
                    update_column(); 
                    print_token("FLOAT_LITERAL", yytext); 
                    yylval.float_val = atof(yytext); 
                    return FLOAT_LITERAL; 
                }

    /* Literales de caracteres */
{CHAR_LITERAL}  { 
                    update_column(); 
                    print_token("CHAR_LITERAL", yytext); 
                    char c = yytext[1];
                    if (c == '\\') {
                        switch(yytext[2]) {
                            case 'n': c = '\n'; break;
                            case 't': c = '\t'; break;
                            case 'r': c = '\r'; break;
                            case 'b': c = '\b'; break;
                            case 'f': c = '\f'; break;
                            case '\\': c = '\\'; break;
                            case '\'': c = '\''; break;
                            case '"': c = '"'; break;
                            default: c = yytext[2]; break;
                        }
                    }
                    yylval.char_val = c; 
                    return CHAR_LITERAL; 
                }

    /* Literales de cadena */
{STRING_LITERAL} { 
                    update_column(); 
                    print_token("STRING_LITERAL", yytext); 
                    int len = strlen(yytext);
                    char *str = malloc(len - 1);
                    if (str) {
                        strncpy(str, yytext + 1, len - 2);
                        str[len - 2] = '\0';
                    }
                    yylval.str_val = str; 
                    return STRING_LITERAL; 
                }

    /* Identificadores */
{IDENTIFIER}    { 
                    update_column(); 
                    print_token("IDENTIFIER", yytext); 
                    yylval.str_val = strdup(yytext); 
                    return IDENTIFIER; 
                }

    /* === MANEJO DE ESPACIOS Y COMENTARIOS === */

    /* Espacios en blanco */
{WHITESPACE}    { col_num += yyleng; }

    /* Nueva línea */
{NEWLINE}       { 
                    line_num++; 
                    col_num = 1; 
                }

    /* Comentarios de línea */
{LINE_COMMENT}  { 
                    col_num += yyleng; 
                    print_token("LINE_COMMENT", yytext); 
                }

    /* Comentarios de bloque */
{BLOCK_COMMENT_START} { 
                    col_num += yyleng; 
                    print_token("BLOCK_COMMENT_START", yytext);
                    
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
                    
                    if (c == EOF) {
                        add_error(ERROR_LEXICAL, "Comentario de bloque no cerrado", "Global", line_num, col_num);
                    }
                }

    /* Carácter no reconocido */
.               { 
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Carácter no reconocido: '%c'", yytext[0]);
                    add_error(ERROR_LEXICAL, error_msg, "Global", line_num, col_num);
                    update_column(); 
                    printf("ERROR: Carácter no reconocido '%c' en línea %d, columna %d\n", 
                           yytext[0], line_num, col_num - 1);
                }

%%

#ifdef TEST_LEXER
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
    token_count = 0;
    
    printf("🔍 Analizando archivo: %s\n", argv[1]);
    printf("==============================\n");
    printf("TOKEN           | LEXEME               | LINE | COL\n");
    printf("----------------|----------------------|------|----\n");

    int token;
    while ((token = yylex()) != 0) {
    }

    printf("==============================\n");
    printf("✅ Análisis léxico completado\n");
    printf("📊 Total de tokens: %d\n", token_count);
    printf("📍 Líneas procesadas: %d\n", line_num);
    
    if (error_count > 0) {
        print_errors();
    } else {
        printf("🎉 Sin errores léxicos encontrados\n");
    }

    fclose(file);
    return 0;
}
#endif