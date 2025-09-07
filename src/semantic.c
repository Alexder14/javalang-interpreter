

#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
static SemanticAnalyzer *global_analyzer = NULL;

// Crear analizador semántico
SemanticAnalyzer* create_semantic_analyzer() {
    SemanticAnalyzer *analyzer = malloc(sizeof(SemanticAnalyzer));
    if (!analyzer) {
        fprintf(stderr, "Error: No se pudo crear el analizador semántico\n");
        exit(1);
    }
    
    analyzer->symbol_table = NULL;
    analyzer->current_scope = strdup("Global");
    analyzer->scope_level = 0;
    analyzer->current_function = NULL;
    analyzer->errors = NULL;
    analyzer->error_count = 0;
    analyzer->in_loop = false;
    analyzer->in_function = false;
    
    global_analyzer = analyzer;
    return analyzer;
}

// Destruir analizador semántico
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
    
    // Liberar errores
    SemanticError *error = analyzer->errors;
    while (error) {
        SemanticError *next = error->next;
        free(error->message);
        free(error->context);
        free(error);
        error = next;
    }
    
    free(analyzer->current_scope);
    free(analyzer);
}

// Crear símbolo
Symbol* create_symbol(const char *id, SymbolType type, DataType data_type, 
                     const char *scope, int line, int col) {
    Symbol *symbol = malloc(sizeof(Symbol));
    if (!symbol) {
        fprintf(stderr, "Error: No se pudo crear símbolo\n");
        exit(1);
    }
    
    symbol->id = strdup(id);
    symbol->symbol_type = type;  // CORREGIDO: usar symbol_type
    symbol->data_type = data_type;
    symbol->scope = strdup(scope);
    symbol->line = line;
    symbol->column = col;
    symbol->is_initialized = false;
    symbol->is_array = false;
    symbol->array_size = 0;
    symbol->parameters = NULL;
    symbol->value = NULL;
    symbol->next = NULL;
    
    return symbol;
}

// Buscar símbolo en la tabla
Symbol* lookup_symbol(SemanticAnalyzer *analyzer, const char *id) {
    Symbol *current = analyzer->symbol_table;
    
    // Buscar en el ámbito actual primero
    while (current) {
        if (strcmp(current->id, id) == 0 && 
            strcmp(current->scope, analyzer->current_scope) == 0) {
            return current;
        }
        current = current->next;
    }
    
    // Buscar en ámbito global
    current = analyzer->symbol_table;
    while (current) {
        if (strcmp(current->id, id) == 0 && 
            strcmp(current->scope, "Global") == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

// Agregar símbolo a la tabla
bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol) {
    // Verificar que no exista en el ámbito actual
    Symbol *existing = lookup_symbol(analyzer, symbol->id);
    if (existing && strcmp(existing->scope, symbol->scope) == 0) {
        add_semantic_error(analyzer, "Variable ya declarada en este ámbito", 
                          symbol->id, symbol->line, symbol->column);
        return false;
    }
    
    // Agregar al inicio de la lista
    symbol->next = analyzer->symbol_table;
    analyzer->symbol_table = symbol;
    return true;
}

// Agregar error semántico
void add_semantic_error(SemanticAnalyzer *analyzer, const char *message, 
                       const char *context, int line, int col) {
    SemanticError *error = malloc(sizeof(SemanticError));
    if (!error) return;
    
    error->message = strdup(message);
    error->context = strdup(context ? context : "");
    error->line = line;
    error->column = col;
    error->next = analyzer->errors;
    
    analyzer->errors = error;
    analyzer->error_count++;
}

// Analizar declaración de función - CORREGIDO
bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_DECL) {
        return false;
    }
    
    // CORREGIDO: Usar el nombre correcto del campo en el AST
    char *return_type = node->data.func_decl.return_type;
    char *name = node->data.func_decl.name;
    ASTNode *parameters = node->data.func_decl.parameters;
    ASTNode *body = node->data.func_decl.body;
    
    // Convertir tipo de retorno
    DataType ret_type = string_to_data_type(return_type);
    
    // Crear símbolo de función
    Symbol *func_symbol = create_symbol(name, SYMBOL_FUNCTION, ret_type,
                                       analyzer->current_scope, node->line, node->column);
    func_symbol->parameters = parameters;
    
    if (!add_symbol(analyzer, func_symbol)) {
        return false;
    }
    
    bool result = true;
    
    // Entrar al ámbito de la función
    enter_scope(analyzer, name);
    analyzer->in_function = true;
    
    // Establecer función actual
    analyzer->current_function = func_symbol;
    
    // Analizar parámetros
    if (parameters) {
        result = analyze_semantic(analyzer, parameters);
    }
    
    // Analizar cuerpo
    if (body) {
        result = analyze_semantic(analyzer, body) && result;
    }
    
    // Salir del ámbito
    exit_scope(analyzer);
    analyzer->in_function = false;
    analyzer->current_function = NULL;
    
    return result;
}

