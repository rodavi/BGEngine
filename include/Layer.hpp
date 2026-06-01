#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Layer {
public:
    virtual void render(SDL_Renderer* pRenderer) = 0; // Agregado el renderer
    virtual void update() = 0; 
protected:
    virtual ~Layer() {}
};