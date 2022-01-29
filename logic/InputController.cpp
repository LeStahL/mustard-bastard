#include <InputController.h>

#include <SFML/Window.hpp>

InputController::InputController(GameLogic& gameLogic) :
        gameLogic(gameLogic) {
}

void InputController::pullEvents() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        gameLogic.moveForward();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        gameLogic.moveBackward();
    } else {
        gameLogic.stay();
    }
}