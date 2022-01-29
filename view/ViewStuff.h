#ifndef VIEW_STUFF_H
#define VIEW_STUFF_H

#include <SFML/Graphics.hpp>

#include <IsDrawable.hpp>

class ViewStuff : public IsDrawable
{
    private:
        sf::RenderWindow *window;

    public:
        ViewStuff(sf::RenderWindow *window);
        void DrawBackground();
        void customDraw(double time) override;
};

#endif
