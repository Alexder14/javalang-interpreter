%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/* Variables globales para manejo de posición */
extern int line_num;
extern int col_num;

/* Funciones auxiliares */
void update_column();
void print_token(const char* token_type, const char* lexeme);

/* Contador de tokens para estadísticas */
int token_count = 0;
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
"public"        { print_token("PUBLIC", yytext); return 1; }
"private"       { print_token("PRIVATE", yytext); return 2; }
"protected"     { print_token("PROTECTED", yytext); return 3; }
"static"        { print_token("STATIC", yytext); return 4; }
"final"         { print_token("FINAL", yytext); return 5; }
"void"          { print_token("VOID", yytext); return 6; }
"main"          { print_token("MAIN", yytext); return 7; }

    /* Tipos de datos */
"int"           { print_token("INT", yytext); return 8; }
"float"         { print_token("FLOAT", yytext); return 9; }
"double"        { print_token("DOUBLE", yytext); return 10; }
"boolean"       { print_token("BOOLEAN", yytext); return 11; }
"char"          { print_token("CHAR", yytext); return 12; }
"String"        { print_token("STRING_TYPE", yytext); return 13; }

    /* Estructuras de control */
"if"            { print_token("IF", yytext); return 14; }
"else"          { print_token("ELSE", yytext); return 15; }
"switch"        { print_token("SWITCH", yytext); return 16; }
"case"          { print_token("CASE", yytext); return 17; }
"default"       { print_token("DEFAULT", yytext); return 18; }
"while"         { print_token("WHILE", yytext); return 19; }
"for"           { print_token("FOR", yytext); return 20; }
"do"            { print_token("DO", yytext); return 21; }

    /* Sentencias de transferencia */
"break"         { print_token("BREAK", yytext); return 22; }
"continue"      { print_token("CONTINUE", yytext); return 23; }
"return"        { print_token("RETURN", yytext); return 24; }

    /* Valores literales */
"true"          { print_token("TRUE", yytext); return 25; }
"false"         { print_token("FALSE", yytext); return 26; }
"null"          { print_token("NULL", yytext); return 27; }

    /* Palabras clave para arreglos y objetos */
"new"           { print_token("NEW", yytext); return 28; }
"this"          { print_token("THIS", yytext); return 29; }

    /* === OPERADORES ARITMÉTICOS === */
"+"             { print_token("PLUS", yytext); return 30; }
"-"             { print_token("MINUS", yytext); return 31; }
"*"             { print_token("MULTIPLY", yytext); return 32; }
"/"             { print_token("DIVIDE", yytext); return 33; }
"%"             { print_token("MODULO", yytext); return 34; }

    /* Operadores de incremento/decremento */
"++"            { print_token("INCREMENT", yytext); return 35; }
"--"            { print_token("DECREMENT", yytext); return 36; }

    /* === OPERADORES DE ASIGNACIÓN === */
"="             { print_token("ASSIGN", yytext); return 37; }
"+="            { print_token("PLUS_ASSIGN", yytext); return 38; }
"-="            { print_token("MINUS_ASSIGN", yytext); return 39; }
"*="            { print_token("MULT_ASSIGN", yytext); return 40; }
"/="            { print_token("DIV_ASSIGN", yytext); return 41; }
"%="            { print_token("MOD_ASSIGN", yytext); return 42; }

    /* === OPERADORES RELACIONALES === */
"=="            { print_token("EQUAL", yytext); return 43; }
"!="            { print_token("NOT_EQUAL", yytext); return 44; }
"<"             { print_token("LESS", yytext); return 45; }
"<="            { print_token("LESS_EQUAL", yytext); return 46; }
">"             { print_token("GREATER", yytext); return 47; }
">="            { print_token("GREATER_EQUAL", yytext); return 48; }

    /* === OPERADORES LÓGICOS === */
"&&"            { print_token("AND", yytext); return 49; }
"||"            { print_token("OR", yytext); return 50; }
"!"             { print_token("NOT", yytext); return 51; }

    /* === OPERADORES BIT A BIT === */
"&"             { print_token("BIT_AND", yytext); return 52; }
"|"             { print_token("BIT_OR", yytext); return 53; }
"^"             { print_token("BIT_XOR", yytext); return 54; }
"~"             { print_token("BIT_NOT", yytext); return 55; }
"<<"            { print_token("LEFT_SHIFT", yytext); return 56; }
">>"            { print_token("RIGHT_SHIFT", yytext); return 57; }

    /* === DELIMITADORES === */
