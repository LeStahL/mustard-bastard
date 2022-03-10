#include <Medikit.hpp>
#include <ViewConst.h> // coupling

float Medikit::width() {
    return static_cast<float>(MEDIKIT_PIXEL_WIDTH);
}

bool Medikit::canCollide() {
    return !spawning;
}
