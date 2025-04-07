#include "game.h"
#include <iostream>

Game::Game() {}
    

void Game::Collisions(Mario &mario, Goomba &goomba, MapAssets &map) { 
	if (CheckCollisionRecs(mario.GetHitBox(), goomba.GetHitBox())) {
		std::cout << "Collision\n";
	}
	Rectangle marioHitbox = mario.GetHitBox();
    	Rectangle tubeHitbox = map.GetTube();
	//dont allow mario to walk through the tube on its left
	std::cout << "Jumping: " << mario.GetIsJumping() << std::endl;
	std::cout << "Ground: " << mario.GetIsOnGround() << std::endl;
	bool collision = CheckCollisionRecs(marioHitbox, tubeHitbox);
	std::cout <<  "Collision Status: " << collision << std::endl;
	std::cout << "Tube: " << map.GetTube().x << ", " << map.GetTube().y << std::endl;
	std::cout << "Mario: " << mario.GetHitBox().x << ", " << mario.GetHitBox().y << std::endl;
	// Debugging draw function
	//DrawRectangleLines(marioHitbox.x, marioHitbox.y, marioHitbox.width, marioHitbox.height, RED);
	//DrawRectangleLines(tubeHitbox.x, tubeHitbox.y, tubeHitbox.width, tubeHitbox.height, BLUE);

	if (marioHitbox.x + 29  >= tubeHitbox.x and  
		mario.GetForwardVector().x == 1 and mario.GetIsJumping() == false
	       	and mario.GetIsOnGround() and mario.GetPosition().x <= 925) {
		std::cout << " Run L" << std::endl;
		mario.SetPosition({mario.GetPosition().x - 5, mario.GetPosition().y});
	}
	
	//Dont allow mario to walk through the tube on its right
	if (marioHitbox.x - 74 <= tubeHitbox.x and mario.GetPosition().x >= 926 
	  and mario.GetForwardVector().x == -1 and mario.GetIsJumping() == false and mario.GetIsOnGround()) {
		std::cout <<" Run R" << std::endl;
		mario.SetPosition({mario.GetPosition().x + 5, mario.GetPosition().y});
	}
	// Check if Mario is on top of the tube (vertical collision, only if jumping or falling)
	// Vertical Collision (Checking if Mario is on top of the tube)
	// If Mario is falling and his feet are about to land on the tube
	if (marioHitbox.y >= tubeHitbox.y + 10 and  // Within landing range
    		mario.GetIsFalling() and  // Only check if Mario is falling
                CheckCollisionRecs(marioHitbox, tubeHitbox)) {  // Collision happens
		mario.SetIsOnAsset(true);
			mario.SetIsOnGround(false);
    			 mario.SetIsJumping(false);
    			 mario.SetOverrideJumpAnimation(false); 
			 // Snap Mario to the top of the tube
    			 mario.SetPosition({mario.GetPosition().x,  marioHitbox.y});
   			 std::cout << "Mario landed on the tube!\n";
	}
        
   	Vector2 pos = mario.GetPosition();
	if (collision == false and mario.GetIsOnAsset() == true) {
		mario.SetIsFalling(true);
		mario.SetIsJumping(true);
		pos.y += mario.GetGravity() * 0.55;
		mario.SetPosition(pos);
		// Stop jumping when Mario reaches the ground (adjust Y value as needed)
   		if (mario.GetPosition().y >= 415) {
        		mario.SetPosition({mario.GetPosition().x, 415});
			mario.SetIsFalling(false);
			mario.SetIsJumping(false); // Allow jumping again
			mario.SetIsOnAsset(false);
			mario.SetIsOnGround(true);
   		}   
	}

//	std::cout << "MarioHitBox: " << marioHitbox.x << ", " << marioHitbox.y << std::endl; 
//	std::cout << "TubeHitBox: " << tubeHitbox.x << ", " << tubeHitbox.y << std::endl; 

}
			    

