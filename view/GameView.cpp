#include <GameView.hpp>
#include <IsDrawable.hpp>
#include <iostream>

GameView::GameView(sf::RenderWindow *renderWindow, GameViewModel& model) :
        _renderWindow(renderWindow),
        model(model) {
}

bool GameView::draw(double time) {
    for(size_t layer = 0; layer < Z_LAYER_COUNT; layer++) {
        std::vector<IsDrawable*>* drawableList = model.getLayer(layer);

        for(auto it = std::begin(*drawableList); it != std::end(*drawableList); ++it) {
            int id = (*it)->getGraphicId();
            sf::Vector2f position((*it)->x, (*it)->y);

            switch((*it)->getDrawType()) {
                case IsDrawable::DrawType::animation:
                    _animations.at(id).update(time);
                    _sprites.at(id).setPosition(position);
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
    _textures.resize(3);
    _textures[0].loadFromFile("assets/bastard.png");
    _textures[1].loadFromFile("assets/Zombie_01.png");
    _textures[2].loadFromFile("assets/mainscreen.png");

    _sprites.resize(3);
    _sprites[0].setTexture(_textures[0]);
    _sprites[1].setTexture(_textures[1]);
    _sprites[2].setTexture(_textures[2]);

    _animations.push_back(Animation(&_sprites[0], .1));
    for(int i=0; i<4; ++i)
        _animations[0].addFrame(96*i, 0, 96, 160);

    _animations.push_back(Animation(&_sprites[1], .1));
    for(int i=0; i<2; ++i)
        _animations[1].addFrame(150*i, 0, 150, 210);

    return true;
}

bool GameView::tearDown() {
    return true;
}