#ifndef VIEW_STUFF_H
#define VIEW_STUFF_H

#include <SFML/Graphics.hpp>

#include <WorldPosition.h>

class ViewStuff
{
    private:
        sf::RenderWindow *window;

    public:
        ViewStuff(sf::RenderWindow *window);
        void DrawBackground();
        void customDraw(sf::RenderWindow *window, double time);
        int getBackgroundBaseLine(WorldPosition position);
};

#endif
