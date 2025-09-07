%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#ifdef TEST_PARSER
#include "parser.tab.h"
#elif defined(TEST_SEMANTIC)
#include "parser.tab.h"
#else
// Para test del lexer standalone, definir tokens como constantes
#define PUBLIC 1
#define PRIVATE 2
#define PROTECTED 3
#define STATIC 4
#define FINAL 5
#define VOID 6
#define MAIN 7
#define INT 8
#define FLOAT 9
#define DOUBLE 10
#define BOOLEAN 11
#define CHAR 12
#define STRING_TYPE 13
#define IF 14
#define ELSE 15
#define SWITCH 16
#define CASE 17
#define DEFAULT 18
#define WHILE 19
#define FOR 20
#define DO 21
#define BREAK 22
#define CONTINUE 23
#define RETURN 24
#define NULL_VAL 25
#define NEW 26
#define THIS 27
#define TRUE 28
#define FALSE 29
#define PLUS 30
#define MINUS 31
#define MULTIPLY 32
#define DIVIDE 33
#define MODULO 34
#define INCREMENT 35
#define DECREMENT 36
#define ASSIGN 37
#define PLUS_ASSIGN 38
#define MINUS_ASSIGN 39
#define MULT_ASSIGN 40
#define DIV_ASSIGN 41
#define MOD_ASSIGN 42
#define EQUAL 43
#define NOT_EQUAL 44
#define LESS 45
#define LESS_EQUAL 46
#define GREATER 47
#define GREATER_EQUAL 48
#define AND 49
#define OR 50
#define NOT 51
#define BIT_AND 52
#define BIT_OR 53
#define BIT_XOR 54
#define BIT_NOT 55
#define LEFT_SHIFT 56
#define RIGHT_SHIFT 57
#define LPAREN 58
#define RPAREN 59
#define LBRACE 60
#define RBRACE 61
#define LBRACKET 62
#define RBRACKET 63
#define SEMICOLON 64
#define COMMA 65
#define DOT 66
#define COLON 67
#define QUESTION 68
#define PRINTLN 69
#define PRINT 70
#define PARSE_INT 71
#define PARSE_FLOAT 72
#define PARSE_DOUBLE 73
#define VALUE_OF 74
#define STRING_JOIN 75
#define ARRAY_INDEX_OF 76
#define IDENTIFIER 77
#define STRING_LITERAL 78
#define INT_LITERAL 79
#define FLOAT_LITERAL 80
#define CHAR_LITERAL 81
#endif


/* Funciones auxiliares */
void update_column();
void print_token(const char* token_type, const char* lexeme);

/* Contador de tokens para estadísticas */
int token_count = 0;

/* Variable global para valor de tokens */
#ifdef TEST_PARSER
extern YYSTYPE yylval;
#elif defined(TEST_SEMANTIC)
extern YYSTYPE yylval;
#endif

%}

/* Expresiones regulares básicas */
DIGIT           [0-9]
LETTER          [a-zA-Z]
IDENTIFIER_CHAR [a-zA-Z0-9_]
NEWLINE         \n
WHITESPACE      [ \t\r]

/* Literales numéricos */
INTEGER         {DIGIT}+
FLOAT           {DIGIT}+\.{DIGIT}+
EXPONENTIAL     {DIGIT}+(\.{DIGIT}+)?[eE][+-]?{DIGIT}+

/* Literales de caracteres y cadenas */
CHAR_CONTENT    [^'\\]|\\[\\'"nrtbfav0]|\\x[0-9a-fA-F]{2}|\\[0-7]{1,3}
STRING_CONTENT  [^"\\]|\\[\\'"nrtbfav0]|\\x[0-9a-fA-F]{2}|\\[0-7]{1,3}

/* Espacios en blanco */
WHITESPACE_PATTERN {WHITESPACE}+

/* Comentarios */
SINGLE_LINE_COMMENT "//".*
MULTI_LINE_COMMENT  "/*"([^*]|\*+[^*/])*\*+"/"

%%

{WHITESPACE_PATTERN}    { 
    col_num += yyleng; 
}

{NEWLINE}               { 
    line_num++; 
    col_num = 1; 
}

{SINGLE_LINE_COMMENT}   { 
    update_column();
    #ifdef TEST_LEXER
    print_token("COMMENT", yytext);
    #endif
}

{MULTI_LINE_COMMENT}    { 
    // Contar líneas en comentarios multi-línea
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == '\n') {
            line_num++;
            col_num = 1;
        } else {
            col_num++;
        }
    }
    #ifdef TEST_LEXER
    print_token("COMMENT", "/* ... */");
    #endif
}

