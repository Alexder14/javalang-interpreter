#ifndef AST_DOT_H
#define AST_DOT_H

#include <stdio.h>
#include "ast.h"

/* Escribe el AST en formato Graphviz (DOT) para dibujarlo como grafo:
 *   dot -Tpng programa_ast.dot -o programa_ast.png
 */
void ast_write_dot(ASTNode *root, FILE *f);

#endif
