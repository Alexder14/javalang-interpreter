# JavaLang Compiler

Compilador educativo para el lenguaje JavaLang (curso Organización de Lenguajes y Compiladores 2).

## Fases implementadas

- **Fase 2**: análisis léxico (Flex) — `lexer/lexer.l`
- **Fase 3**: análisis sintáctico y AST (Bison) — `parser/parser.y`, `src/ast.c`
- **Fase 4**: análisis semántico y tabla de símbolos — `src/semantic.c`

## Requisitos

`gcc`, `make`, `flex`, `bison`

## Uso

```bash
make                                  # compila ./javalang_interpreter
./javalang_interpreter archivo.usl    # analiza y genera reportes (*_errors.txt, *_ast.txt)
make check-ejemplos                   # corre examples/ y tests/ (los *error* deben fallar)
make clean
```

Los reportes se generan junto al directorio de ejecución. Si Graphviz está instalado,
también se puede visualizar el AST.
