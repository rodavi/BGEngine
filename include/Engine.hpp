#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

class Engine {

public:
    Engine();
    ~Engine();
    bool init();
    void handleEvents();
    void update();
    void render();
    void cleanup();
    void run();
    

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    bool m_bIsRunning;

    const double MS_PER_UPDATE = 16.666; // 60 FPS fijos para la lógica [3]
    
};
