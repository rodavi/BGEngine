#pragma once
#include <string>
#include <map>
#include <iostream>
#include "GameObject.hpp"

// Interfaz base para los creadores de objetos [3]
class BaseCreator {
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory {
public:
    static GameObjectFactory* Instance(); // Acceso Singleton [1]
    
    bool registerType(std::string typeID, BaseCreator* pCreator); // Registro dinámico [5]
    GameObject* create(std::string typeID); // Instanciación por ID [6]

private:
    GameObjectFactory() {} // Constructor privado [1]
    static GameObjectFactory* s_pInstance;
    
    std::map<std::string, BaseCreator*> m_creators; // Mapa de tipos y creadores [4]
};

typedef GameObjectFactory TheGameObjectFactory;