"("             { print_token("LPAREN", yytext); return 58; }
")"             { print_token("RPAREN", yytext); return 59; }
"{"             { print_token("LBRACE", yytext); return 60; }
"}"             { print_token("RBRACE", yytext); return 61; }
"["             { print_token("LBRACKET", yytext); return 62; }
"]"             { print_token("RBRACKET", yytext); return 63; }
";"             { print_token("SEMICOLON", yytext); return 64; }
","             { print_token("COMMA", yytext); return 65; }
"."             { print_token("DOT", yytext); return 66; }
":"             { print_token("COLON", yytext); return 67; }
"?"             { print_token("QUESTION", yytext); return 68; }

    /* === LITERALES === */
{INTEGER}       { 
                    print_token("INT_LITERAL", yytext); 
                    return 69; 
                }

{FLOAT}         { 
                    print_token("FLOAT_LITERAL", yytext); 
                    return 70; 
                }

{CHAR_LITERAL}  { 
                    print_token("CHAR_LITERAL", yytext); 
                    return 71; 
                }

{STRING_LITERAL} { 
                    print_token("STRING_LITERAL", yytext); 
                    return 72; 
                }

    /* === IDENTIFICADORES === */
{IDENTIFIER}    { 
                    print_token("IDENTIFIER", yytext); 
                    return 73; 
                }

    /* === FUNCIONES EMBEBIDAS DE JAVALANG === */
"System.out.println"    { print_token("PRINTLN", yytext); return 74; }
"System.out.print"      { print_token("PRINT", yytext); return 75; }
"Integer.parseInt"      { print_token("PARSE_INT", yytext); return 76; }
"Float.parseFloat"      { print_token("PARSE_FLOAT", yytext); return 77; }
"Double.parseDouble"    { print_token("PARSE_DOUBLE", yytext); return 78; }
"String.valueOf"        { print_token("VALUE_OF", yytext); return 79; }
"String.join"           { print_token("STRING_JOIN", yytext); return 80; }
"Arrays.indexOf"        { print_token("ARRAY_INDEX_OF", yytext); return 81; }

    /* === MANEJO DE ESPACIOS Y COMENTARIOS === */
{WHITESPACE}    { 
                    col_num += yyleng; 
                    /* No retornar token para espacios */ 
                }

{NEWLINE}       { 
                    line_num++; 
                    col_num = 1; 
                    /* No retornar token para saltos de línea */ 
                }

{LINE_COMMENT}  { 
                    /* Ignorar comentarios de línea */
                    col_num += yyleng;
                }

{BLOCK_COMMENT_START} {
                    /* Manejar comentarios de bloque */
                    int c1, c2;
                    col_num += 2;
                    
                    while ((c1 = input()) != EOF) {
                        if (c1 == '\n') {
                            line_num++;
                            col_num = 1;
                        } else {
                            col_num++;
                        }
                        
                        if (c1 == '*') {
                            if ((c2 = input()) == '/') {
                                col_num++;
                                break;
                            } else {
                                unput(c2);
                            }
                        }
                    }
                }

    /* === MANEJO DE ERRORES === */
.               { 
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), 
                            "Carácter no reconocido: '%s'", yytext);
                    add_error(ERROR_LEXICAL, error_msg, "Global", line_num, col_num);
                    print_token("ERROR", yytext);
                    col_num++;
                    return -1;
                }

%%

/* === FUNCIONES AUXILIARES === */

void update_column() {
    col_num += yyleng;
}

void print_token(const char* token_type, const char* lexeme) {
    token_count++;
    printf("%-20s | %-30s | Línea: %3d | Columna: %3d\n", 
           token_type, lexeme, line_num, col_num);
    col_num += strlen(lexeme);
}

/* Función principal para pruebas del lexer */
#ifdef TEST_LEXER
int main(int argc, char **argv) {
    printf("=== ANALIZADOR LÉXICO JAVALANG ===\n");
    printf("Universidad San Carlos de Guatemala\n");
    printf("Organización de Lenguajes y Compiladores 2\n\n");
    
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error abriendo archivo");
            return 1;
        }
        yyin = file;
        printf("Analizando archivo: %s\n\n", argv[1]);
    } else {
        printf("Analizando entrada estándar...\n\n");
    }
    
    printf("%-20s | %-30s | %-12s | %s\n", 
           "TIPO DE TOKEN", "LEXEMA", "LÍNEA", "COLUMNA");
    printf("-----|-----|-----|-----\n");
    
    /* Inicializar contadores */
    line_num = 1;
    col_num = 1;
    token_count = 0;
    clear_errors();
    
    int token;
    while ((token = yylex()) > 0) {
        /* Los tokens se imprimen dentro de yylex() */
    }
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    printf("\n=== ESTADÍSTICAS ===\n");
    printf("Total de tokens reconocidos: %d\n", token_count);
    printf("Total de líneas procesadas: %d\n", line_num);
    
    if (has_errors) {
        print_errors();
    } else {
        printf("✅ Análisis léxico completado sin errores\n");
    }
    
    return 0;
}
#endif