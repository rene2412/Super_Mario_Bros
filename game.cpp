#include "game.h"
#include <iostream>

Game::Game() {}
  

void Game::Collisions(Mario &mario, Goomba &goomba, MapAssets &map) {
    HandleGoombaCollision(mario, goomba);
    
    
// Handle each tube with its own landing height offset
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube())) {
        HandleTubeCollision(mario, map.GetTube(), 3);
        std::cout << "Collision with Tube1\n";
    }

    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube2())) {
        HandleTubeCollision(mario, map.GetTube2(), 6);
        std::cout << "Collision with Tube2\n";
    }
/*
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube3())) {
        HandleTubeCollision(mario, map.GetTube3(), 4);
    }

    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube4())) {
        HandleTubeCollision(mario, map.GetTube4(), 7);
    }
    */
}

void Game::HandleGoombaCollision(Mario &mario, Goomba &goomba) {
    if (CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) {
        std::cout << "Collision with Goomba\n";
    
    }
}

void Game::HandleTubeCollision(Mario &mario, Rectangle tubeHitbox, float padding) {
    Rectangle marioHitbox = mario.GetHitBox();

    //DrawRectangleLines(tubeHitbox.x, tubeHitbox.y, tubeHitbox.width, tubeHitbox.height, BLUE);

    if (CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetForwardVector().x == 1 &&
        !mario.GetIsJumping() && mario.GetIsOnGround()) {
        std::cout << "Run L (Tube1)\n";
        mario.SetPosition({mario.GetPosition().x - 5, mario.GetPosition().y});
    }

    if (CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetForwardVector().x == -1 &&
        !mario.GetIsJumping() && mario.GetIsOnGround()) {
        std::cout << "Run R (Tube1)\n";
        mario.SetPosition({mario.GetPosition().x + 5, mario.GetPosition().y});
    }

    if ((marioHitbox.y - 6 >= tubeHitbox.y) && mario.GetIsFalling() &&
        CheckCollisionRecs(marioHitbox, tubeHitbox)) {
        mario.SetIsOnAsset(true);
        mario.SetIsOnGround(false);
        mario.SetIsJumping(false);
        mario.SetOverrideJumpAnimation(false);
        mario.SetPosition({mario.GetPosition().x, tubeHitbox.y + padding});
        std::cout << "Mario landed on tube 1\n";
    }

    if (!CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetIsOnAsset()) {
        std::cout << "1!\n";
        mario.SetIsFalling(true);
        mario.SetIsJumping(false);
        mario.SetIsOnAsset(false);
        mario.SetIsOnGround(true);
    }
}


