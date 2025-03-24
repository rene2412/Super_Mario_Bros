#include "game.h"

Game::Game() {}
    
void Game::Collisions(Mario &mario, Goomba &goomba, MapAssets &map) { 
   	if (CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) {
		std::cout << "Collision\n";
	}
	//problem for tmmrw how to allow to jump over it 
   	if (CheckCollisionRecs(mario.GetHitBox(), map.GetTube())) {
		mario.SetPosition({map.GetTube().x - mario.GetHitBox().width, mario.GetPosition().y}); 
	}
}
			    

