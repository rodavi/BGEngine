#pragma once
#include "LoaderParams.hpp"
#include "utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

class GameObject {
public:
    virtual void draw(SDL_Renderer* pRenderer)=0;
    virtual void update(double dt)=0;
    virtual void render(double alpha)=0;

    std::string getId() const { return m_id; }
    bool isDead() const { return m_isDead; }
    void markAsDead() { m_isDead = true; }
    
    // El destructor debe ser virtual para asegurar una limpieza correcta [3]
    virtual ~GameObject() {} 

protected:
    GameObject(const LoaderParams* pParams) : m_id(pParams->getTextureID()), m_isDead(false) {}

private:
    // Atributos del objeto
    std::string m_id; // Identificador único del objeto
    bool m_isDead = false; // Estado de vida del objeto
    // Otros atributos...
};
