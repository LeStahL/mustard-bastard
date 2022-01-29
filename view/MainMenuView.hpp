#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "View.hpp"
#include "MenuState.hpp"
#include "MainMenuState.hpp"

class MainMenuView : public View
{
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;

    MenuState *_menuState;
    MainMenuState *_mainMenuState;
    sf::RenderWindow *_renderWindow;

    public:
    MainMenuView(sf::RenderWindow *renderWindow, MenuState *menuState, MainMenuState *mainMenuState);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;
};
