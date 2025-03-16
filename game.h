#pragma once
#include "mario.h"
#include "enemies.h"

class Game {

public:
    Game();
    void Collisions(Mario &mario, Goomba &goomba);
};

