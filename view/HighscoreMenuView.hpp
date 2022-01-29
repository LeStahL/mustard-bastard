#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "View.hpp"
#include "MenuState.hpp"
#include "HighscoreList.hpp"

class HighscoreMenuView : public View
{
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;

    MenuState *_menuState;
    HighscoreList *_highscoreList;
    sf::RenderWindow *_renderWindow;

    public:
    HighscoreMenuView(sf::RenderWindow *renderWindow, MenuState *menuState, HighscoreList *highscoreList);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;
};
