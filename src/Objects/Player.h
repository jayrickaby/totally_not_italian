//
// Created by jay on 30/04/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_PLAYER_H
#define TOTALLY_NOT_ITALIAN_PLAYER_H


#include "Entity.h"
#include "SFML/Audio.hpp"

struct Animation;

class Player : public Entity {
public:
    Player();

    void update(float deltaTime) override;

private:
    // Physics
    const float SPEED;
    const float JUMP_STRENGTH;

    // Logic
    bool tryToJump;

    void handleInput();

    // Sound
    sf::SoundBuffer buf_jump;
    sf::Sound snd_jump;
protected:
    void preMoveY(float deltaTime) override;
};


#endif //TOTALLY_NOT_ITALIAN_PLAYER_H
