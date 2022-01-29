#pragma once

class InputController {
public:
    InputController() = default;
    virtual void pullEvents() = 0;
};
