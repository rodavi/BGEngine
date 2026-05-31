# The Board Game Engine (BGEngine)
BGEngine is a personal project, where the main intention is to learn C/C++, CMake, Ctest and Game development.

## Introduction

## Dependencies

## Development Phases

- Fase 1: Cimientos y Gestión de Proyecto (Modern CMake)
Antes de escribir código del motor, debemos establecer un entorno profesional. El aprendizaje aquí se centra en la automatización y portabilidad.

    - Desarrollo: Configura una estructura de carpetas modular (src, include, extern, tests) utilizando Modern CMake. Define objetivos lógicos (targets) en lugar de manipular archivos individuales para mantener el código limpio y mantenible.
    - Aprendizaje: Estudia la diferencia entre la etapa de configuración, generación y construcción en CMake. Aprende a usar FetchContent para gestionar dependencias externas (como SDL3) de forma automática al configurar el proyecto.
    - Tarea Inicial: Crea un "Hello World" que compile con CMake, use el estándar C++20 y genere un binario en una carpeta build separada de la fuente (out-of-source build).

- Fase 2: Capa de Abstracción de Plataforma (SDL3)
Aquí aprenderás a interactuar con el hardware (gráficos, entrada, sonido) sin depender del sistema operativo.

    - Desarrollo: Implementa la inicialización de SDL3. Ten en cuenta que en SDL3, las funciones de inicialización (como SDL_Init) ahora devuelven un bool en lugar de códigos negativos. Debes incluir <SDL3/SDL_main.h> explícitamente en el archivo que contenga tu función main().
    - Aprendizaje: Migración y APIs modernas. Investiga cómo SDL3 maneja ahora el renderizado por texturas acelerado por hardware de forma predeterminada.
    - Prueba CTest: Crea una prueba simple que verifique que el motor puede inicializar y cerrar el subsistema de video de SDL3 correctamente.

- Fase 3: El Núcleo del Motor (Game Loop y Arquitectura)
El motor necesita un "latido" constante para procesar la lógica de los juegos de mesa.

    - Desarrollo: Implementa un Game Loop que desacople la progresión del tiempo del procesamiento de la CPU. Estructúralo en tres fases: handleEvents, update y render.
    Aprendizaje: Patrones de secuenciación. Estudia el patrón Update Method, donde cada objeto del juego simula un marco de comportamiento a la vez.
    - Optimización: Aprende sobre el Double Buffer para evitar parpadeos visuales al renderizar, asegurando que el estado del juego se muestre como un paso instantáneo.

- Fase 4: Lógica de Juegos de Mesa (Patrones de Comportamiento)
Los juegos de mesa tienen requisitos únicos como turnos, movimientos legales y estados de juego claros.

    - Patrón Command (Esencial): Implementa las acciones de los jugadores (mover pieza, robar carta) como objetos Command. Esto te facilitará enormemente añadir funciones de deshacer/rehacer (undo/redo), vitales en prototipado de juegos de mesa.
    - Patrón State: Utiliza máquinas de estados finitos (FSM) para gestionar las fases del juego (Turno del Jugador, Fase de Resolución, Menú Principal).
    - Aprendizaje: Desacoplamiento. Practica cómo el patrón Observer permite que el sistema de puntuación o de logros reaccione a eventos del juego sin estar fuertemente vinculado a la lógica del tablero.

- Fase 5: Verificación con CTest y Calidad de Software
Para un motor, la estabilidad es clave.

    - Desarrollo: Integra CTest para ejecutar una suite de pruebas automatizadas. Separa la lógica de tu main() a una función run() para poder vincularla y probarla individualmente sin violar la regla de definición única (ODR).
    - Aprendizaje: Análisis dinámico. Utiliza herramientas como Valgrind (Memcheck) a través de CTest para detectar fugas de memoria (memory leaks) de forma temprana.
    Tarea de Calidad: Configura una prueba que simule una secuencia de comandos (movimientos en el tablero) y verifique que el estado final del juego sea el esperado.

- Fase 6: Flexibilidad y Herramientas (Data-Driven Design)
Un motor debe permitir crear juegos sin recompilar todo el código.

    - Desarrollo: Adopta una arquitectura Data-Driven. Define la configuración del tablero, las estadísticas de las piezas o las reglas en archivos externos (JSON o XML).
    Herramientas: Considera integrar una biblioteca de GUI inmediata como Dear ImGui para crear un editor visual o herramientas de depuración que te permitan modificar valores en tiempo real.
    - Aprendizaje: Patrón Type Object. Aprende a definir "clases" de piezas en datos, de modo que un nuevo tipo de unidad sea solo una nueva instancia de datos y no una nueva clase de C++.