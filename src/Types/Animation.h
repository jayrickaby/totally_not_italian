//
// Created by jay on 05/05/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_ANIMATION_H
#define TOTALLY_NOT_ITALIAN_ANIMATION_H
#include <vector>

#include "SFML/Graphics/Rect.hpp"

#endif //TOTALLY_NOT_ITALIAN_ANIMATION_H

struct Animation {
    std::vector<sf::IntRect> frames;
    float frameDuration = 1;
    float frameTimer = 0;
    signed int currentFrame = 0;
};