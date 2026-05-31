#pragma once
#include <vector>
#include "GameObject.hpp"

class GameObjectManager {
public:
    // Ciclo de vida principal
    void update(double dt);
    void render(double alpha);

    // Gestion de entidades
    void addEntity(GameObject* pEntity);
    void removeEntity(GameObject* pEntity);
    void clearObjects();

    // Consultas
    GameObject* findEntityById(int id);

private:
    std::vector<GameObject*> m_gameObjects;
};