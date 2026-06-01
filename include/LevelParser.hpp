#pragma once
#include "tinyxml2.h"
#include "Level.hpp"
#include "Layer.hpp"
#include <vector>

class LevelParser {
public:
    Level* parseLevel(const char* levelFile, SDL_Renderer* pRenderer); // Punto de entrada principal

private:
    void parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets, SDL_Renderer* pRenderer);
    void parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);
    void parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*> *pLayers);
    void parseTextures(tinyxml2::XMLElement* pTextureRoot);

    int m_tileSize;
    int m_width;
    int m_height;
};