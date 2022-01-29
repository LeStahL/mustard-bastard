#pragma once

#include <InputController.hpp>
#include <MainMenuState.hpp>
// #include <MenuController.hpp>
class MenuController;

#include <SFML/System.hpp>

class MainMenuInputController : public InputController 
{
    MainMenuState *_mainMenuState;
    MenuController *_menuController;
    sf::Clock _disableClock;
    bool _disabled;

public:
    MainMenuInputController(MainMenuState *mainMenuState, MenuController *menuController);
    void pullEvents() override;

    static const double disableTime;
};
