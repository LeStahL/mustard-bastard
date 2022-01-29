#ifndef VIEW_STUFF_H
#define VIEW_STUFF_H

#include <SFML/Graphics.hpp>

class ViewStuff
{
    private:
        sf::RenderWindow *window;

    public:
        ViewStuff(sf::RenderWindow *window);
        void DrawBackground();
};

#endif
