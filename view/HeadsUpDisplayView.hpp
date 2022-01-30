#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "View.hpp"
#include "MenuState.hpp"
#include "Player.h"

class HeadsUpDisplayView : public View
{
    MenuState *_menuState;
    sf::RenderWindow *_renderWindow;
    Player *_player1;
    Player *_player2;

    sf::Font _font;

    public:
    HeadsUpDisplayView(sf::RenderWindow *renderWindow, MenuState *menuState, Player *_player1, Player *player2 = nullptr);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    enum HUDSide
    {
        Left,
        Right
    };
    void drawPlayerHUD(Player *player, HUDSide where);
};
