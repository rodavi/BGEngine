#pragma once
#include "GameObject.hpp"
#include "LoaderParams.hpp"
#include "utils.hpp"
#include "TextureManager.hpp"


class SDLGameObject : public GameObject {
public:
    SDLGameObject(const LoaderParams* pParams);
    void draw(SDL_Renderer* pRenderer) override;
    void update(double dt) override;
    void render(double alpha) override;
    ~SDLGameObject() override;
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width, m_height;
    int m_currentRow, m_currentFrame, m_numFrames;
    std::string m_textureID;

    void animate(); // Función genérica
    int m_animSpeed = 100; // Milisegundos por cuadro (por defecto 100)
    void setAnimation(int row, int numFrames, int animSpeed = 100); // Configura la animación (fila, número de cuadros, velocidad)
};