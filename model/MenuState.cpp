#include "MenuState.hpp"

MenuState::MenuState()
    : _type(MenuState::MenuType::MainMenu)
{
}

MenuState::MenuType MenuState::currentType()
{
    return _type;
}

void MenuState::setType(MenuState::MenuType type)
{
    _type = type;
}
