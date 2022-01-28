#include <GameInputController.hpp>

#include <SFML/Window.hpp>

GameInputController::GameInputController(GameLogic& gameLogic) :
        gameLogic(gameLogic) {
}

void GameInputController::pullEvents() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        gameLogic.moveForward();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        gameLogic.moveBackward();
    } else {
        gameLogic.stay();
    }
}
