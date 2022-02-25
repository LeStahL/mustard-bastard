#pragma once

#include <InputController.hpp>
#include <PauseMenuState.hpp>
class MenuController;

#include <SFML/System.hpp>

class PauseMenuInputController : public InputController 
{
    PauseMenuState *_PauseMenuState;
    MenuController *_menuController;
    sf::Clock _disableClock;
    bool _disabled;

public:
    PauseMenuInputController(PauseMenuState *PauseMenuState, MenuController *menuController);
    void pullEvents() override;

    static const double disableTime;
};
