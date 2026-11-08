# JavaLang Compiler / Interpreter

Intérprete educativo para el lenguaje JavaLang (sintaxis tipo Java, archivos `.usl`), hecho en C con
Flex y Bison para el curso Organización de Lenguajes y Compiladores 2 (USAC).

## Fases

| Fase | Archivos |
|------|----------|
| Análisis léxico (Flex) | `lexer/lexer.l` |
| Análisis sintáctico y AST (Bison) | `parser/parser.y`, `src/ast.c` |
| Análisis semántico y tabla de símbolos | `src/semantic.c` |
| Intérprete (ejecución del AST) | `src/interpreter.c` |
| Reportes (errores, símbolos, AST en Graphviz) | `src/common.c`, `src/interpreter.c`, `src/ast_dot.c` |

Si el análisis semántico no encuentra errores, el programa se **ejecuta** buscando
`public static void main()`.

## Requisitos

`gcc`, `make`, `flex`, `bison` y, para dibujar el grafo del AST, `graphviz` (`sudo apt install graphviz`).

## Uso

```bash
make                                  # compila ./javalang_interpreter
./javalang_interpreter archivo.usl    # analiza, ejecuta y genera los reportes
make clean
```

## Lenguaje soportado

- **Tipos:** `int float double boolean char String`, con sus valores por defecto; `null`; casting
  `(int) x`; widening automático `char → int → float → double`.
- **Constantes:** `final int K = 3;` (reasignarlas es un error).
- **Operadores:** aritméticos, relacionales, lógicos (`&& || !`), de bits (`& | ^ ~ << >>`),
  `++ --` y asignaciones compuestas (`+= -= *= /= %= &= |= ^= <<= >>=`).
- **Control de flujo:** `if / else if / else`, `while`, `do-while`, `for`, **for-each**
  (`for (int n : numeros)`), `switch / case / default`, `break`, `continue`, `return`.
- **Funciones:** con o sin parámetros, con valor de retorno, recursivas, ámbito local; se pueden
  declarar `public static`, `public` o sin modificadores.
- **Arreglos:** `int[] a = new int[5]`, `int[] a = {1, 2, 3}`, **multidimensionales**
  (`int[][] m = new int[3][4]`, `int m[][] = {{1, 2}, {3, 4}}`, N dimensiones), acceso `m[1][2]`,
  `a.length`, `a.add(x)` (devuelve un arreglo nuevo con el elemento al final).
- **Funciones integradas:** `System.out.println/print`, `Integer.parseInt`, `Float.parseFloat`,
  `Double.parseDouble`, `String.valueOf`, `String.join(delim, a, b, …)` / `String.join(delim, arreglo)`,
  `Arrays.indexOf(arreglo, clave)`, `texto.equals(otro)`.
- Comentarios `//` y `/* */`, secuencias de escape `\n \t \r \" \\`.

## Reportes

Se generan junto al directorio desde el que se ejecuta, con el nombre del archivo de entrada:

| Archivo | Contenido |
|---------|-----------|
| `<nombre>_errors.txt` | Tabla de errores: No., Descripción, Ámbito, Línea, Columna (léxicos, sintácticos, semánticos y de ejecución) |
| `<nombre>_symbols.txt` | Tabla de símbolos tras la ejecución: ID, Tipo símbolo (Variable / Parámetro / Constante / Función), Tipo dato, Ámbito, Línea, Columna y **Valor final** |
| `<nombre>_ast.dot` y `<nombre>_ast.png` | AST como grafo (Graphviz); el `.png` se genera si `dot` está instalado |
| `<nombre>_ast.txt` | AST como texto con sangría |

## Cambiar la precedencia de operadores

La precedencia está en el bloque `%left` de `parser/parser.y`. Para ver el efecto de intercambiar
`+ -` con `* / %` sin editar el parser:

```bash
make precedencia-invertida
./javalang_interpreter_inv tests/run/precedencia.usl   # a + b * b = 10 en vez de 7
```

## Pruebas

```bash
make check-ejemplos   # examples/ y tests/test_files/: compilan; los *error* deben fallar
make check-ejecucion  # tests/run/*.usl: la salida debe coincidir con su .out
make check-semantica  # tests/semantica/*.usl: cada error debe reportar el mensaje de su .msg
make check-reportes   # se generan los reportes (errores, símbolos, AST)
make check-todo       # las cuatro anteriores
```

Las salidas esperadas de `tests/run` están calculadas a mano, no copiadas del programa.

## Licencia

MIT. Ver [LICENSE](LICENSE).
