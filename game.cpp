#include "game.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Game::Game() {
SuperMarioBros = LoadSound("sounds/SuperMarioBros.wav");
PlaySound(SuperMarioBros);
}
  
void Game::Collisions(Mario &mario, std::vector<std::shared_ptr<Goomba>>& goombas, MapAssets &map) {
   int i = 0; 
   for (auto g : goombas) {
	   if (g->GetIsAlive()) {
		HandleGoombaCollision(mario, *g);
		if (i == 1 and g->GetHitBox().x <= map.GetTube2().x + map.GetTube().width) {
			float newX = map.GetTube2().x + map.GetTube().width;
			g->SetPosition({newX, g->GetHitBox().y});
			}
		if ((i == 2 or i == 3) and g->GetHitBox().x <= map.GetTube3().x + map.GetTube3().width) {
			float newX = map.GetTube3().x + map.GetTube3().width;
			g->SetPosition({newX, g->GetHitBox().y});
			}
		 }
	   i++;
	}
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
    if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube4())) {
        HandleTubeCollision(mario, map.GetTube4(), 4);
        onAnyAsset = true;
    }
if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube5())) {
        HandleTubeCollision(mario, map.GetTube5(), 3);
        onAnyAsset = true;
    }

 // GoombaTubeCollision(goombas, map.GetTube2());
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
  GoombaIsFallingDown(goombas, map);
}

void Game::HandleKoopaCollision(Mario &mario, Koopa& koopa) {
	if (CheckCollisionRecs(mario.GetHitBox(), koopa.GetHitBox())) {
		mario.SetIsAlive(false);	
	}
}

void Game::GoombaIsFallingDown(std::vector<std::shared_ptr<Goomba>> &goombas, MapAssets &map) {
	goombas[4]->SetIsOnBricks(false);
	goombas[4]->SetIsOnQuestion(false);
	goombas[5]->SetIsOnBricks(false);
	goombas[5]->SetIsOnQuestion(false);
	for (auto &brick : map.GetHardBrick()) {
		if (CheckCollisionRecs(goombas[4]->GetHitBox(), brick)) {
			goombas[4]->SetIsOnBricks(true);
			break;
		}
	}
	for (auto &brick : map.GetHardBrick()) {
		if (CheckCollisionRecs(goombas[5]->GetHitBox(), brick)) {
			goombas[5]->SetIsOnBricks(true);
			break;
		}
	}
	if (CheckCollisionRecs(goombas[4]->GetHitBox(), map.GetQuestionBrick()[4])) {
		goombas[4]->SetIsOnQuestion(true);
	}
	if (CheckCollisionRecs(goombas[5]->GetHitBox(), map.GetQuestionBrick()[4])) {
		goombas[5]->SetIsOnQuestion(true);
	}
	if  (goombas[4]->GetIsOnBricks() == false and goombas[4]->GetIsOnQuestion() == false) {
			goombas[4]->SetIsFalling(true);	
	}
	if  (goombas[5]->GetIsOnBricks() == false and goombas[5]->GetIsOnQuestion() == false) {
			goombas[5]->SetIsFalling(true);	
	}
	if (goombas[4]->GetIsFalling() and goombas[4]->GetIsOnBricks() == false and goombas[4]->GetPosition().y <= 446) { 
		Vector2 pos = goombas[4]->GetPosition();
		pos.y += 4;
		goombas[4]->SetPosition(pos);
	}
	if (goombas[5]->GetIsFalling() and goombas[5]->GetIsOnBricks() == false and goombas[5]->GetPosition().y <= 446) { 
		Vector2 pos = goombas[5]->GetPosition();
		pos.y += 4;
		goombas[5]->SetPosition(pos);
	}
	if (goombas[4]->GetPosition().x <= 3460 and goombas[4]->GetPosition().y  >= 446) {
		Vector2 pos = goombas[4]->GetPosition();
		pos.y += 4;
		goombas[4]->SetPosition(pos);
	}
	if (goombas[5]->GetPosition().x <= 3460 and goombas[5]->GetPosition().y  >= 446) {
		Vector2 pos = goombas[5]->GetPosition();
		pos.y += 4;
		goombas[5]->SetPosition(pos);
	}
}

void Game::GoombaTubeCollision(std::vector<std::shared_ptr<Goomba>> &goombas, Rectangle rectangle) {
	for (auto &g : goombas) {
		if (CheckCollisionRecs(g->GetHitBox(), rectangle)) {
		}
	}
}

void Game::HandleMushroomCollision(Mario &mario, MapAssets &map) {
	if (CheckCollisionRecs(mario.GetHitBox(), map.GetMushroom()) and mario.GetIsBig() == false) {
		mario.SetShowMushroom(false);	
		mario.SetTimer(GetTime());
	        mario.SetIsBig(true); 
		mario.SetIsPoweredUp(false); // Reset animation state
	} 
}

void Game::DisableCoinAnimation(Mario &mario, MapAssets &map) {
	if (mario.GetJumpCycle()) {
	//std::cout << "HOLA: " << map.GetHasQuestionPassed().size() << "\n";
		for (size_t i = 0; i < map.GetHasQuestionPassed().size(); i++) { 
			//if we already hit a coin dont recalcuate since mario cant hit the same coin twice
			// if (i == 1) continue;
			 map.SetHaveCoinsPassed(map.GetHasQuestionPassed()[i], i);
		//	 std::cout << "i: " << map.GetHaveCoinsPassed()[i] << std::endl;
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
	std::vector<bool> allStairs(map.GetStairs().size(), false);
	// for every stair check if mario is colliding with it
	int i = 0;
	for (auto &stair : map.GetStairs()) {
	    bool stairs = CheckCollisionRecs(mario.GetHitBox(), stair);
		allStairs.push_back(stairs);
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
		i++;
	}
	if (mario.GetIsOnStairs() and std::all_of(allStairs.begin(), allStairs.end(), [](bool x) { return x == 0; })) {
	    	mario.SetIsOnStairs(false);
     		mario.SetIsOnAsset(true);
			FallFromAsset(mario);
			
	} 
}

void Game::HandleQuestionCollision(Mario &mario, MapAssets &map) {
	int i = 0;
	for(auto &brick : map.GetQuestionBrick()) {
		//std::cout << "B: " << map.GetQuestionBrick().size() << std::endl;
		if (i != 1 and CheckCollisionRecs(mario.GetHitBox(), brick)) {
			std::cout << "question hit\n";
			mario.SetIsOnAsset(true);
			FallFromAsset(mario);
			map.SetRemoveQuestionBricks(false, i);
			if (i == 0) {
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 0); 
			map.SetCoinTimer(0.0f, 0);
			break;
			}
			if (i == 2) {
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 2); 
			map.SetCoinTimer(0.0f, 2);
			break;
			}
			if (i == 3) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 1); 
			map.SetCoinTimer(0.0f, 1);
			break;
			}
			if (i == 4) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 3); 
			map.SetCoinTimer(0.0f, 3);
			break;
			}
			if (i == 6) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 4); 
			map.SetCoinTimer(0.0f, 4);
			break;
			}
			if (i == 7) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 5); 
			map.SetCoinTimer(0.0f, 5);
			break;
			}	
			if (i == 8) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 6); 
			map.SetCoinTimer(0.0f, 6);
			break;
			}
			if (i == 9) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 7); 
			map.SetCoinTimer(0.0f, 7);
			break;
			}
			if (i == 10) {	
			map.SetHasQuestionPassed(true, i);
			map.SetQuestionIndex(i);
			map.SetShowCoin(true, 8); 
			map.SetCoinTimer(0.0f, 8);
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
