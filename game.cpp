#include "game.h"
#include <iostream>
#include <cmath>

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
    
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube3())) {
        HandleTubeCollision(mario, map.GetTube3(), 4);
        onAnyAsset = true;
    }
/*
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
  HandleStairCollision(mario, map);
  HandleMushroomCollision(mario, map);
  OnTopOfBricks(mario, map);
  DisableCoinAnimation(mario, map);
  //std::cout << mario.GetPosition().x << ", " << mario.GetPosition().y << std::endl;;	
  //std::cout << mario.GetIsOnBricks() << std::endl; 
  //std::cout << "Jumping: " << mario.GetIsJumping() << std::endl;
 // std::cout << "Falling: " << mario.GetIsFalling() << std::endl;

}


void Game::HandleMushroomCollision(Mario &mario, MapAssets &map) {
	if (CheckCollisionRecs(mario.GetHitBox(), map.GetMushroom()) and mario.GetIsBig() == false) {
		std::cout << "big mario time\n";
		mario.SetShowMushroom(false);	
		mario.SetTimer(GetTime());
	        mario.SetIsBig(true); 
		mario.SetIsPoweredUp(false); // Reset animation state
	} 
}



void Game::DisableCoinAnimation(Mario &mario, MapAssets &map) {
	if (mario.GetJumpCycle()) {
		for (size_t i = 0; i < map.GetHasQuestionPassed().size(); i++) { 
			//if we already hit a coin dont recalcuate since mario cant hit the same coin twice
			 if (i == 1) continue;
			 map.SetHaveCoinsPassed(map.GetHasQuestionPassed()[i], i);
			// std::cout << "i: " << map.GetHaveCoinsPassed()[i] << std::endl;
		}
	}
}

void Game::OnTopOfBricks(Mario &mario, MapAssets &map) {
	for (auto &brick : map.GetHardBrick()) {
       		if ((mario.GetHitBox().y <= brick.y) and mario.GetIsFalling() and
        	     CheckCollisionRecs(mario.GetHitBox(), brick)) {
		         mario.SetIsOnBricks(true);
		}
		if (mario.GetPosition().x < map.GetHardBrick()[0].x - 35 or mario.GetPosition().x > map.GetHardBrick()[2].x + 25) {
		        mario.SetIsOnBricks(false);
		} 
	}
	for (auto &brick : map.GetQuestionBrick()) {
		if ((mario.GetHitBox().y <= brick.y)  and mario.GetIsFalling() and
        		 CheckCollisionRecs(mario.GetHitBox(), brick)) {
			 mario.SetIsOnBricks(true);
		}
	}
	if (mario.GetIsOnBricks()) { 
	     if (!IsKeyDown(KEY_SPACE)) { 
		  mario.SetIsOnAsset(true);
                  mario.SetIsOnGround(false);
                  mario.SetIsJumping(false);
                  mario.SetIsFalling(false);
        	  mario.SetOverrideJumpAnimation(false);
		  float y = 250 - mario.GetHitBox().height; 
		  mario.SetPosition({mario.GetPosition().x, y}); // map.GetHardBrick().y - map.GetHardBrick().height});
		}
	}
}


void Game::HandleStairCollision(Mario &mario, MapAssets &map) {
	// for every stair check if mario is colliding with it
	for (auto &stair : map.GetStairs()) {
		if (CheckCollisionRecs(mario.GetHitBox(), stair) and mario.GetForwardVector().x == 1 and IsKeyDown(KEY_RIGHT)) {
			// calculate the slope angle mario needs to travel at for upstairs and then downstairs
			Vector2 anglePos = mario.GetPosition();
			float rads = 140.0f * (PI / 180.0f);
		       	anglePos.x += 1.85 * cos(rads);
		       	anglePos.y -= 1.85 * sin(rads);
			mario.SetPosition({anglePos.x, anglePos.y});
			mario.SetIsOnStairs(true);
		}	
		if (mario.GetIsOnStairs() and mario.GetForwardVector().x == -1 and IsKeyDown(KEY_LEFT)) {
			Vector2 anglePos = mario.GetPosition();
			float rads = 80.0f * (PI / 180.0f);
		       	anglePos.x -= 0.3 * cos(rads);
		       	anglePos.y += 0.4 * sin(rads);
			mario.SetPosition({anglePos.x, anglePos.y});
		}
		if (mario.GetIsOnStairs() and mario.GetPosition().y >= 415) {
			mario.SetIsOnStairs(false);
		}
	}
}

void Game::HandleQuestionCollision(Mario &mario, MapAssets &map) {
	int i = 0;
	for(auto &brick : map.GetQuestionBrick()) {
		if (i != 1 and CheckCollisionRecs(mario.GetHitBox(), brick)) {
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
			map.SetRemoveQuestionBricks(false, i);
			map.SetShowCoin(true, i); 
			map.SetCoinTimer(0.0f, i);
			if (i == 0) {
			map.SetHasQuestionPassed(true, 0);
			map.SetQuestionIndex(i);
			break;
			}
			if (i == 2) {	
			map.SetHasQuestionPassed(true, 2);
			map.SetQuestionIndex(i);
			}
			if (i == 3) {	
			map.SetHasQuestionPassed(true, 3);
			map.SetQuestionIndex(i);
			break;
			}
		}
		if (i == 1 and CheckCollisionRecs(mario.GetHitBox(), brick)) {
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
			map.SetMushroomCollided(true);
			map.SetQuestionIndex(1);
			map.SetRemoveQuestionBricks(false, 1);
			map.SetHasQuestionPassed(true, 1);
		}
		i++;
	}
}

void Game::HandleBrickCollision(Mario &mario, MapAssets &map) {
	for (auto &brick : map.GetHardBrick()) {
		if (CheckCollisionRecs(mario.GetHitBox(), brick)) { 
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
		   }
          }
}


void Game::HandleGoombaCollision(Mario &mario, Goomba &goomba) {
    if (mario.GetIsFalling() and goomba.GetIsDamageValid() and mario.GetHitBox().y <= goomba.GetHitBox().y
	and CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) {
   		//std::cout << "Goomba ded\n";
	        goomba.SetIsAlive(false);
		goomba.SetIsDamageValid(false);
		return;	
   }
   if (CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) { 	       	
      if (mario.GetIsAlive() and goomba.GetIsDamageValid()) {
        //std::cout << "Mario ded\n"; 
	mario.SetIsAlive(false);
	mario.SetTimer(GetTime());
	goomba.SetIsDamageValid(false);
	}
	return;
   }
}

void Game::HandleTubeCollision(Mario &mario, Rectangle tubeHitbox, float padding) {
    Rectangle marioHitbox = mario.GetHitBox();

    //DrawRectangleLines(tubeHitbox.x, tubeHitbox.y, tubeHitbox.width, tubeHitbox.height, BLUE);
    if (CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetForwardVector().x == 1 && 
	 mario.GetIsOnGround()) {
    
        mario.SetPosition({mario.GetPosition().x - 5, mario.GetPosition().y});
    }

    if (CheckCollisionRecs(marioHitbox, tubeHitbox) && mario.GetForwardVector().x == -1 &&
         mario.GetIsOnGround()) {
        mario.SetPosition({mario.GetPosition().x + 5, mario.GetPosition().y});
    }

    if ((marioHitbox.y - 3 >= tubeHitbox.y) && mario.GetIsFalling() &&
        CheckCollisionRecs(marioHitbox, tubeHitbox)) {
        mario.SetIsOnAsset(true);
        mario.SetIsOnGround(false);
        mario.SetIsJumping(false);
        mario.SetIsFalling(false);
	mario.SetOverrideJumpAnimation(false);
        mario.SetPosition({mario.GetPosition().x, tubeHitbox.y});
   }
}

void Game::FallFromAsset(Mario &mario) {
    Vector2 pos = mario.GetPosition();
    if (mario.GetIsOnAsset()) {
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
