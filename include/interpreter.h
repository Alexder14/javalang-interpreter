#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include "ast.h"

/* Intérprete del AST de JavaLang.
 *
 * Se ejecuta DESPUÉS del análisis semántico (sin errores). Evalúa el programa
 * recorriendo el AST: variables con valor, aritmética, cadenas, arreglos,
 * if/while/do-while/for/switch, funciones (con recursión) y System.out.println.
 *
 * Los errores en ejecución (división entre cero, índice fuera de rango, etc.)
 * se registran con add_error(ERROR_RUNTIME, ...) y detienen la ejecución.
 */

/* Ejecuta el programa. La salida de println/print se escribe en `out`.
 * Devuelve 0 si terminó bien, 1 si hubo un error en ejecución. */
int interpret_program(ASTNode *root, FILE *out);

/* Tabla de símbolos con los valores finales (de la última ejecución). */
int  interpreter_symbol_count(void);
void interpreter_write_symbol_table(FILE *f);

/* Libera toda la memoria de la última ejecución. */
void interpreter_reset(void);

#endif
