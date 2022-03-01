#include <InputRouter.hpp>

sf::Keyboard::Key InputRouter::_pressedKey = sf::Keyboard::Key::Unknown;
sf::Clock InputRouter::_disableClock = sf::Clock();
