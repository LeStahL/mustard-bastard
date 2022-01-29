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

            std::cout << position.x << std::endl;

            switch((*it)->getDrawType()) {
                case IsDrawable::DrawType::animation:
                    _animations.at(id).update(time);
                    _sprites.at(id).setPosition(position);
                    _renderWindow->draw(_sprites.at(id));
                    break;
            }
        }
    }

    return true;
}

bool GameView::setUp() {
    sf::Texture bastardTexture;
    
    if( bastardTexture.loadFromFile("assets/bastard.png")) {
        std::cout << "loaded" << std::endl;
    }
   
    _textures.push_back(bastardTexture);

    sf::Sprite bastardSprite;
    bastardSprite.setTexture(_textures.back());
    _sprites.push_back(bastardSprite);

    Animation bastardAnimation(&_sprites.back(), .1);
    for(int i=0; i<4; ++i)
        bastardAnimation.addFrame(96*i, 0, 96, 160);
    _animations.push_back(bastardAnimation);

    return true;
}

bool GameView::tearDown() {
    return true;
}