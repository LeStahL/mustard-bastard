#ifndef VIEW_STUFF_H
#define VIEW_STUFF_H

#include <utility>
#include <SFML/Graphics.hpp>
#include <WorldCoordinates.h>

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

#endif
