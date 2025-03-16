#include "game.h"

Game::Game() {}
    
void Game::Collisions(Mario &mario, Goomba &goomba) { 
   	if (CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) {
		std::cout << "Collision\n";
	}
    }
			    
   

