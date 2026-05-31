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

# Agregar FetchContent para SDL3
include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# 1. Definir la librería del motor (con tus archivos de lógica)
add_library(BGEngineLib STATIC src/Engine.cpp) 
target_include_directories(BGEngineLib PUBLIC include)
target_link_libraries(BGEngineLib PUBLIC SDL3::SDL3)

# 2. El ejecutable principal ahora es solo un "wrapper"
add_executable(BGEngine src/main.cpp)
target_link_libraries(BGEngine PRIVATE BGEngineLib)

# CTest para agregar pruebas
enable_testing()
add_executable(test_init tests/test_init.cpp)
target_link_libraries(test_init PRIVATE BGEngineLib)

add_test(NAME EngineInitTest COMMAND test_init)