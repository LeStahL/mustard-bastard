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

    loadAnimation("assets/bastard_standing.png", BASTARD_STANDING_PIXEL_WIDTH, BASTARD_STANDING_PIXEL_HEIGHT, BASTARD_STANDING_FRAME_COUNT);
    loadAnimation("assets/bastard_walking.png", BASTARD_WALKING_PIXEL_WIDTH, BASTARD_WALKING_PIXEL_HEIGHT, BASTARD_WALKING_FRAME_COUNT);
    loadAnimation("assets/bastard_attack.png", BASTARD_ATTACK_PIXEL_WIDTH, BASTARD_ATTACK_PIXEL_HEIGHT, BASTARD_ATTACK_FRAME_COUNT);
    loadAnimation("assets/Zombie_01.png", ZOMBIE_PIXEL_WIDTH, ZOMBIE_PIXEL_HEIGHT, ZOMBIE_FRAME_COUNT);
    loadAnimation("assets/katze_01.png", CAT_PIXEL_WIDTH, CAT_PIXEL_HEIGHT, CAT_FRAME_COUNT);
    loadAnimation("assets/Eisberg_01.png", ICEBERG_PIXEL_WIDTH, ICEBERG_PIXEL_HEIGHT, ICEBERG_FRAME_COUNT);
    loadAnimation("assests/Fee_01.png", FAIRY_PIXEL_WIDTH, FAIRY_PIXEL_WIDTH, FAIRY_FRAME_COUNT);
    
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