#include "SDLGameObject.hpp"
#include "LoaderParams.hpp"
#include "GameObjectFactory.hpp"

enum class PlayerState { IDLE, WALKING, JUMPING, DYING };

class Player : public SDLGameObject {
public:
    Player();
    void load(const LoaderParams* pParams) override;
    void draw(SDL_Renderer* pRenderer) override;
    void update(double dt) override;
    void render(double alpha) override;
    ~Player() override;

    private:
    void handleInput(); // Manejo de entrada específico del jugador
    PlayerState m_state = PlayerState::IDLE; // Estado actual del jugador
};

class PlayerCreator : public BaseCreator {
public:
    // Retorna una nueva instancia de Player como un puntero genérico a GameObject
    GameObject* createGameObject() const override {
        return new Player();
    }
};