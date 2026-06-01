#include "GameObjectFactory.hpp"

// Inicialización de la instancia estática [8]
GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

GameObjectFactory* GameObjectFactory::Instance() {
    if (s_pInstance == nullptr) {
        s_pInstance = new GameObjectFactory();
    }
    return s_pInstance;
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator) {
    auto it = m_creators.find(typeID);
    
    // Si el tipo ya existe, eliminamos el creador para evitar fugas [7]
    if (it != m_creators.end()) {
        delete pCreator;
        return false;
    }
    
    m_creators[typeID] = pCreator;
    return true;
}

GameObject* GameObjectFactory::create(std::string typeID) {
    auto it = m_creators.find(typeID);
    
    if (it == m_creators.end()) {
        std::cout << "No se pudo encontrar el tipo: " << typeID << std::endl; //[6]
        return nullptr;
    }
    
    BaseCreator* pCreator = it->second;
    return pCreator->createGameObject(); // Retorna la nueva instancia [6]
}
