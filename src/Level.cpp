#include "Level.hpp"

Level::Level() {}

void Level::update() {
    for(auto& layer : m_layers) {
        layer->update();
    }
}

void Level::render(SDL_Renderer* pRenderer) {
    for(auto& layer : m_layers) {
        layer->render(pRenderer);
    }
}