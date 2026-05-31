#include "Engine.hpp"
#include <cassert>

int main() {
    Engine engine;
    assert(engine.init("BGEngine Test", 800, 600) && "Failed to initialize the engine");
    std::cout << "Engine initialized successfully!" << std::endl;
    return 0;
}