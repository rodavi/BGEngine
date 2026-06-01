#include "Player.hpp"
#include <iostream>

Player::Player() : SDLGameObject() 
{}

void Player::load(const LoaderParams* pParams) {
    SDLGameObject::load(pParams); // Carga propiedades comunes
    m_state = PlayerState::IDLE; // Estado inicial
    setAnimation(3, 1); // Fila 3: Idle (1 cuadro)
}

void Player::draw(SDL_Renderer* pRenderer)
{
    // Implementación de dibujo
    //std::cout << "Dibujando Player con ID: " << getId() << std::endl;
    SDLGameObject::draw(pRenderer); // Llamada a la función base para dibujar el sprite
    
}

void Player::update(double dt) 
{
    // Implementación de actualización
    m_velocity.x = 0; // Reiniciar velocidad por frame
    handleInput();      // Lógica de control
    
    SDLGameObject::update(dt); // Aplica m_position += m_velocity
    animate();               // Lógica de animación genérica
}

void Player::render(double alpha) 
{
    // Implementación de renderizado
}

void Player::handleInput() {
    if (m_state == PlayerState::DYING) return; // No procesar input si está muriendo

    if (m_velocity.y < 0) {
        if (m_state != PlayerState::JUMPING) {
            m_state = PlayerState::JUMPING;
            setAnimation(2, 1, 150); // Fila 3: Salto (1 cuadros)
        }
    } else if (m_velocity.x != 0) {
        if (m_state != PlayerState::WALKING) {
            m_state = PlayerState::WALKING;
            setAnimation(1, 8, 100); // Fila 1: Caminar (8 cuadros)
        }
    } else {
        if (m_state != PlayerState::IDLE) {
            m_state = PlayerState::IDLE;
            setAnimation(3, 1);      // Fila 3: Idle (1 cuadro)
        }
    }
}

Player::~Player() {
    // Implementación de destrucción
}