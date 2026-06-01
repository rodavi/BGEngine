#include "LevelParser.hpp"
#include "TextureManager.hpp"
#include "GameObjectFactory.hpp"
#include "TileLayer.hpp"
#include "ObjectLayer.hpp"
#include "base64.hpp" // Necesario para decodificar tiles [5]
#include <zlib.h>   // Necesario para descomprimir tiles [5]

Level* LevelParser::parseLevel(const char* levelFile, SDL_Renderer* pRenderer){
    tinyxml2::XMLDocument levelDocument;
    if (!levelDocument.LoadFile(levelFile)) return nullptr;

    Level* pLevel = new Level();
    tinyxml2::XMLElement* pRoot = levelDocument.RootElement();

    // 1. Extraer dimensiones del mapa [6]
    pRoot->QueryIntAttribute("tilewidth", &m_tileSize);
    pRoot->QueryIntAttribute("width", &m_width);
    pRoot->QueryIntAttribute("height", &m_height);

    for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets(), pRenderer); // [7]
        } else if (e->Value() == std::string("layer")) {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets()); // [8]
        } else if (e->Value() == std::string("objectgroup")) {
            parseObjectLayer(e, pLevel->getLayers()); // [9]
        }
    }
    return pLevel;
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*> *pLayers) {
    ObjectLayer* pObjectLayer = new ObjectLayer();

    for (tinyxml2::XMLElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            int x, y, width, height, numFrames, callbackID;
            std::string textureID, type;

            e->QueryIntAttribute("x", &x);
            e->QueryIntAttribute("y", &y);
            e->QueryIntAttribute("width", &width);
            e->QueryIntAttribute("height", &height);
            e->QueryIntAttribute("numFrames", &numFrames);
            type = e->Attribute("type");

            // Crear objeto mediante la Factoría [10, 11]
            GameObject* pGO = TheGameObjectFactory::Instance()->create(type);
            
            // Cargar propiedades personalizadas (obviando detalles de loop por brevedad)
            pGO->load(new LoaderParams(x, y, width, height, type, numFrames)); 
            pObjectLayer->getGameObjects()->push_back(pGO);
        }
    }
    pLayers->push_back(pObjectLayer);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement, 
                                 std::vector<Layer*> *pLayers, 
                                 const std::vector<Tileset>* pTilesets) 
{
    // Aquí instancias la capa con las dimensiones que el parser ya conoce
    TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);

    // ... resto de la lógica para decodificar base64 y descomprimir zlib ...
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, 
                                 std::vector<Tileset>* pTilesets, 
                                 SDL_Renderer* pRenderer) // <--- Recibido por parámetro [3]
{
    // Usamos el renderer pasado para cargar la textura en el TextureManager
    TheTextureManager::Instance()->load(
        pTilesetRoot->FirstChildElement()->Attribute("source"), 
        pTilesetRoot->Attribute("name"), 
        pRenderer 
    );

    // 2. Extraer los atributos del XML para llenar el struct Tileset
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("height", &tileset.height);
    pTilesetRoot->QueryIntAttribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->QueryIntAttribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->QueryIntAttribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->QueryIntAttribute("spacing", &tileset.spacing);
    pTilesetRoot->QueryIntAttribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");

    // 3. Calcular cuántas columnas de tiles tiene la imagen
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    // 4. Guardar el tileset en el vector del nivel
    pTilesets->push_back(tileset);
}