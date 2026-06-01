#pragma once
#include "GameObject.hpp"
#include "Layer.hpp"
#include <vector>

class ObjectLayer : public Layer {
public:
    void update() override; // Actualiza todos los objetos de la capa [2]
    void render(SDL_Renderer* pRenderer) override; // Dibuja todos los objetos de la capa [2]

    // Permite al LevelParser añadir objetos a esta capa [1]
    std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
    std::vector<GameObject*> m_gameObjects; // Contenedor de objetos dinámicos [1]
};
