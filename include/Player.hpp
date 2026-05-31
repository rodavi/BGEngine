#include "SDLGameObject.hpp"
#include "LoaderParams.hpp"

enum class PlayerState { IDLE, WALKING, JUMPING, DYING };

class Player : public SDLGameObject {
public:
    Player(const LoaderParams *pParams);
    void draw(SDL_Renderer* pRenderer) override;
    void update(double dt) override;
    void render(double alpha) override;
    ~Player() override;

    private:
    void handleInput(); // Manejo de entrada específico del jugador
    PlayerState m_state = PlayerState::IDLE; // Estado actual del jugador
};