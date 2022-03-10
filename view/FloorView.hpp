#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include <WorldCoordinates.hpp>

class FloorView
{
    private:
        sf::RenderWindow *window;

    public:
        FloorView(sf::RenderWindow *window);
        void DrawBackground();
        void customDraw(sf::RenderWindow *window, double time);
        int getBackgroundBaseLine(WorldCoordinates coords);
        std::pair<int, int> getBothBaseLines(WorldCoordinates coords);
};
