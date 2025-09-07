#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales para reportes
extern bool has_semantic_errors;

// ==========================================
// FUNCIONES DE CREACIÓN Y DESTRUCCIÓN
// ==========================================

SemanticAnalyzer* create_semantic_analyzer() {
    SemanticAnalyzer *analyzer = malloc(sizeof(SemanticAnalyzer));
    if (!analyzer) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el analizador semántico\n");
        exit(1);
    }
    
    analyzer->symbol_table = NULL;
    analyzer->current_scope = strdup("Global");
    analyzer->scope_level = 0;
    analyzer->has_main_function = false;
    analyzer->in_function = false;
    analyzer->current_function_return_type = TYPE_VOID;
    
    return analyzer;
}

void destroy_semantic_analyzer(SemanticAnalyzer *analyzer) {
    if (!analyzer) return;
    
    // Liberar tabla de símbolos
    Symbol *current = analyzer->symbol_table;
    while (current) {
        Symbol *next = current->next;
        free(current->id);
        free(current->scope);
        free(current);
        current = next;
    }
    
    free(analyzer->current_scope);
    free(analyzer);
}

// ==========================================
// FUNCIONES DE TABLA DE SÍMBOLOS
// ==========================================

Symbol* create_symbol(const char *id, SymbolType symbol_type, DataType data_type, 
                     const char *scope, int line, int column) {
    Symbol *symbol = malloc(sizeof(Symbol));
    if (!symbol) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el símbolo\n");
        exit(1);
    }
    
    symbol->id = strdup(id);
    symbol->symbol_type = symbol_type;
    symbol->data_type = data_type;
    symbol->scope = strdup(scope);
    symbol->line = line;
    symbol->column = column;
    symbol->is_array = false;
    symbol->array_size = 0;
    symbol->is_initialized = false;
    symbol->is_constant = false;
    symbol->parameters = NULL;
    symbol->return_type = TYPE_VOID;
    symbol->next = NULL;
    
    return symbol;
}

bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol) {
    if (!analyzer || !symbol) return false;
    
    // Verificar si ya existe en el mismo ámbito
    Symbol *existing = lookup_symbol_in_scope(analyzer, symbol->id, symbol->scope);
    if (existing) {
        add_error(ERROR_SEMANTIC, 
                 "Variable o función ya declarada en este ámbito", 
                 symbol->scope, symbol->line, symbol->column);
        return false;
    }
    
    // Agregar al inicio de la lista
    symbol->next = analyzer->symbol_table;
    analyzer->symbol_table = symbol;
    
    // Verificar si es la función main
    if (symbol->symbol_type == SYMBOL_FUNCTION && strcmp(symbol->id, "main") == 0) {
        analyzer->has_main_function = true;
    }
    
    return true;
}

