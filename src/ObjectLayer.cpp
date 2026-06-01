#include "ObjectLayer.hpp"

void ObjectLayer::update() {
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update(0); // Aquí se suele pasar 'dt' si se usa tiempo variable [5]
    }
}

void ObjectLayer::render(SDL_Renderer* pRenderer) {
    for(int i = 0; i < m_gameObjects.size(); i++) {
        // Pasamos el renderer a cada objeto para su dibujo
        m_gameObjects[i]->draw(pRenderer); 
    }
}