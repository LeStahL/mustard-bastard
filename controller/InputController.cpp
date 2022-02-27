#include <InputController.hpp>

sf::Keyboard::Key InputController::_pressedKey = sf::Keyboard::Key::Unknown;
sf::Clock InputController::_disableClock = sf::Clock();
