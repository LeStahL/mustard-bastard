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
        int getBackgroundBaseLine(WorldPosition position);
};

#endif
