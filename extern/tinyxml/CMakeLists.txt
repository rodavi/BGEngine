add_library(tinyxml STATIC
    tinyxml2.cpp
    tinyxml2.h
)

# Definir el uso de STL como requisito de la interfaz [1]
#target_compile_definitions(tinyxml PUBLIC TIXML_USE_STL)

# Exponer los encabezados para que otros targets los encuentren
target_include_directories(tinyxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})