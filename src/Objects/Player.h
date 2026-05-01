//
// Created by jay on 30/04/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_PLAYER_H
#define TOTALLY_NOT_ITALIAN_PLAYER_H
#include "SFML/Graphics.hpp"
#include <map>

struct Animation {
    std::vector<sf::IntRect> frames;
    float frameDuration = 1;
    float frameTimer = 0;
    signed int currentFrame = 0;
};

class Player {
public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderTarget& target);

private:
    // Appearance
    sf::Texture texture;
    sf::Sprite sprite;

    std::map<std::string, Animation> animations;
    std::string currentAnimation;
    std::string defaultAnimation;

    void playAnimation(const std::string& anim);
    void animate(float deltaTime);

    // Physics
    const float SPEED;
    int direction;
    sf::FloatRect boundingBox;
};


#endif //TOTALLY_NOT_ITALIAN_PLAYER_H