// Analizar declaración de variable - CORREGIDO
bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_VAR_DECL) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo a los campos
    char *data_type_str = node->data.var_decl.data_type;
    char *name = node->data.var_decl.name;
    ASTNode *init_value = node->data.var_decl.init_value;
    bool is_array = node->data.var_decl.is_array;
    int array_size = node->data.var_decl.array_size;
    
    // Convertir tipo
    DataType data_type = string_to_data_type(data_type_str);
    
    // Crear símbolo de variable
    Symbol *var_symbol = create_symbol(name, SYMBOL_VARIABLE, data_type,
                                      analyzer->current_scope, node->line, node->column);
    var_symbol->is_array = is_array;
    var_symbol->array_size = array_size;
    var_symbol->is_initialized = (init_value != NULL);
    
    if (!add_symbol(analyzer, var_symbol)) {
        return false;
    }
    
    // Analizar inicializador si existe
    if (init_value) {
        DataType init_type;
        if (analyze_expression(analyzer, init_value, &init_type)) {
            if (!is_compatible_types(data_type, init_type)) {
                add_semantic_error(analyzer, "Tipo de inicializador incompatible",
                                  name, node->line, node->column);
                return false;
            }
        }
    }
    
    return true;
}

// Analizar asignación - CORREGIDO
bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_ASSIGNMENT) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo
    ASTNode *left = node->data.assignment.left;
    ASTNode *right = node->data.assignment.right;
    
    // Verificar que el lado izquierdo sea un identificador válido
    if (left->type == NODE_IDENTIFIER) {
        const char *var_name = left->data.identifier.name;
        Symbol *var_symbol = lookup_symbol(analyzer, var_name);
        
        if (!var_symbol) {
            add_semantic_error(analyzer, "Variable no declarada", var_name,
                              left->line, left->column);
            return false;
        }
        
        if (var_symbol->symbol_type != SYMBOL_VARIABLE) { // CORREGIDO: symbol_type
            add_semantic_error(analyzer, "No se puede asignar a este identificador",
                              var_name, left->line, left->column);
            return false;
        }
        
        // Marcar como inicializada
        var_symbol->is_initialized = true;
        
        // Analizar expresión del lado derecho
        DataType right_type;
        if (analyze_expression(analyzer, right, &right_type)) {
            if (!is_compatible_types(var_symbol->data_type, right_type)) {
                add_semantic_error(analyzer, "Tipos incompatibles en asignación",
                                  var_name, node->line, node->column);
                return false;
            }
        }
    }
    
    return true;
}

