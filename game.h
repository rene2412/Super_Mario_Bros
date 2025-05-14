#pragma once
#include "mario.h"
#include "enemies.h"
#include "load_map.h"

class Game {

public:
    Game();
    void Collisions(Mario &mario, Goomba &goomba, MapAssets &map);
    void HandleGoombaCollision(Mario &mario, Goomba &goomba);
    void HandleTubeCollision(Mario &mario, Rectangle tubeHitbox, float padding); 
    void FallFromAsset(Mario &mario);
    void HandleBrickCollision(Mario &mario, MapAssets &map);
    void HandleQuestionCollision(Mario &mario, MapAssets &map);
    void HandleStairCollision(Mario &mario, MapAssets &map);
};

