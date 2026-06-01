#pragma once
#include "Layer.hpp"
#include "Level.hpp"
#include "utils.hpp"
#include <vector>

class TileLayer : public Layer {
public:
    // Recibe el tamaño del tile y una referencia a los tilesets del nivel
    TileLayer(int tileSize, int gameWidth, int gameHeight, const std::vector<Tileset> &tilesets);

    virtual void update() override;
    virtual void render(SDL_Renderer* pRenderer) override;

    // Getters y Setters para que el LevelParser configure la capa
    void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; }

    const std::vector<std::vector<int>>& getTileIDs() const { return m_tileIDs; }
    const Vector2D getPosition() const { return m_position; }
    int getTileSize() const { return m_tileSize; }

private:
    // Busca el tileset correspondiente basándose en el ID del tile
    Tileset getTilesetByID(int tileID);

    int m_numColumns; // Columnas visibles en pantalla
    int m_numRows;    // Filas visibles en pantalla
    int m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    const std::vector<Tileset>& m_tilesets;
    std::vector<std::vector<int>> m_tileIDs; // Matriz de IDs del mapa
};
