#!/bin/bash

# Script de configuración completo para JavaLang Compiler
# Configura el entorno, instala dependencias y compila el proyecto

echo "╔════════════════════════════════════════════════════════════════════════╗"
echo "║                      CONFIGURADOR JAVALANG                            ║"
echo "║                   Compilador Educativo v1.0                           ║"
echo "╚════════════════════════════════════════════════════════════════════════╝"

# Variables de control
INSTALL_DEPS=true
RUN_TESTS=true
CREATE_EXAMPLES=true
INSTALL_GRAPHVIZ=true

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Función para mostrar mensajes con color
print_step() {
    echo -e "${BLUE}🔧 $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_info() {
    echo -e "${CYAN}ℹ️  $1${NC}"
}

# Función para detectar el sistema operativo
detect_os() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        OS=$ID
        VERSION=$VERSION_ID
    elif type lsb_release >/dev/null 2>&1; then
        OS=$(lsb_release -si | tr '[:upper:]' '[:lower:]')
        VERSION=$(lsb_release -sr)
    elif [ -f /etc/redhat-release ]; then
        OS="centos"
    else
        OS=$(uname -s | tr '[:upper:]' '[:lower:]')
    fi
}

# Función para instalar dependencias según el OS
install_dependencies() {
    print_step "Detectando sistema operativo..."
    detect_os
    print_info "Sistema detectado: $OS"
    
    case $OS in
        ubuntu|debian)
            print_step "Actualizando repositorios..."
            sudo apt update
            
            print_step "Instalando dependencias básicas..."
            sudo apt install -y build-essential gcc make
            
            print_step "Instalando Flex y Bison..."
            sudo apt install -y flex bison libfl-dev
            
            if [ "$INSTALL_GRAPHVIZ" = true ]; then
                print_step "Instalando Graphviz para visualización..."
                sudo apt install -y graphviz
            fi
            
            print_step "Instalando herramientas adicionales..."
            sudo apt install -y git vim tree htop
            ;;
            
        centos|rhel|fedora)
            if command -v dnf &> /dev/null; then
                PKG_MANAGER="dnf"
            else
                PKG_MANAGER="yum"
            fi
            
            print_step "Instalando dependencias básicas..."
            sudo $PKG_MANAGER groupinstall -y "Development Tools"
            sudo $PKG_MANAGER install -y gcc make
            
            print_step "Instalando Flex y Bison..."
            sudo $PKG_MANAGER install -y flex bison flex-devel
            
            if [ "$INSTALL_GRAPHVIZ" = true ]; then
                print_step "Instalando Graphviz para visualización..."
                sudo $PKG_MANAGER install -y graphviz
            fi
            
            print_step "Instalando herramientas adicionales..."
            sudo $PKG_MANAGER install -y git vim tree htop
            ;;
            
        arch|manjaro)
            print_step "Instalando dependencias básicas..."
            sudo pacman -S --noconfirm base-devel gcc make
            
            print_step "Instalando Flex y Bison..."
            sudo pacman -S --noconfirm flex bison
            
            if [ "$INSTALL_GRAPHVIZ" = true ]; then
                print_step "Instalando Graphviz para visualización..."
                sudo pacman -S --noconfirm graphviz
            fi
            
            print_step "Instalando herramientas adicionales..."
            sudo pacman -S --noconfirm git vim tree htop
            ;;
            
        *)
            print_warning "Sistema operativo no reconocido: $OS"
            print_info "Por favor instale manualmente:"
            print_info "- GCC y herramientas de desarrollo"
            print_info "- Flex (>= 2.6)"
            print_info "- Bison (>= 3.0)"
            print_info "- Make"
            if [ "$INSTALL_GRAPHVIZ" = true ]; then
                print_info "- Graphviz (opcional, para visualización)"
            fi
            ;;
    esac
}

# Función para verificar dependencias
check_dependencies() {
    print_step "Verificando dependencias instaladas..."
    
    DEPS_OK=true
    
    if ! command -v gcc &> /dev/null; then
        print_error "GCC no encontrado"
        DEPS_OK=false
    else
        print_success "GCC encontrado: $(gcc --version | head -n1)"
    fi
    
    if ! command -v make &> /dev/null; then
        print_error "Make no encontrado"
        DEPS_OK=false
    else
        print_success "Make encontrado: $(make --version | head -n1)"
    fi
    
    if ! command -v flex &> /dev/null; then
        print_error "Flex no encontrado"
        DEPS_OK=false
    else
        print_success "Flex encontrado: $(flex --version)"
    fi
    
    if ! command -v bison &> /dev/null; then
        print_error "Bison no encontrado"
        DEPS_OK=false
    else
        print_success "Bison encontrado: $(bison --version | head -n1)"
    fi
    
    if command -v dot &> /dev/null; then
        print_success "Graphviz encontrado: $(dot -V 2>&1)"
    else
        print_warning "Graphviz no encontrado (opcional para visualización)"
    fi
    
    if [ "$DEPS_OK" = false ]; then
        print_error "Faltan dependencias críticas"
        return 1
    fi
    
    print_success "Todas las dependencias críticas están instaladas"
    return 0
}

