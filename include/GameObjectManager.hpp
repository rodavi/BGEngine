#pragma once
#include <vector>
#include "GameObject.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class GameObjectManager {
public:
    // Ciclo de vida principal
    void update(double dt);
    void render(double alpha);
    void draw(SDL_Renderer* pRenderer);

    // Gestion de entidades
    void addEntity(GameObject* pEntity);
    void removeEntity(GameObject* pEntity);
    void clearObjects();

    // Consultas
    GameObject* findEntityById(std::string id);

private:
    std::vector<GameObject*> m_gameObjects;
};