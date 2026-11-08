# JavaLang Compiler / Interpreter

Compilador e intérprete educativo para el lenguaje JavaLang (curso Organización de Lenguajes y Compiladores 2).

## Fases implementadas

- **Fase 2**: análisis léxico (Flex) — `lexer/lexer.l`
- **Fase 3**: análisis sintáctico y AST (Bison) — `parser/parser.y`, `src/ast.c`
- **Fase 4**: análisis semántico y tabla de símbolos — `src/semantic.c`
- **Fase 5**: intérprete (ejecución del AST) — `src/interpreter.c`

Si el análisis semántico no encuentra errores, el programa se **ejecuta**: variables con valor,
aritmética, cadenas, arreglos, `if/else`, `while`, `do-while`, `for`, `switch`, funciones con
recursión y `System.out.println/print`. Los errores en ejecución (división entre cero, índice fuera
de rango, bucle infinito, recursión desbordada) se reportan con línea y columna.

## Requisitos

`gcc`, `make`, `flex`, `bison`

## Uso

```bash
make                                  # compila ./javalang_interpreter
./javalang_interpreter archivo.usl    # analiza, ejecuta y genera reportes
make clean
```

Ejemplo (`tests/run/precedencia.usl`):

```text
▶️  Ejecutando código
a + b * b = 7
a - b / b = 2
b1 && b2 || b2 = false
✅ Ejecución finalizada
```

Reportes que se generan junto al directorio de ejecución:
`<archivo>_errors.txt`, `<archivo>_ast.txt` y `<archivo>_symbols.txt` (tabla de símbolos con
**ID, Scope, tipo, valor final y función**).

## Cambiar la precedencia de operadores

La precedencia está en `parser/parser.y` (bloque `%left`). Para ver el efecto de intercambiar la de
`+ -` con la de `* / %` sin editar el parser:

```bash
make precedencia-invertida
./javalang_interpreter_inv tests/run/precedencia.usl   # a + b * b = 10, a - b / b = 0
```

## Pruebas

```bash
make check-ejemplos   # examples/ y tests/test_files/ deben compilar; los *error* deben fallar
make check-ejecucion  # tests/run/*.usl: la salida debe coincidir con su .out
```

## Lenguaje

`public static void main(String[] args) { ... }`, funciones (a nivel superior, con o sin
`public static`), tipos `int float double boolean char String`, arreglos 1D (`new int[n]` o
`{1, 2, 3}`), operadores aritméticos, lógicos, de comparación y de bits, `++ --`, `+= -= *= /= %=`.
Una clase envolvente (`public class X { ... }`) no forma parte de la gramática.
