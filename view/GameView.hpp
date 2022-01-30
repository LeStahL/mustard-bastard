#pragma once

#include <vector>
#include <GameViewModel.hpp>
#include <Animation.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "View.hpp"

class GameView : public View {
    private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Vector2f> _spriteCenters;
    std::vector<sf::IntRect> _rects;
    std::vector<Animation> _animations;

    sf::RenderWindow *_renderWindow;
    GameViewModel& model;

    void adjustSprite(IsDrawable *drawable);

    public:
    GameView(sf::RenderWindow *renderWindow, GameViewModel& model);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    private:
    bool loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frame_count);
};