// Analizar expresión
bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type) {
    if (!node || !result_type) return false;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            *result_type = TYPE_INT;
            return true;
            
        case NODE_FLOAT_LITERAL:
            *result_type = TYPE_FLOAT;
            return true;
            
        case NODE_STRING_LITERAL:
            *result_type = TYPE_STRING;
            return true;
            
        case NODE_CHAR_LITERAL:
            *result_type = TYPE_CHAR;
            return true;
            
        case NODE_BOOLEAN_LITERAL:
            *result_type = TYPE_BOOLEAN;
            return true;
            
        case NODE_NULL_LITERAL:
            *result_type = TYPE_NULL;
            return true;
            
        case NODE_IDENTIFIER: {
            const char *name = node->data.identifier.name;
            Symbol *symbol = lookup_symbol(analyzer, name);
            
            if (!symbol) {
                add_semantic_error(analyzer, "Variable no declarada", name,
                                  node->line, node->column);
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            
            if (!symbol->is_initialized && symbol->symbol_type == SYMBOL_VARIABLE) { // CORREGIDO
                add_semantic_error(analyzer, "Variable usada antes de ser inicializada",
                                  name, node->line, node->column);
            }
            
            *result_type = symbol->data_type;
            return true;
        }
        
        case NODE_BINARY_OP: {
            DataType left_type, right_type;
            bool left_ok = analyze_expression(analyzer, node->data.binary_op.left, &left_type);
            bool right_ok = analyze_expression(analyzer, node->data.binary_op.right, &right_type);
            
            if (!left_ok || !right_ok) {
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            
            // CORREGIDO: orden correcto de parámetros
            *result_type = get_binary_operation_result_type(node->data.binary_op.operator,
                                                           left_type, right_type);
            
            if (*result_type == TYPE_UNKNOWN) {
                add_semantic_error(analyzer, "Operación no válida entre tipos",
                                  node->data.binary_op.operator, node->line, node->column);
                return false;
            }
            
            return true;
        }
        
        default:
            *result_type = TYPE_UNKNOWN;
            return false;
    }
}

// Analizar llamada a función - CORREGIDO
bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_CALL) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo
    char *name = node->data.func_call.name;
    ASTNode *arguments = node->data.func_call.arguments;
    
    // Buscar función en la tabla de símbolos
    Symbol *func_symbol = lookup_symbol(analyzer, name);
    
    if (!func_symbol) {
        add_semantic_error(analyzer, "Función no declarada", name,
                          node->line, node->column);
        return false;
    }
    
    if (func_symbol->symbol_type != SYMBOL_FUNCTION) { // CORREGIDO
        add_semantic_error(analyzer, "Identificador no es una función", name,
                          node->line, node->column);
        return false;
    }
    
    // TODO: Verificar argumentos
    
    return true;
}

// Verificar compatibilidad de tipos
bool is_compatible_types(DataType type1, DataType type2) {
    if (type1 == type2) return true;
    
    // Conversiones implícitas permitidas
    if (type1 == TYPE_FLOAT && type2 == TYPE_INT) return true;
    if (type1 == TYPE_DOUBLE && (type2 == TYPE_INT || type2 == TYPE_FLOAT)) return true;
    
    return false;
}

// Obtener tipo resultado de operación binaria - CORREGIDO
DataType get_binary_operation_result_type(const char *op, DataType left_type, DataType right_type) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
        strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
            if (left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) return TYPE_DOUBLE;
            if (left_type == TYPE_FLOAT || right_type == TYPE_FLOAT) return TYPE_FLOAT;
            return TYPE_INT;
        }
    }
    
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
        strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) {
        if (is_compatible_types(left_type, right_type)) {
            return TYPE_BOOLEAN;
        }
    }
    
    if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0) {
        if (left_type == TYPE_BOOLEAN && right_type == TYPE_BOOLEAN) {
            return TYPE_BOOLEAN;
        }
    }
    
    return TYPE_UNKNOWN;
}

// Entrar a nuevo ámbito
void enter_scope(SemanticAnalyzer *analyzer, const char *scope_name) {
    free(analyzer->current_scope);
    analyzer->current_scope = strdup(scope_name);
    analyzer->scope_level++;
}

// Salir del ámbito actual
void exit_scope(SemanticAnalyzer *analyzer) {
    analyzer->scope_level--;
    if (analyzer->scope_level <= 0) {
        free(analyzer->current_scope);
        analyzer->current_scope = strdup("Global");
    }
}

// Función principal de análisis semántico
bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node) return true;
    
    switch (node->type) {
        case NODE_FUNCTION_DECL:
            return analyze_function_declaration(analyzer, node);
            
        case NODE_VAR_DECL:
            return analyze_variable_declaration(analyzer, node);
            
        case NODE_ASSIGNMENT:
            return analyze_assignment(analyzer, node);
            
        case NODE_FUNCTION_CALL:
            return analyze_function_call(analyzer, node);
            
        // TODO: Agregar más casos según sea necesario
        
        default:
            return true;
    }
}

// Generar reporte de errores semánticos
void generate_semantic_errors_report(const char *filename) {
    if (global_analyzer) {
        printf("📄 Generando reporte de errores semánticos: %s\n", filename);
        // Aquí se puede implementar la generación del reporte a archivo
    }
}

// Funciones de utilidad adicionales
const char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case SYMBOL_VARIABLE: return "Variable";
        case SYMBOL_FUNCTION: return "Función";
        case SYMBOL_PARAMETER: return "Parámetro";
        case SYMBOL_CONSTANT: return "Constante";
        default: return "Desconocido";
    }
}