cmake_minimum_required(VERSION 3.10)
project(BGEngine
    VERSION 1.0.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Evitar compilaciones dentro de la carpeta fuente (in-source builds) [11]
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds no están permitidos. Crea una carpeta 'build'.")
endif()

# Definir el ejecutable principal [12, 13]
add_executable(BGEngine src/main.cpp)

# Configurar directorios de inclusión [14]
target_include_directories(BGEngine PRIVATE include)