#pragma once

#include <InputRouter.hpp>
#include <MainMenuState.hpp>
class MenuController;

class MainMenuInputRouter : public InputRouter
{
    MainMenuState *_mainMenuState;
    MenuController *_menuController;

public:
    MainMenuInputRouter(MainMenuState *mainMenuState, MenuController *menuController);
    void pullEvents() override;

    static const double disableTime;
};
