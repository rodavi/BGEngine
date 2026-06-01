#pragma once
#include <string>
#include <vector>
#include "Layer.hpp"

// Estructura para almacenar información de los tilesets [4]
struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level {
public:
    ~Level() {}
    
    void update(); // Actualiza todas las capas del nivel [5]
    void render(SDL_Renderer* pRenderer); // Dibuja todas las capas del nivel [5]

    // Getters para que el LevelParser pueda poblar el nivel [2, 5]
    std::vector<Tileset>* getTilesets() { return &m_tilesets; }
    std::vector<Layer*>* getLayers() { return &m_layers; }

private:
    // El constructor es privado para forzar el uso de LevelParser [6]
    friend class LevelParser;
    Level();

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};