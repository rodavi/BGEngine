#include "GameObjectManager.hpp"
#include <algorithm>

void GameObjectManager::update(double dt) {
    // Fase 1: Actualizar solo los objetos vivos
    for (GameObject* pEntity : m_gameObjects) {
        if (!pEntity->isDead()) {
            pEntity->update(dt);
        }
    }

    // Fase 2: Limpieza de cadáveres (Deferred Removal)
    auto it = m_gameObjects.begin();
    while (it != m_gameObjects.end()) {
        if ((*it)->isDead()) {
            delete *it;            // Liberar la memoria del objeto [5]
            it = m_gameObjects.erase(it); // Eliminar el puntero del vector de forma segura [1]
        } else {
            ++it;
        }
    }
}

void GameObjectManager::render(double alpha) {
    for (auto& obj : m_gameObjects) {
        obj->render(alpha);
    }
}

void GameObjectManager::addEntity(GameObject* pEntity) {
    m_gameObjects.push_back(pEntity);
}

void GameObjectManager::removeEntity(GameObject* pEntity) {
    m_gameObjects.erase(
        std::remove(m_gameObjects.begin(), m_gameObjects.end(), pEntity), 
        m_gameObjects.end());
}

void GameObjectManager::clearObjects() {
    m_gameObjects.clear();
}

GameObject* GameObjectManager::findEntityById(int id) {
    for (auto& obj : m_gameObjects) {
        if (obj->getId() == id) {
            return obj;
        }
    }
    return nullptr;
}