"public"                { update_column(); return PUBLIC; }
"private"               { update_column(); return PRIVATE; }
"protected"             { update_column(); return PROTECTED; }
"static"                { update_column(); return STATIC; }
"final"                 { update_column(); return FINAL; }
"void"                  { update_column(); return VOID; }
"main"                  { update_column(); return MAIN; }

"int"                   { update_column(); return INT; }
"float"                 { update_column(); return FLOAT; }
"double"                { update_column(); return DOUBLE; }
"boolean"               { update_column(); return BOOLEAN; }
"char"                  { update_column(); return CHAR; }
"String"                { update_column(); return STRING_TYPE; }

"if"                    { update_column(); return IF; }
"else"                  { update_column(); return ELSE; }
"switch"                { update_column(); return SWITCH; }
"case"                  { update_column(); return CASE; }
"default"               { update_column(); return DEFAULT; }
"while"                 { update_column(); return WHILE; }
"for"                   { update_column(); return FOR; }
"do"                    { update_column(); return DO; }
"break"                 { update_column(); return BREAK; }
"continue"              { update_column(); return CONTINUE; }
"return"                { update_column(); return RETURN; }

"null"                  { update_column(); return NULL_VAL; }
"new"                   { update_column(); return NEW; }
"this"                  { update_column(); return THIS; }
"true"                  { 
    update_column(); 
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.bool_val = true;
    #endif
    return TRUE; 
}
"false"                 { 
    update_column(); 
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.bool_val = false;
    #endif
    return FALSE; 
}

"System.out.println"    { update_column(); return PRINTLN; }
"System.out.print"      { update_column(); return PRINT; }
"Integer.parseInt"      { update_column(); return PARSE_INT; }
"Float.parseFloat"      { update_column(); return PARSE_FLOAT; }
"Double.parseDouble"    { update_column(); return PARSE_DOUBLE; }
"String.valueOf"        { update_column(); return VALUE_OF; }
"String.join"           { update_column(); return STRING_JOIN; }
"Arrays.indexOf"        { update_column(); return ARRAY_INDEX_OF; }

"++"                    { update_column(); return INCREMENT; }
"--"                    { update_column(); return DECREMENT; }
"+="                    { update_column(); return PLUS_ASSIGN; }
"-="                    { update_column(); return MINUS_ASSIGN; }
"*="                    { update_column(); return MULT_ASSIGN; }
"/="                    { update_column(); return DIV_ASSIGN; }
"%="                    { update_column(); return MOD_ASSIGN; }
"=="                    { update_column(); return EQUAL; }
"!="                    { update_column(); return NOT_EQUAL; }
"<="                    { update_column(); return LESS_EQUAL; }
">="                    { update_column(); return GREATER_EQUAL; }
"&&"                    { update_column(); return AND; }
"||"                    { update_column(); return OR; }
"<<"                    { update_column(); return LEFT_SHIFT; }
">>"                    { update_column(); return RIGHT_SHIFT; }

"+"                     { update_column(); return PLUS; }
"-"                     { update_column(); return MINUS; }
"*"                     { update_column(); return MULTIPLY; }
"/"                     { update_column(); return DIVIDE; }
"%"                     { update_column(); return MODULO; }
"="                     { update_column(); return ASSIGN; }
"<"                     { update_column(); return LESS; }
">"                     { update_column(); return GREATER; }
"!"                     { update_column(); return NOT; }
"&"                     { update_column(); return BIT_AND; }
"|"                     { update_column(); return BIT_OR; }
"^"                     { update_column(); return BIT_XOR; }
"~"                     { update_column(); return BIT_NOT; }

"("                     { update_column(); return LPAREN; }
")"                     { update_column(); return RPAREN; }
"{"                     { update_column(); return LBRACE; }
"}"                     { update_column(); return RBRACE; }
"["                     { update_column(); return LBRACKET; }
"]"                     { update_column(); return RBRACKET; }
";"                     { update_column(); return SEMICOLON; }
","                     { update_column(); return COMMA; }
"."                     { update_column(); return DOT; }
":"                     { update_column(); return COLON; }
"?"                     { update_column(); return QUESTION; }

{INTEGER}               { 
    update_column();
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.int_val = atoi(yytext);
    #endif
    #ifdef TEST_LEXER
    print_token("INT_LITERAL", yytext);
    #endif
    return INT_LITERAL; 
}

{FLOAT}|{EXPONENTIAL}   { 
    update_column();
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.float_val = atof(yytext);
    #endif
    #ifdef TEST_LEXER
    print_token("FLOAT_LITERAL", yytext);
    #endif
    return FLOAT_LITERAL; 
}

