#!/bin/bash
echo "🚀 Compilando JavaLang..."
gcc -Wall -std=c99 -g -Iinclude -o javalang_interpreter src/main.c src/common.c
flex -o lexer/lex.yy.c lexer/lexer.l
gcc -DTEST_LEXER -Wall -std=c99 -g -Iinclude -o test_lexer lexer/lex.yy.c src/common.c -lfl
echo "✅ ¡Listo!"