# Función para crear estructura de directorios
create_directory_structure() {
    print_step "Verificando estructura de directorios..."
    
    # Crear directorios si no existen
    mkdir -p include src parser lexer examples docs tests reports
    
    # Crear directorios para reportes si no existen
    mkdir -p reports/html reports/json reports/graphviz
    
    print_success "Estructura de directorios verificada"
}

# Función para crear archivos de ejemplo
create_example_files() {
    if [ "$CREATE_EXAMPLES" = false ]; then
        return
    fi
    
    print_step "Creando archivos de ejemplo..."
    
    # Crear ejemplo básico si no existe
    if [ ! -f "examples/test1.usl" ]; then
        cat > examples/test1.usl << 'EOF'
public class Test {
    public static void main() {
        int x = 5;
        System.out.println("Hola JavaLang!");
        System.out.println("El valor de x es: " + x);
    }
}
EOF
        print_success "Creado examples/test1.usl"
    fi
    
    # Crear ejemplo con errores si no existe
    if [ ! -f "examples/test_simple_errors.usl" ]; then
        cat > examples/test_simple_errors.usl << 'EOF'
public class TestErrores {
    public static void main() {
        int x = 5;
        y = 10;  // Error: variable no declarada
        x = "texto";  // Error: tipo incompatible
        if (x) {  // Error: condición no booleana
            System.out.println("Nunca debería ejecutarse");
        }
    }
}
EOF
        print_success "Creado examples/test_simple_errors.usl"
    fi
    
    print_success "Archivos de ejemplo creados"
}

# Función para compilar el proyecto
compile_project() {
    print_step "Compilando proyecto JavaLang..."
    
    # Limpiar compilación anterior
    make clean > /dev/null 2>&1
    
    # Compilar todo el proyecto
    if make all; then
        print_success "Proyecto compilado exitosamente"
        
        # Mostrar ejecutables creados
        echo ""
        print_info "Ejecutables disponibles:"
        if [ -f "javalang_interpreter" ]; then
            echo "  ✅ javalang_interpreter - Interpretador completo"
        fi
        if [ -f "test_semantic" ]; then
            echo "  ✅ test_semantic - Test de análisis semántico"
        fi
        if [ -f "test_parser" ]; then
            echo "  ✅ test_parser - Test de análisis sintáctico"
        fi
        if [ -f "test_lexer" ]; then
            echo "  ✅ test_lexer - Test de análisis léxico"
        fi
        
        return 0
    else
        print_error "Error en la compilación"
        return 1
    fi
}

# Función para ejecutar pruebas
run_tests() {
    if [ "$RUN_TESTS" = false ]; then
        return
    fi
    
    print_step "Ejecutando suite de pruebas..."
    
    if [ -f "run_tests.sh" ]; then
        chmod +x run_tests.sh
        if ./run_tests.sh; then
            print_success "Todas las pruebas pasaron"
        else
            print_warning "Algunas pruebas fallaron - revisar detalles arriba"
        fi
    else
        print_warning "Script de pruebas no encontrado"
        
        # Ejecutar pruebas básicas manualmente
        if [ -f "test_lexer" ] && [ -f "examples/test1.usl" ]; then
            print_step "Probando analizador léxico..."
            if ./test_lexer examples/test1.usl > /dev/null 2>&1; then
                print_success "Test léxico: OK"
            else
                print_error "Test léxico: FALLÓ"
            fi
        fi
        
        if [ -f "test_parser" ] && [ -f "examples/test1.usl" ]; then
            print_step "Probando analizador sintáctico..."
            if ./test_parser examples/test1.usl > /dev/null 2>&1; then
                print_success "Test sintáctico: OK"
            else
                print_error "Test sintáctico: FALLÓ"
            fi
        fi
        
        if [ -f "test_semantic" ] && [ -f "examples/test1.usl" ]; then
            print_step "Probando analizador semántico..."
            if ./test_semantic examples/test1.usl > /dev/null 2>&1; then
                print_success "Test semántico: OK"
            else
                print_error "Test semántico: FALLÓ"
            fi
        fi
    fi
}