'{CHAR_CONTENT}'        { 
    update_column();
    char ch;
    if (yytext[1] == '\\') {
        // Carácter de escape
        switch (yytext[2]) {
            case 'n': ch = '\n'; break;
            case 't': ch = '\t'; break;
            case 'r': ch = '\r'; break;
            case 'b': ch = '\b'; break;
            case 'f': ch = '\f'; break;
            case 'a': ch = '\a'; break;
            case 'v': ch = '\v'; break;
            case '0': ch = '\0'; break;
            case '\\': ch = '\\'; break;
            case '\'': ch = '\''; break;
            case '"': ch = '"'; break;
            default: ch = yytext[2]; break;
        }
    } else {
        ch = yytext[1];
    }
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.char_val = ch;
    #endif
    #ifdef TEST_LEXER
    print_token("CHAR_LITERAL", yytext);
    #endif
    return CHAR_LITERAL; 
}

\"{STRING_CONTENT}*\"   { 
    update_column();
    // Remover comillas y procesar caracteres de escape
    char *str = malloc(yyleng - 1);
    int j = 0;
    for (int i = 1; i < yyleng - 1; i++) {
        if (yytext[i] == '\\' && i + 1 < yyleng - 1) {
            switch (yytext[i + 1]) {
                case 'n': str[j++] = '\n'; break;
                case 't': str[j++] = '\t'; break;
                case 'r': str[j++] = '\r'; break;
                case 'b': str[j++] = '\b'; break;
                case 'f': str[j++] = '\f'; break;
                case 'a': str[j++] = '\a'; break;
                case 'v': str[j++] = '\v'; break;
                case '0': str[j++] = '\0'; break;
                case '\\': str[j++] = '\\'; break;
                case '\'': str[j++] = '\''; break;
                case '"': str[j++] = '"'; break;
                default: str[j++] = yytext[i + 1]; break;
            }
            i++; // Saltar el siguiente carácter
        } else {
            str[j++] = yytext[i];
        }
    }
    str[j] = '\0';
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.str_val = str;
    #endif
    #ifdef TEST_LEXER
    print_token("STRING_LITERAL", yytext);
    free(str);
    #endif
    return STRING_LITERAL; 
}

{LETTER}{IDENTIFIER_CHAR}* { 
    update_column();
    #if defined(TEST_PARSER) || defined(TEST_SEMANTIC)
    yylval.str_val = strdup(yytext);
    #endif
    #ifdef TEST_LEXER
    print_token("IDENTIFIER", yytext);
    #endif
    return IDENTIFIER; 
}

.                       { 
    update_column();
    char error_msg[100];
    snprintf(error_msg, sizeof(error_msg), "Carácter no válido: '%c' (ASCII %d)", yytext[0], yytext[0]);
    add_error(ERROR_LEXICAL, error_msg, "Global", line_num, col_num);
    #ifdef TEST_LEXER
    printf("❌ Error léxico en línea %d, columna %d: %s\n", line_num, col_num, error_msg);
    #endif
}

%%

void update_column() {
    col_num += yyleng;
    token_count++;
}

void print_token(const char* token_type, const char* lexeme) {
    printf("%-15s: %-20s (línea %d, columna %d)\n", 
           token_type, lexeme, line_num, col_num - yyleng);
}

int yywrap() {
    return 1;
}

#ifdef TEST_LEXER

int main(int argc, char **argv) {
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     TEST ANALIZADOR LÉXICO JAVALANG                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
    
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.usl>\n", argv[0]);
        return 1;
    }
    
    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        fprintf(stderr, "❌ Error: No se pudo abrir el archivo '%s'\n", filename);
        return 1;
    }
    
    printf("📁 Analizando archivo: %s\n", filename);
    printf("═══════════════════════════════════════════════════════════════════════════\n\n");
    
    yyin = file;
    line_num = 1;
    col_num = 1;
    token_count = 0;
    
    clear_errors();
    
    printf("🔍 Tokens encontrados:\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    
    int token;
    while ((token = yylex()) != 0) {
        // Los tokens se imprimen automáticamente en print_token()
    }
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("📊 RESUMEN DEL ANÁLISIS LÉXICO\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    
    printf("📈 ESTADÍSTICAS:\n");
    printf("   • Archivo procesado: %s\n", filename);
    printf("   • Líneas analizadas: %d\n", line_num);
    printf("   • Tokens reconocidos: %d\n", token_count);
    printf("   • Errores léxicos: %d\n", error_count);
    
    if (error_count > 0) {
        printf("\n❌ ERRORES ENCONTRADOS:\n");
        print_errors();
        printf("\n❌ Análisis léxico FALLÓ\n");
    } else {
        printf("\n✅ Análisis léxico EXITOSO\n");
        printf("✅ Todos los tokens fueron reconocidos correctamente\n");
    }
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("🏁 ANÁLISIS LÉXICO COMPLETADO\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    
    fclose(file);
    
    return error_count > 0 ? 1 : 0;
}

#endif