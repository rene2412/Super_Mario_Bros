#include "game.h"
#include <iostream>

Game::Game() {}
  
void Game::Collisions(Mario &mario, Goomba &goomba, MapAssets &map) {
    HandleGoombaCollision(mario, goomba);
    
    // Store current state before checking collisions
    bool wasOnAsset = mario.GetIsOnAsset();
    bool onAnyAsset = false;
    
    // Check collision with tube 1
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube())) {
        HandleTubeCollision(mario, map.GetTube(), 3);
        onAnyAsset = true;
    }
    
    // Check collision with tube 2
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube2())) {
        HandleTubeCollision(mario, map.GetTube2(), 3);
        onAnyAsset = true;
    }
    
    //these dont exist yet
    /*
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube3())) {
        HandleTubeCollision(mario, map.GetTube3(), 4);
        onAnyAsset = true;
    }

    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube4())) {
        HandleTubeCollision(mario, map.GetTube4(), 7);
        onAnyAsset = true;
    }
    */

    // If Mario was on an asset but now isn't on any asset, handle falling
    if (wasOnAsset && !onAnyAsset) {
        FallFromAsset(mario);
    }

  HandleBrickCollision(mario, map);	
  HandleQuestionCollision(mario, map);

}


void Game::HandleQuestionCollision(Mario &mario, MapAssets &map) {
	for(auto &brick : map.GetQuestionBrick()) {
		if (CheckCollisionRecs(mario.GetHitBox(), brick)) {
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
		}
	}
}

void Game::HandleBrickCollision(Mario &mario, MapAssets &map) {
	for (auto &brick : map.GetHardBrick()) {
		if (CheckCollisionRecs(mario.GetHitBox(), brick)) { 
			std::cout << "Brick!\n";
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
			}
        	  }
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
	 mario.GetIsOnGround()) {
    
        std::cout << "Run L (Tube)\n";
        mario.SetPosition({mario.GetPosition().x - 5, mario.GetPosition().y});
    }

    if (CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetForwardVector().x == -1 &&
         mario.GetIsOnGround()) {
        std::cout << "Run R (Tube)\n";
        mario.SetPosition({mario.GetPosition().x + 5, mario.GetPosition().y});
    }

    if ((marioHitbox.y - 3 >= tubeHitbox.y) && mario.GetIsFalling() &&
        CheckCollisionRecs(marioHitbox, tubeHitbox)) {
        mario.SetIsOnAsset(true);
        mario.SetIsOnGround(false);
        mario.SetIsJumping(false);
        mario.SetOverrideJumpAnimation(false);
        std::cout << "Mario landed on tube\n";
        mario.SetPosition({mario.GetPosition().x, tubeHitbox.y});
   }
}

void Game::FallFromAsset(Mario &mario) {
    Vector2 pos = mario.GetPosition();
    if (mario.GetIsOnAsset()) {
        std::cout << "1!\n";
	pos.y += mario.GetGravity() * 0.35f;
        mario.SetIsFalling(true);
        mario.SetIsJumping(true);
	mario.SetPosition(pos);
       if (mario.GetPosition().y >= 415) {	
       	        mario.SetPosition({mario.GetPosition().x, 415});	
	        mario.SetIsOnAsset(false);
        	mario.SetIsOnGround(true);
    		mario.SetIsFalling(false);
		mario.SetIsJumping(false); 
        	mario.SetOverrideJumpAnimation(false);
       		}	
	}
} 
