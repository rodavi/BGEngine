#pragma once

#include "Engine.hpp"

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
}

void Engine::render() 
{
    // 1. Establecer el color con el que se limpiará la pantalla (por ejemplo, negro)
    // Nota: En SDL3, SDL_SetRenderDrawColor ahora devuelve un bool para indicar éxito [3, 4].
    SDL_SetRenderDrawColor(m_pRenderer, 0, 200, 100, 255);

    // 2. Limpiar el renderizador (Back Buffer) con el color seleccionado
    // Esto borra lo que se dibujó en el frame anterior [4, 5].
    SDL_RenderClear(m_pRenderer);

    // 3. Espacio para la lógica de dibujado de objetos (Fase 4 y 6)
    // Aquí es donde en el futuro llamarás a las funciones de renderizado de tus piezas o tablero.
    SDL_FRect rect = {100.0f, 100.0f, 200.0f, 200.0f};
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(m_pRenderer, &rect);
    // 4. Presentar el contenido en pantalla
    // SDL_RenderPresent realiza el intercambio de buffers (Double Buffering), 
    // lo que evita el parpadeo visual al mostrar el frame completo de una vez [1, 2].
    // En SDL3, esta función también devuelve un bool [4].
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



