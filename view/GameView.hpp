#pragma once

#include <vector>
#include <GameViewModel.hpp>
#include <Animation.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameView {
    private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;
    std::vector<Animation> _animations;

    sf::RenderWindow *_renderWindow;
    GameViewModel& model;

    public:
    GameView(sf::RenderWindow *renderWindow, GameViewModel& model);

    bool draw(double time);
    bool setUp();
    bool tearDown();
};