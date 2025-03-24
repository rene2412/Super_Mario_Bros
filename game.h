#pragma once
#include "mario.h"
#include "enemies.h"
#include "load_map.h"

class Game {

public:
    Game();
    void Collisions(Mario &mario, Goomba &goomba, MapAssets &map);
};