# Función para crear archivos de configuración
create_config_files() {
    print_step "Creando archivos de configuración..."
    
    # Crear .gitignore si no existe
    if [ ! -f ".gitignore" ]; then
        cat > .gitignore << 'EOF'
# Archivos compilados
*.o
*.so
*.a

# Ejecutables
javalang_interpreter
test_lexer
test_parser
test_semantic

# Archivos generados por Flex/Bison
lexer/lex.yy.c
parser/parser.tab.c
parser/parser.tab.h

# Reportes generados
*_report.txt
*_report.html
*_report.json
*.dot
*.png

# Logs
*.log
test_results.log

# Directorios de build
build/
dist/

# Archivos de respaldo
*~
*.bak
*.tmp

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db
EOF
        print_success "Creado .gitignore"
    fi
    
    # Crear README básico si no existe
    if [ ! -f "README.md" ]; then
        cat > README.md << 'EOF'
# JavaLang Compiler

Compilador educativo para el lenguaje JavaLang desarrollado para el curso de Organización de Lenguajes y Compiladores 2.

## Características Implementadas

- ✅ **Fase 1**: Configuración del entorno
- ✅ **Fase 2**: Analizador léxico (Flex)
- ✅ **Fase 3**: Analizador sintáctico y AST (Bison)
- ✅ **Fase 4**: Análisis semántico y tabla de símbolos

## Uso Rápido

```bash
# Compilar todo
make all

# Analizar un archivo
./javalang_interpreter examples/test1.usl

# Generar reportes completos
./javalang_interpreter examples/test1.usl -reports -visualize
```

## Documentación

Ver `MANUAL_USUARIO.md` para documentación completa.
EOF
        print_success "Creado README.md básico"
    fi
}

# Función para mostrar información final
show_final_info() {
    echo ""
    echo -e "${PURPLE}╔════════════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${PURPLE}║                        CONFIGURACIÓN COMPLETA                         ║${NC}"
    echo -e "${PURPLE}╚════════════════════════════════════════════════════════════════════════╝${NC}"
    
    print_success "JavaLang Compiler configurado exitosamente"
    
    echo ""
    print_info "🚀 Para empezar a usar:"
    echo "   ./javalang_interpreter examples/test1.usl"
    echo "   ./javalang_interpreter examples/test_comprehensive.usl -v"
    echo "   ./javalang_interpreter examples/test_semantic.usl -reports"
    
    echo ""
    print_info "🧪 Para ejecutar pruebas:"
    echo "   make test-all"
    echo "   ./run_tests.sh"
    
    echo ""
    print_info "📚 Documentación disponible:"
    echo "   MANUAL_USUARIO.md - Manual completo"
    echo "   README_FASE4.md - Documentación de la Fase 4"
    
    echo ""
    print_info "📊 Para generar reportes:"
    echo "   ./javalang_interpreter archivo.usl -reports"
    echo "   ./javalang_interpreter archivo.usl -visualize"
    
    if command -v dot &> /dev/null; then
        echo ""
        print_info "🎨 Graphviz instalado - Visualizaciones gráficas disponibles"
    else
        echo ""
        print_warning "Instale Graphviz para visualizaciones gráficas:"
        echo "   sudo apt install graphviz  # Ubuntu/Debian"
        echo "   sudo yum install graphviz  # CentOS/RHEL"
    fi
    
    echo ""
    print_success "¡Disfrute programando en JavaLang! 🎉"
}

# Función principal
main() {
    echo ""
    print_step "Iniciando configuración de JavaLang Compiler..."
    
    # Procesar argumentos de línea de comandos
    while [[ $# -gt 0 ]]; do
        case $1 in
            --no-deps)
                INSTALL_DEPS=false
                shift
                ;;
            --no-tests)
                RUN_TESTS=false
                shift
                ;;
            --no-examples)
                CREATE_EXAMPLES=false
                shift
                ;;
            --no-graphviz)
                INSTALL_GRAPHVIZ=false
                shift
                ;;
            -h|--help)
                echo "Uso: $0 [opciones]"
                echo ""
                echo "Opciones:"
                echo "  --no-deps       No instalar dependencias"
                echo "  --no-tests      No ejecutar pruebas"
                echo "  --no-examples   No crear archivos de ejemplo"
                echo "  --no-graphviz   No instalar Graphviz"
                echo "  -h, --help      Mostrar esta ayuda"
                exit 0
                ;;
            *)
                print_warning "Opción desconocida: $1"
                shift
                ;;
        esac
    done
    
    # Ejecutar pasos de configuración
    if [ "$INSTALL_DEPS" = true ]; then
        install_dependencies
        echo ""
    fi
    
    check_dependencies
    if [ $? -ne 0 ]; then
        print_error "Configuración abortada debido a dependencias faltantes"
        exit 1
    fi
    
    echo ""
    create_directory_structure
    
    echo ""
    create_example_files
    
    echo ""
    create_config_files
    
    echo ""
    compile_project
    if [ $? -ne 0 ]; then
        print_error "Configuración abortada debido a errores de compilación"
        exit 1
    fi
    
    echo ""
    run_tests
    
    echo ""
    show_final_info
}

# Verificar si se está ejecutando como root (no recomendado excepto para instalación de dependencias)
if [ "$EUID" -eq 0 ] && [ "$INSTALL_DEPS" = false ]; then
    print_warning "No se recomienda ejecutar como root"
    print_info "Use sudo solo cuando sea necesario para instalar dependencias"
fi

# Ejecutar función principal
main "$@"