#pragma once

#include <InputRouter.hpp>
#include <MainMenuState.hpp>
class MenuController;

class HighscoreMenuInputRouter : public InputRouter
{
    MainMenuState *_mainMenuState;
    MenuController *_menuController;

public:
    HighscoreMenuInputRouter(MainMenuState *mainMenuState, MenuController *menuController);
    void pullEvents() override;
};