Symbol* lookup_symbol(SemanticAnalyzer *analyzer, const char *id) {
    if (!analyzer || !id) return NULL;
    
    Symbol *current = analyzer->symbol_table;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Symbol* lookup_symbol_in_scope(SemanticAnalyzer *analyzer, const char *id, const char *scope) {
    if (!analyzer || !id || !scope) return NULL;
    
    Symbol *current = analyzer->symbol_table;
    while (current) {
        if (strcmp(current->id, id) == 0 && strcmp(current->scope, scope) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_symbol_table(SemanticAnalyzer *analyzer) {
    if (!analyzer) return;
    
    printf("\n=== TABLA DE SÍMBOLOS ===\n");
    printf("%-20s %-15s %-12s %-15s %-6s %-6s\n", 
           "ID", "Tipo Símbolo", "Tipo Dato", "Ámbito", "Línea", "Columna");
    printf("────────────────────────────────────────────────────────────────────────\n");
    
    Symbol *current = analyzer->symbol_table;
    while (current) {
        printf("%-20s %-15s %-12s %-15s %-6d %-6d\n",
               current->id,
               symbol_type_to_string(current->symbol_type),
               data_type_to_string(current->data_type),
               current->scope,
               current->line,
               current->column);
        current = current->next;
    }
    printf("\n");
}

// ==========================================
// ANÁLISIS SEMÁNTICO PRINCIPAL
// ==========================================

bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!analyzer || !node) return true;
    
    bool result = true;
    
    switch (node->type) {
        case NODE_PROGRAM:
            result = analyze_program(analyzer, node);
            break;
            
        case NODE_MAIN_CLASS:
            result = analyze_main_class(analyzer, node);
            break;
            
        case NODE_FUNCTION_DECL:
            result = analyze_function_declaration(analyzer, node);
            break;
            
        case NODE_VAR_DECL:
            result = analyze_variable_declaration(analyzer, node);
            break;
            
        case NODE_ASSIGNMENT:
            result = analyze_assignment(analyzer, node);
            break;
            
        case NODE_IF_STMT:
            result = analyze_if_statement(analyzer, node);
            break;
            
        case NODE_WHILE_STMT:
            result = analyze_while_statement(analyzer, node);
            break;
            
        case NODE_FOR_STMT:
            result = analyze_for_statement(analyzer, node);
            break;
            
        case NODE_RETURN_STMT:
            result = analyze_return_statement(analyzer, node);
            break;
            
        case NODE_LIST:
            result = analyze_statement_list(analyzer, node);
            break;
            
        default:
            // Para otros tipos de nodos, continuar el análisis
            if (node->children) {
                for (int i = 0; i < node->child_count; i++) {
                    if (!analyze_semantic(analyzer, node->children[i])) {
                        result = false;
                    }
                }
            }
            break;
    }
    
    return result;
}

bool analyze_program(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_PROGRAM) return false;
    
    bool result = true;
    
    // Analizar el cuerpo del programa
    if (node->data.program.body) {
        result = analyze_semantic(analyzer, node->data.program.body);
    }
    
    // Verificar que existe función main
    if (!analyzer->has_main_function) {
        add_error(ERROR_SEMANTIC, "No se encontró función main", "Global", 0, 0);
        result = false;
    }
    
    return result;
}

bool analyze_main_class(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_MAIN_CLASS) return false;
    
    // Crear símbolo para la función main
    Symbol *main_symbol = create_symbol("main", SYMBOL_FUNCTION, TYPE_VOID, 
                                       "Global", node->line, node->column);
    add_symbol(analyzer, main_symbol);
    
    // Entrar al ámbito de main
    enter_scope(analyzer, "Main");
    analyzer->in_function = true;
    analyzer->current_function_return_type = TYPE_VOID;
    
    bool result = true;
    
    // Analizar el cuerpo de main
    if (node->data.main_class.body) {
        result = analyze_semantic(analyzer, node->data.main_class.body);
    }
    
    // Salir del ámbito
    analyzer->in_function = false;
    exit_scope(analyzer);
    
    return result;
}

bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_DECL) return false;
    
    FunctionDecl *func = &node->data.function_decl;
    
    // Determinar tipo de retorno
    DataType return_type = string_to_data_type(func->return_type);
    
    // Crear símbolo para la función
    Symbol *func_symbol = create_symbol(func->name, SYMBOL_FUNCTION, return_type,
                                      analyzer->current_scope, node->line, node->column);
    func_symbol->parameters = func->parameters;
    func_symbol->return_type = return_type;
    
    if (!add_symbol(analyzer, func_symbol)) {
        return false;
    }
    
    // Entrar al ámbito de la función
    enter_scope(analyzer, func->name);
    analyzer->in_function = true;
    analyzer->current_function_return_type = return_type;
    
    bool result = true;
    
    // Analizar parámetros
    if (func->parameters) {
        result = analyze_semantic(analyzer, func->parameters);
    }
    
    // Analizar cuerpo de la función
    if (func->body) {
        result = analyze_semantic(analyzer, func->body) && result;
    }
    
    // Salir del ámbito
    analyzer->in_function = false;
    exit_scope(analyzer);
    
    return result;
}

bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_VAR_DECL) return false;
    
    VarDecl *var = &node->data.var_decl;
    
    // Determinar tipo de dato
    DataType data_type = string_to_data_type(var->type);
    
    // Crear símbolo para la variable
    Symbol *var_symbol = create_symbol(var->name, SYMBOL_VARIABLE, data_type,
                                     analyzer->current_scope, node->line, node->column);
    var_symbol->is_array = var->is_array;
    var_symbol->array_size = var->array_size;
    var_symbol->is_initialized = (var->initializer != NULL);
    
    if (!add_symbol(analyzer, var_symbol)) {
        return false;
    }
    
    // Analizar inicializador si existe
    if (var->initializer) {
        DataType init_type;
        if (analyze_expression(analyzer, var->initializer, &init_type)) {
            if (!is_compatible_types(data_type, init_type)) {
                add_error(ERROR_SEMANTIC, "Tipos incompatibles en inicialización",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
        }
    }
    
    return true;
}

bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_ASSIGNMENT) return false;
    
    Assignment *assign = &node->data.assignment;
    
    // Verificar que la variable esté declarada
    if (assign->left->type == NODE_IDENTIFIER) {
        const char *var_name = assign->left->data.identifier.name;
        Symbol *symbol = lookup_symbol(analyzer, var_name);
        
        if (!symbol) {
            add_error(ERROR_SEMANTIC, "Variable no declarada",
                     analyzer->current_scope, node->line, node->column);
            return false;
        }
        
        // Verificar que no sea constante
        if (symbol->is_constant) {
            add_error(ERROR_SEMANTIC, "No se puede asignar a una constante",
                     analyzer->current_scope, node->line, node->column);
            return false;
        }
        
        // Analizar expresión del lado derecho
        DataType right_type;
        if (analyze_expression(analyzer, assign->right, &right_type)) {
            if (!is_compatible_types(symbol->data_type, right_type)) {
                add_error(ERROR_SEMANTIC, "Tipos incompatibles en asignación",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
        }
        
        // Marcar como inicializada
        symbol->is_initialized = true;
    }
    
    return true;
}

bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type) {
    if (!node || !result_type) return false;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            *result_type = TYPE_INT;
            return true;
            
        case NODE_FLOAT_LITERAL:
            *result_type = TYPE_FLOAT;
            return true;
            
        case NODE_BOOLEAN_LITERAL:
            *result_type = TYPE_BOOLEAN;
            return true;
            
        case NODE_STRING_LITERAL:
            *result_type = TYPE_STRING;
            return true;
            
        case NODE_CHAR_LITERAL:
            *result_type = TYPE_CHAR;
            return true;
            
        case NODE_IDENTIFIER: {
            const char *var_name = node->data.identifier.name;
            Symbol *symbol = lookup_symbol(analyzer, var_name);
            
            if (!symbol) {
                add_error(ERROR_SEMANTIC, "Variable no declarada",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
            
            *result_type = symbol->data_type;
            return true;
        }
        
        case NODE_BINARY_OP: {
            DataType left_type, right_type;
            
            if (!analyze_expression(analyzer, node->data.binary_op.left, &left_type) ||
                !analyze_expression(analyzer, node->data.binary_op.right, &right_type)) {
                return false;
            }
            
            *result_type = get_binary_operation_result_type(node->data.binary_op.operator,
                                                          left_type, right_type);
            
            if (*result_type == TYPE_UNKNOWN) {
                add_error(ERROR_SEMANTIC, "Operación inválida entre tipos",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
            
            return true;
        }
        
        case NODE_UNARY_OP: {
            DataType operand_type;
            
            if (!analyze_expression(analyzer, node->data.unary_op.operand, &operand_type)) {
                return false;
            }
            
            *result_type = get_unary_operation_result_type(node->data.unary_op.operator,
                                                         operand_type);
            
            if (*result_type == TYPE_UNKNOWN) {
                add_error(ERROR_SEMANTIC, "Operación unaria inválida",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
            
            return true;
        }
        
        case NODE_FUNCTION_CALL:
            return analyze_function_call(analyzer, node, result_type);
            
        default:
            *result_type = TYPE_UNKNOWN;
            return false;
    }
}

bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type) {
    if (!node || node->type != NODE_FUNCTION_CALL) return false;
    
    FunctionCall *call = &node->data.function_call;
    
    // Buscar la función en la tabla de símbolos
    Symbol *func_symbol = lookup_symbol(analyzer, call->name);
    
    if (!func_symbol || func_symbol->symbol_type != SYMBOL_FUNCTION) {
        add_error(ERROR_SEMANTIC, "Función no declarada",
                 analyzer->current_scope, node->line, node->column);
        return false;
    }
    
    *result_type = func_symbol->return_type;
    
    // TODO: Verificar argumentos vs parámetros
    
    return true;
}

bool analyze_statement_list(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_LIST) return true;
    
    bool result = true;
    
    for (int i = 0; i < node->child_count; i++) {
        if (!analyze_semantic(analyzer, node->children[i])) {
            result = false;
        }
    }
    
    return result;
}

bool analyze_if_statement(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_IF_STMT) return false;
    
    IfStmt *if_stmt = &node->data.if_stmt;
    
    // Analizar condición
    DataType condition_type;
    if (!analyze_expression(analyzer, if_stmt->condition, &condition_type)) {
        return false;
    }
    
    if (!is_boolean_type(condition_type)) {
        add_error(ERROR_SEMANTIC, "La condición del if debe ser booleana",
                 analyzer->current_scope, node->line, node->column);
        return false;
    }
    
    bool result = true;
    
    // Analizar cuerpo then
    if (if_stmt->then_stmt) {
        result = analyze_semantic(analyzer, if_stmt->then_stmt) && result;
    }
    
    // Analizar cuerpo else
    if (if_stmt->else_stmt) {
        result = analyze_semantic(analyzer, if_stmt->else_stmt) && result;
    }
    
    return result;
}

bool analyze_while_statement(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_WHILE_STMT) return false;
    
    WhileStmt *while_stmt = &node->data.while_stmt;
    
    // Analizar condición
    DataType condition_type;
    if (!analyze_expression(analyzer, while_stmt->condition, &condition_type)) {
        return false;
    }
    
    if (!is_boolean_type(condition_type)) {
        add_error(ERROR_SEMANTIC, "La condición del while debe ser booleana",
                 analyzer->current_scope, node->line, node->column);
        return false;
    }
    
    // Analizar cuerpo
    return analyze_semantic(analyzer, while_stmt->body);
}

bool analyze_for_statement(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FOR_STMT) return false;
    
    ForStmt *for_stmt = &node->data.for_stmt;
    bool result = true;
    
    // Analizar inicialización
    if (for_stmt->init) {
        result = analyze_semantic(analyzer, for_stmt->init) && result;
    }
    
    // Analizar condición
    if (for_stmt->condition) {
        DataType condition_type;
        if (analyze_expression(analyzer, for_stmt->condition, &condition_type)) {
            if (!is_boolean_type(condition_type)) {
                add_error(ERROR_SEMANTIC, "La condición del for debe ser booleana",
                         analyzer->current_scope, node->line, node->column);
                result = false;
            }
        } else {
            result = false;
        }
    }
    
    // Analizar actualización
    if (for_stmt->update) {
        result = analyze_semantic(analyzer, for_stmt->update) && result;
    }
    
    // Analizar cuerpo
    if (for_stmt->body) {
        result = analyze_semantic(analyzer, for_stmt->body) && result;
    }
    
    return result;
}

