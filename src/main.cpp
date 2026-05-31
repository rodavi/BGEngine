#include <iostream>
#include "Engine.hpp"

int main(int argc, char* argv[]) {
    std::cout << "BGEngine: Iniciando cimientos..." << std::endl;

    Engine engine;
    if (!engine.init()) {
        std::cerr << "Error al inicializar el motor" << std::endl;
        return 1;
    }
    engine.run();

    return 0;
}