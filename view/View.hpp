#pragma once

class View
{
    public:
    View() = default;

    virtual bool draw(double time) = 0;
    virtual bool setUp() = 0;
    virtual bool tearDown() = 0;

    // virtual void processMouseEvent(int x, int y) = 0;
};
