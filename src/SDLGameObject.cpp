#include "SDLGameObject.hpp"
#include <iostream>

SDLGameObject::SDLGameObject() : 
GameObject()
{}

void SDLGameObject::load(const LoaderParams* pParams) {
    // Carga de propiedades desde LoaderParams
    m_position = Vector2D{pParams->getX(), pParams->getY()};
    m_velocity = Vector2D{0, 0};
    m_acceleration = Vector2D{0, 0};
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_currentRow = 1;
    m_currentFrame = 1;
    m_numFrames = pParams->getNumFrames();
    m_textureID = pParams->getTextureID();
}


void SDLGameObject::draw(SDL_Renderer* pRenderer) {
    // SDL3 usa float para m_position para mayor suavidad
    //std::cout << "Dibujando SDLGameObject con ID: " << m_textureID << " en posición (" << m_position.x << ", " << m_position.y << ")" << std::endl;
    TheTextureManager::Instance()->drawFrame(
        m_textureID, (int)m_position.x, (int)m_position.y, 
        m_width, m_height, m_currentRow, m_currentFrame, 
        pRenderer
    );
}

void SDLGameObject::update(double dt) {
    // Implementación de actualización
    m_velocity.x += m_acceleration.x * dt;
}

void SDLGameObject::render(double alpha) {
    // Implementación de renderizado
}

void SDLGameObject::animate() {
    // Cicla m_currentFrame desde 0 hasta m_numFrames - 1
    m_currentFrame = int(((SDL_GetTicks() / m_animSpeed) % m_numFrames));
}

void SDLGameObject::setAnimation(int row, int numFrames, int animSpeed) {
    m_currentRow = row;
    m_numFrames = numFrames;
    m_animSpeed = animSpeed;
    m_currentFrame = 0; // Reiniciar animación
}

SDLGameObject::~SDLGameObject() {
    // Implementación de destrucción
}