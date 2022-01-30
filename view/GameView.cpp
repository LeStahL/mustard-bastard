#include <GameView.hpp>
#include <IsDrawable.hpp>
#include <iostream>
#include "ViewConst.h"

GameView::GameView(sf::RenderWindow *renderWindow, GameViewModel& model) :
    _renderWindow(renderWindow),
    model(model) {
}

void GameView::adjustSprite(IsDrawable *it)
{
    int id = it->getGraphicId();
    sf::Vector2f position(it->x, it->y);
    sf::Vector2f shift = _spriteCenters.at(id);

    float x_sign = it->facing_left ? -1 : 1;
    _sprites.at(id).setPosition(position - sf::Vector2f(x_sign * shift.x, shift.y));
    _sprites.at(id).setScale(sf::Vector2f(x_sign, 1));
}

bool GameView::draw(double time) {

    // hack: this is for the Entity <-> IsDrawable sync for coordinates etc.
    model.syncDrawableEntities();

    for(size_t layer = 0; layer < Z_LAYER_COUNT; layer++) {
        std::vector<IsDrawable*>* drawableList = model.getLayer(layer);

        for(auto it = std::begin(*drawableList); it != std::end(*drawableList); ++it) {
            int id = (*it)->getGraphicId();
            sf::Vector2f position((*it)->x, (*it)->y);

            switch((*it)->getDrawType()) {
                case IsDrawable::DrawType::animation:
                    _animations.at(id).update(time);
                    adjustSprite(*it);
                    _renderWindow->draw(_sprites.at(id));
                    break;

                case IsDrawable::DrawType::texture:
                    _renderWindow->draw(_sprites.at(id));
                    break;

                case IsDrawable::DrawType::primitive:
                    (*it)->customDraw(time);
                    break;
            }
        }
    }

    return true;
}

bool GameView::setUp() {
    // reserving space is needed, becaus references on vector elements
    // become invalid if a new element is added
    const size_t RESERVE_SPACE = 20;
    _textures.reserve(RESERVE_SPACE);
    _sprites.reserve(RESERVE_SPACE);
    _animations.reserve(RESERVE_SPACE);
    _spriteCenters.reserve(RESERVE_SPACE);

    loadAnimation("assets/bastard.png", BASTARD_PIXEL_WIDTH, BASTARD_PIXEL_HEIGHT, BASTARD_FRAME_COUNT);
    loadAnimation("assets/Zombie_01.png", ZOMBIE_01_PIXEL_WIDTH, ZOMBIE_01_PIXEL_HEIGHT, ZOMBIE_01_FRAME_COUNT);
    loadAnimation("assets/Eisberg_01.png", ICEBERG_PIXEL_WIDTH, ICEBERG_PIXEL_HEIGHT, ICEBERG_FRAME_COUNT);
    loadAnimation("assets/katze_01.png", CAT_PIXEL_WIDTH, CAT_PIXEL_HEIGHT, CAT_FRAME_COUNT);

    /*
    _textures.resize(4);
    _textures[0].loadFromFile("assets/bastard.png");
    _textures[1].loadFromFile("assets/Zombie_01.png");
    _textures[2].loadFromFile("assets/Eisberg_01.png");
    _textures[3].loadFromFile("assets/katze_01.png");

    _sprites.resize(4);
    _sprites[0].setTexture(_textures[0]);
    _sprites[1].setTexture(_textures[1]);
    _sprites[2].setTexture(_textures[2]);
    _sprites[3].setTexture(_textures[3]);

    _animations.push_back(Animation(&_sprites[0], .1));
    for(int i=0; i<4; ++i)
        _animations[0].addFrame(96*i, 0, 96, 160);

    _animations.push_back(Animation(&_sprites[1], .1));
    for(int i=0; i<2; ++i)
        _animations[1].addFrame(150*i, 0, 150, 210);

    _animations.push_back(Animation(&_sprites[2], .1));
    for(int i=0; i<2; ++i)
        _animations[2].addFrame(400*i, 0, 400, 260);

    _animations.push_back(Animation(&_sprites[3], .1));
    for(int i=0; i<2; ++i)
        _animations[3].addFrame(150*i, 0, 150, 150);

    _spriteCenters.clear();
    _spriteCenters.push_back(sf::Vector2f(0.5 * BASTARD_PIXEL_WIDTH, BASTARD_PIXEL_HEIGHT));
    _spriteCenters.push_back(sf::Vector2f());
    _spriteCenters.push_back(sf::Vector2f());
    _spriteCenters.push_back(sf::Vector2f());*/

    return true;
}

bool GameView::tearDown() {
    return true;
}

bool GameView::loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frameCount) {
    _textures.push_back(sf::Texture());
    if(!_textures.back().loadFromFile(filename)) {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    _sprites.push_back(sf::Sprite(_textures.back()));

    _animations.push_back(Animation(&_sprites.back(), .1));
    for(int i=0; i<frameCount; ++i)
        _animations.back().addFrame(spriteWidthPx*i, 0, spriteWidthPx, spriteHeightPx);

    _spriteCenters.push_back(sf::Vector2f(0.5 * spriteWidthPx, spriteHeightPx));

    return true;
}