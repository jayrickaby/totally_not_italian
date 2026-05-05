//
// Created by jay on 04/05/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_GOOMBA_H
#define TOTALLY_NOT_ITALIAN_GOOMBA_H

#include "Entity.h"

class Goomba : public Entity {
public:
    Goomba();

protected:
    void preMoveX(float deltaTime) override;
};


#endif //TOTALLY_NOT_ITALIAN_GOOMBA_H
