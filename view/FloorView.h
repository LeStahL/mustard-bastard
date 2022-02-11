#ifndef VIEW_STUFF_H
#define VIEW_STUFF_H

#include <utility>
#include <SFML/Graphics.hpp>
#include <WorldPosition.h>

class FloorView
{
    private:
        sf::RenderWindow *window;

    public:
        FloorView(sf::RenderWindow *window);
        void DrawBackground();
        void customDraw(sf::RenderWindow *window, double time);
        int getBackgroundBaseLine(WorldPosition position);
        std::pair<int, int> getBothBaseLines(WorldPosition position);
};

#endif
