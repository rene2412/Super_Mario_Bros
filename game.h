#pragma once
#include "mario.h"
#include "enemies.h"
#include "load_map.h"

class Game {
    private:
    Sound coin_audio;
public:
    Game();
    void Collisions(Mario &mario, std::vector<std::shared_ptr<Goomba>>& goombas, MapAssets &map);
    void HandleGoombaCollision(Mario &mario, Goomba& goomba);
    void HandleKoopaCollision(Mario &mario, Koopa& koopa);
    void HandleTubeCollision(Mario &mario, Rectangle tubeHitbox, float padding); 
    void FallFromAsset(Mario &mario);
    void HandleBrickCollision(Mario &mario, MapAssets &map);
    void HandleQuestionCollision(Mario &mario, MapAssets &map);
    void HandleStairCollision(Mario &mario, MapAssets &map);
    void OnTopOfBricks(Mario &mario, MapAssets &map);
    void DisableCoinAnimation(Mario &mario, MapAssets &map); 
    void HandleMushroomCollision(Mario &mario, MapAssets &map);
    void GoombaTubeCollision(std::vector<std::shared_ptr<Goomba>>& goombas, Rectangle rectangle);
    void GoombaIsFallingDown(std::vector<std::shared_ptr<Goomba>> &goombas, MapAssets &map);
};



