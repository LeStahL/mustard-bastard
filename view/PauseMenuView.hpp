#pragma once

#include <View.hpp>
#include <PauseMenuState.hpp>

#include <SFML/Graphics.hpp>

class PauseMenuView : public View
{
    private:
    sf::Texture pauseMenuTexture;
    sf::Texture pauseMenuHighlightsTexture;
    sf::Sprite  pauseMenuSprite;
    sf::Sprite  pauseMenuHighlightsSprite;
    sf::IntRect highlightsRect;

    sf::RenderWindow *renderWindow;
    PauseMenuState *pauseMenuState;

    public:
    PauseMenuView(sf::RenderWindow *renderWindow, PauseMenuState* pauseMenuState);

    bool draw(double time);
    bool setUp();
    bool tearDown();
};