bool analyze_return_statement(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_RETURN_STMT) return false;
    
    if (!analyzer->in_function) {
        add_error(ERROR_SEMANTIC, "Return fuera de función",
                 analyzer->current_scope, node->line, node->column);
        return false;
    }
    
    ReturnStmt *ret_stmt = &node->data.return_stmt;
    
    if (ret_stmt->value) {
        DataType return_type;
        if (analyze_expression(analyzer, ret_stmt->value, &return_type)) {
            if (!is_compatible_types(analyzer->current_function_return_type, return_type)) {
                add_error(ERROR_SEMANTIC, "Tipo de retorno incompatible",
                         analyzer->current_scope, node->line, node->column);
                return false;
            }
        }
    } else {
        if (analyzer->current_function_return_type != TYPE_VOID) {
            add_error(ERROR_SEMANTIC, "Función debe retornar un valor",
                     analyzer->current_scope, node->line, node->column);
            return false;
        }
    }
    
    return true;
}

// ==========================================
// FUNCIONES DE VALIDACIÓN DE TIPOS
// ==========================================

bool is_compatible_types(DataType type1, DataType type2) {
    if (type1 == type2) return true;
    
    // Conversiones implícitas permitidas
    if (type1 == TYPE_FLOAT && type2 == TYPE_INT) return true;
    if (type1 == TYPE_DOUBLE && (type2 == TYPE_INT || type2 == TYPE_FLOAT)) return true;
    
    return false;
}

