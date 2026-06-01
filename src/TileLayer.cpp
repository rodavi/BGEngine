#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

TileLayer::TileLayer(int tileSize, int gameWidth, int gameHeight, const std::vector<Tileset> &tilesets) 
    : m_tileSize(tileSize), m_tilesets(tilesets), m_position{0,0}, m_velocity{0,0} {
    
    m_numColumns = (gameWidth / m_tileSize);
    m_numRows = (gameHeight / m_tileSize);
}

void TileLayer::update() {
    //m_position += m_velocity; // Actualizamos posición para el scroll [6]
    m_position.x += m_position.x;
    m_position.y += m_position.y;
}

void TileLayer::render(SDL_Renderer* pRenderer) {
    int x, y, x2, y2 = 0;

    // x, y: Índice del tile donde empezamos a dibujar (basado en scroll) [2, 7]
    x = m_position.x / m_tileSize;
    y = m_position.y / m_tileSize;

    // x2, y2: Desplazamiento en píxeles dentro del primer tile para scroll suave [2, 4]
    x2 = int(m_position.x) % m_tileSize;
    y2 = int(m_position.y) % m_tileSize;

    for(int i = 0; i < m_numRows; i++) {
        for(int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x]; // Obtenemos el ID del tile en esa posición [8]

            if(id == 0) continue; // ID 0 suele ser un espacio vacío [3, 8]

            Tileset tileset = getTilesetByID(id);
            id--; // Ajustamos el ID para que coincida con el índice base 0 de la textura [9, 10]

            // Dibujamos el tile calculando su fila/columna dentro de su tileset original [11, 12]
            TheTextureManager::Instance()->drawTile(
                tileset.name, tileset.margin, tileset.spacing, 
                (j * m_tileSize) - x2, (i * m_tileSize) - y2, 
                m_tileSize, m_tileSize, 
                (id - (tileset.firstGridID - 1)) / tileset.numColumns, 
                (id - (tileset.firstGridID - 1)) % tileset.numColumns, 
                pRenderer
            );
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) {
    for(size_t i = 0; i < m_tilesets.size(); i++) {
        if(i + 1 <= m_tilesets.size() - 1) {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }
    return Tileset(); // Retornar tileset vacío si no se encuentra [8, 9]
}