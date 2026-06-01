#pragma once

#include "Engine.hpp"
#include "GameObjectFactory.hpp"
#include "Player.hpp"
#include "LevelParser.hpp"

Engine::Engine() : m_pWindow(nullptr), m_pRenderer(nullptr), m_bIsRunning(false) 
{

}

Engine::~Engine()
{
    cleanup();
}

bool Engine::init(const char* title, int width, int height) 
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!m_pWindow) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL);
    if (!m_pRenderer) {
        std::cerr << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return false;
    }

    // Inicialización de texturas u otros recursos puede ir aquí (Fase 3)
    if(!TheTextureManager::Instance()->load("assets/AnimatedAstronout.png", "astronaut", m_pRenderer)) { // Ejemplo de carga de textura [6]
        std::cerr << "Error al cargar la textura: " << SDL_GetError() << std::endl;
        return false;
    }
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator()); 

    // 4. Carga del nivel inicial usando LevelParser
    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel("assets/map1.tmx", m_pRenderer); // Carga el nivel y le pasa el renderer para que pueda cargar texturas [7]

    if (m_pLevel == nullptr) {
        return false;
    }

    m_bIsRunning = true;
    return true;
}

void Engine::handleEvents() {
    SDL_Event event;

    // SDL_PollEvent extrae eventos de la cola uno por uno. 
    // Usamos un bucle 'while' para procesar todos los eventos acumulados en este frame [2, 3].
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // El usuario ha solicitado cerrar la aplicación (clic en la X o Alt+F4) [1].
            case SDL_EVENT_QUIT:
                m_bIsRunning = false; // Detiene el bucle principal en Engine::run [3, 4].
                break;

            // Aquí añadirás más adelante el manejo de teclado o ratón (Fase 4).
            default:
                break;
        }
    }
}

void Engine::update() 
{
    // Aquí se actualizará la lógica del juego en el futuro
    m_gameObjectManager.update(0.5); // Actualiza todos los objetos del juego (pasando un delta fijo por ahora)
}

void Engine::render() 
{
    SDL_RenderClear(m_pRenderer);

    // El Engine entrega su m_pRenderer al manager
    m_gameObjectManager.draw(m_pRenderer); 

    SDL_RenderPresent(m_pRenderer);
}

void Engine::cleanup() 
{
    if (m_pRenderer) {
        SDL_DestroyRenderer(m_pRenderer);
        m_pRenderer = nullptr;
    }
    if (m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
        m_pWindow = nullptr;
    }
    SDL_Quit();
    SDL_Log("BGEngine: Limpieza completada con éxito.");
}

void Engine::run() {
    double previous = SDL_GetTicks();    // Tiempo de inicio [4]
    double lag = 0.0;

    while (m_bIsRunning) {                 // Bucle principal [5, 6]
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // 1. Procesar Entrada (sin bloqueo) [7, 8]
        handleEvents();

        // 2. Actualizar Lógica (Paso de tiempo fijo) [2, 4]
        // Se ejecuta tantas veces como sea necesario para alcanzar el tiempo real
        while (lag >= MS_PER_UPDATE) {
            update(); 
            lag -= MS_PER_UPDATE;
        }

        // 3. Renderizar (frecuencia variable) [9-11]
        // Opcionalmente puedes pasar 'lag / MS_PER_UPDATE' para interpolación [12]
        render();

    }
    cleanup(); // Limpieza al salir [13]
}