DataType get_binary_operation_result_type(const char *operator, DataType left_type, DataType right_type) {
    // Operadores aritméticos
    if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0 ||
        strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0 ||
        strcmp(operator, "%") == 0) {
        
        if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
            if (left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) return TYPE_DOUBLE;
            if (left_type == TYPE_FLOAT || right_type == TYPE_FLOAT) return TYPE_FLOAT;
            return TYPE_INT;
        }
        return TYPE_UNKNOWN;
    }
    
    // Operadores de comparación
    if (strcmp(operator, "<") == 0 || strcmp(operator, "<=") == 0 ||
        strcmp(operator, ">") == 0 || strcmp(operator, ">=") == 0) {
        
        if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
            return TYPE_BOOLEAN;
        }
        return TYPE_UNKNOWN;
    }
    
    // Operadores de igualdad
    if (strcmp(operator, "==") == 0 || strcmp(operator, "!=") == 0) {
        if (is_compatible_types(left_type, right_type)) {
            return TYPE_BOOLEAN;
        }
        return TYPE_UNKNOWN;
    }
    
    // Operadores lógicos
    if (strcmp(operator, "&&") == 0 || strcmp(operator, "||") == 0) {
        if (is_boolean_type(left_type) && is_boolean_type(right_type)) {
            return TYPE_BOOLEAN;
        }
        return TYPE_UNKNOWN;
    }
    
    return TYPE_UNKNOWN;
}

DataType get_unary_operation_result_type(const char *operator, DataType operand_type) {
    if (strcmp(operator, "!") == 0) {
        return is_boolean_type(operand_type) ? TYPE_BOOLEAN : TYPE_UNKNOWN;
    }
    
    if (strcmp(operator, "-") == 0 || strcmp(operator, "+") == 0) {
        return is_numeric_type(operand_type) ? operand_type : TYPE_UNKNOWN;
    }
    
    if (strcmp(operator, "++") == 0 || strcmp(operator, "--") == 0) {
        return is_numeric_type(operand_type) ? operand_type : TYPE_UNKNOWN;
    }
    
    return TYPE_UNKNOWN;
}

bool is_valid_assignment(DataType target_type, DataType source_type) {
    return is_compatible_types(target_type, source_type);
}

bool is_numeric_type(DataType type) {
    return type == TYPE_INT || type == TYPE_FLOAT || type == TYPE_DOUBLE;
}

bool is_boolean_type(DataType type) {
    return type == TYPE_BOOLEAN;
}

// ==========================================
// GESTIÓN DE ÁMBITOS
// ==========================================

void enter_scope(SemanticAnalyzer *analyzer, const char *scope_name) {
    if (!analyzer || !scope_name) return;
    
    free(analyzer->current_scope);
    analyzer->current_scope = strdup(scope_name);
    analyzer->scope_level++;
}

void exit_scope(SemanticAnalyzer *analyzer) {
    if (!analyzer) return;
    
    analyzer->scope_level--;
    if (analyzer->scope_level == 0) {
        free(analyzer->current_scope);
        analyzer->current_scope = strdup("Global");
    }
}

char* get_current_scope(SemanticAnalyzer *analyzer) {
    return analyzer ? analyzer->current_scope : NULL;
}

// ==========================================
// FUNCIONES DE REPORTES
// ==========================================

void generate_symbol_table_report(SemanticAnalyzer *analyzer, const char *filename) {
    if (!analyzer || !filename) return;
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear archivo de reporte de tabla de símbolos\n");
        return;
    }
    
    fprintf(file, "=== TABLA DE SÍMBOLOS ===\n");
    fprintf(file, "%-20s %-15s %-12s %-15s %-6s %-6s\n", 
            "ID", "Tipo Símbolo", "Tipo Dato", "Ámbito", "Línea", "Columna");
    fprintf(file, "────────────────────────────────────────────────────────────────────────\n");
    
    Symbol *current = analyzer->symbol_table;
    while (current) {
        fprintf(file, "%-20s %-15s %-12s %-15s %-6d %-6d\n",
                current->id,
                symbol_type_to_string(current->symbol_type),
                data_type_to_string(current->data_type),
                current->scope,
                current->line,
                current->column);
        current = current->next;
    }
    
    fclose(file);
    printf("Reporte de tabla de símbolos generado: %s\n", filename);
}

void generate_semantic_errors_report(const char *filename) {
    generate_error_report(filename);
}

// ==========================================
// FUNCIONES AUXILIARES
// ==========================================

const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_CHAR: return "char";
        case TYPE_STRING: return "String";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}

const char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case SYMBOL_VARIABLE: return "Variable";
        case SYMBOL_FUNCTION: return "Función";
        case SYMBOL_PARAMETER: return "Parámetro";
        case SYMBOL_CONSTANT: return "Constante";
        default: return "Unknown";
    }
}