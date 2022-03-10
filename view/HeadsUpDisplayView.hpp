#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "View.hpp"
#include "Player.h"

class HeadsUpDisplayView : public View
{
    sf::RenderWindow *_renderWindow;
    Player *_player1;
    Player *_player2;

    sf::Font _font;

    public:
    HeadsUpDisplayView(sf::RenderWindow *renderWindow);

    void setPlayer1(Player *player);
    void setPlayer2(Player *player);

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
