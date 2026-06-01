#include "TextureManager.hpp"

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager* TextureManager::Instance() {
    if (!s_pInstance) {
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
    // 1. Cargar la imagen en una superficie temporal
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); // [2]

    if (!pTempSurface) {
        SDL_Log("Error al cargar %s: %s", fileName.c_str(), SDL_GetError());
        return false; // [3]
    }

    // 2. Crear la textura a partir de la superficie
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    // 3. Liberar la superficie (En SDL3 se usa SDL_DestroySurface)
    SDL_DestroySurface(pTempSurface); // [4]

    if (!pTexture) {
        SDL_Log("Error al crear textura para %s: %s", id.c_str(), SDL_GetError());
        return false;
    }

    // 4. Almacenar la textura en el mapa para su reutilización
    m_textureMap[id] = pTexture; // [5]
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, 
              SDL_Renderer* pRenderer, SDL_FlipMode flip)
{
    // 1. Definir dónde se dibujará en pantalla (Destination)
    SDL_FRect destRect;
    destRect.x = (float)x;
    destRect.y = (float)y;
    destRect.w = (float)width;
    destRect.h = (float)height;

    // 2. Renderizar la textura
    SDL_RenderTexture(pRenderer, m_textureMap[id], nullptr, &destRect);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, 
                   int currentRow, int currentFrame, 
                   SDL_Renderer* pRenderer, SDL_FlipMode flip)
{
    // 1. Definir el área del frame en la textura (Source)
    SDL_FRect srcRect;
    srcRect.x = (float)(width * currentFrame);
    srcRect.y = (float)(height * (currentRow - 1)); // 1-based para filas
    srcRect.w = (float)width;
    srcRect.h = (float)height;

    // 2. Definir dónde se dibujará en pantalla (Destination)
    SDL_FRect destRect;
    destRect.x = (float)x;
    destRect.y = (float)y;
    destRect.w = (float)width;
    destRect.h = (float)height;

    // 3. Renderizar con rotación 0 y sin centro específico (nullptr)
    // SDL_RenderTextureRotated es el reemplazo de SDL_RenderCopyEx en SDL3 [1]
    SDL_RenderTextureRotated(pRenderer, m_textureMap[id], &srcRect, &destRect, 0.0, nullptr, flip);
}

void TextureManager::clearFromTextureMap(std::string id) {
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL_DestroyTexture(it->second);
        m_textureMap.erase(it);
    }
}

void TextureManager::drawTile(std::string id, int margin, int spacing, 
                              int x, int y, int width, int height, 
                              int currentRow, int currentFrame, 
                              SDL_Renderer* pRenderer) 
{
    SDL_FRect srcRect;
    SDL_FRect destRect;

    // Cálculo del área a copiar del tileset (Source) [1]
    // Se suma el margen inicial y el desplazamiento por (tamaño + espacio)
    srcRect.x = (float)(margin + (spacing + width) * currentFrame);
    srcRect.y = (float)(margin + (spacing + height) * currentRow);
    srcRect.w = (float)width;
    srcRect.h = (float)height;

    // Cálculo del área de destino en la pantalla (Destination) [1]
    destRect.x = (float)x;
    destRect.y = (float)y;
    destRect.w = (float)width;
    destRect.h = (float)height;

    // En SDL3, SDL_RenderCopyEx se renombra a SDL_RenderTextureRotated [2]
    // m_textureMap es el std::map que almacena tus SDL_Texture*
    SDL_RenderTextureRotated(pRenderer, m_textureMap[id], &srcRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);
}
