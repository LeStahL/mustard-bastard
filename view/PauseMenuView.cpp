#include "PauseMenuView.hpp"

PauseMenuView::PauseMenuView(sf::RenderWindow *renderWindow, PauseMenuState* pauseMenuState) :
    renderWindow(renderWindow),
    pauseMenuState(pauseMenuState)
{

}

bool PauseMenuView::draw(double time) {
    renderWindow->draw(pauseMenuSprite);

    highlightsRect.left = pauseMenuState->selectedIndex() == 0 ? 0 : 960;
    renderWindow->draw(pauseMenuHighlightsSprite);
    pauseMenuHighlightsSprite.setTextureRect(highlightsRect);

    return true;
}

bool PauseMenuView::setUp() {
    bool res = true;

    res &= pauseMenuTexture.loadFromFile("assets/pausescreen.png");
    res &= pauseMenuHighlightsTexture.loadFromFile("assets/pausescreen_highlights.png");

    pauseMenuSprite.setTexture(pauseMenuTexture);
    pauseMenuHighlightsSprite.setTexture(pauseMenuHighlightsTexture);

    highlightsRect.width  = 960;
    highlightsRect.height = 540;

    return res;
}

bool PauseMenuView::tearDown() {
    return true;
}
