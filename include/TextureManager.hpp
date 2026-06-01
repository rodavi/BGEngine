#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager* Instance(); // Singleton Instance

    // Carga una imagen y la asocia a un ID [6]
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    // Dibuja una textura estática completa [7]
    void draw(std::string id, int x, int y, int width, int height, 
              SDL_Renderer* pRenderer, SDL_FlipMode flip = SDL_FLIP_NONE);

    // Dibuja un cuadro específico de una animación (sprite sheet) [3]
    void drawFrame(std::string id, int x, int y, int width, int height, 
                   int currentRow, int currentFrame, 
                   SDL_Renderer* pRenderer, SDL_FlipMode flip = SDL_FLIP_NONE);

    // Libera una textura específica de la memoria [8, 9]
    void clearFromTextureMap(std::string id);
    
    void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, 
                  int currentRow, int currentFrame, SDL_Renderer* pRenderer);
private:
    TextureManager() {} // Constructor privado para el Singleton [2]
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap; // Contenedor de texturas [3]

};
typedef TextureManager TheTextureManager; // Alias para un acceso más limpio [10]
