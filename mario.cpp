#include "mario.h"
#include "enemies.h"
#include "load_map.h"
#include <cmath>

Mario::Mario() {
    // Load Mario's sprite
    img = LoadImage("images/mario64.png");
    ImageResize(&img, 50, 66);
    sprite = LoadTextureFromImage(img);
    UnloadImage(img);

    Image left_idle = LoadImage("images/mario64left.png");
    ImageResize(&left_idle, 50, 66); // Flip it before creating texture
    left_idle_sprite = LoadTextureFromImage(left_idle);
    UnloadImage(left_idle);

    jump_img = LoadImage("images/mariojump.png");
    ImageResize(&jump_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    jump_sprite = LoadTextureFromImage(jump_img);
    UnloadImage(jump_img);

    jump_img_left = LoadImage("images/mariojumpleft.png");
    ImageResize(&jump_img_left, 50, 66); // 50 width and 66 height are just the values from the base animation
    jump_sprite_left = LoadTextureFromImage(jump_img_left);
    UnloadImage(jump_img_left);


    right_img = LoadImage("images/marioright.PNG");
    ImageResize(&right_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    right_sprite = LoadTextureFromImage(right_img);
    UnloadImage(right_img);
   
    left_img = LoadImage("images/marioleft.PNG");
    ImageResize(&left_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    left_sprite = LoadTextureFromImage(left_img);
    UnloadImage(left_img);
	
    marioPowerUp_img = LoadImage("images/mario64.png");
    ImageResize(&marioPowerUp_img, 60, 70); // 50 width and 66 height are just the values from the base animation
    marioPowerUp_sprite = LoadTextureFromImage(marioPowerUp_img);
    UnloadImage(marioPowerUp_img);

    bigMario_img = LoadImage("images/BigMario.png");
    ImageResize(&bigMario_img, 90, 100); 
    bigMario_sprite = LoadTextureFromImage(bigMario_img);
    UnloadImage(bigMario_img);
    
    bigMarioLeft_img = LoadImage("images/BigMarioLeft.png");
    ImageResize(&bigMarioLeft_img, 90, 100); 
    bigMarioLeft_sprite = LoadTextureFromImage(bigMarioLeft_img);
    UnloadImage(bigMarioLeft_img);

    bigMarioWalkRight_img = LoadImage("images/bigMarioWalkRight.png");
    ImageResize(&bigMarioWalkRight_img, 70, 100); // 50 width and 66 height are just the values from the base animation
    bigMarioWalkRight_sprite = LoadTextureFromImage(bigMarioWalkRight_img);
    UnloadImage(bigMarioWalkRight_img);
    
    bigMarioWalkLeft_img = LoadImage("images/bigMarioWalkLeft.png");
    ImageResize(&bigMarioWalkLeft_img, 70, 100); // 50 width and 66 height are just the values from the base animation
    bigMarioWalkLeft_sprite = LoadTextureFromImage(bigMarioWalkLeft_img);
    UnloadImage(bigMarioWalkLeft_img);

    bigMarioJumpRight_img = LoadImage("images/bigMarioJumpRight.png");
    ImageResize(&bigMarioJumpRight_img, 70, 100); // 50 width and 66 height are just the values from the base animation
    bigMarioJumpRight_sprite = LoadTextureFromImage(bigMarioJumpRight_img);
    UnloadImage(bigMarioJumpRight_img);

    bigMarioJumpLeft_img = LoadImage("images/bigMarioJumpLeft.png");
    ImageResize(&bigMarioJumpLeft_img, 70, 100); // 50 width and 66 height are just the values from the base animation
    bigMarioJumpLeft_sprite = LoadTextureFromImage(bigMarioJumpLeft_img);
    UnloadImage(bigMarioJumpLeft_img);

    marioDeath_img = LoadImage("images/marioDeath.png");
    ImageResize(&marioDeath_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    marioDeath_sprite = LoadTextureFromImage(marioDeath_img);
    UnloadImage(marioDeath_img);

    powerUp = LoadSound("sounds/powerUp.wav");

    Forward = { 1, 0 };
    Position.x = 50;
    Position.y = 415;
    speed = 5.0f;
    jump = 10.0f;
    IsAlive = true;
    IsJumping = false;
    IsFalling = false;
    IsOnGround = true;
    IsOnAsset = false;
    IsOnBricks = false;
    IsBig = false;
    playedPoweredUp = false;
    usingHead = false;
    jumpCycle = false;
    hitbox = { Position.x, Position.y, 50, 66 };
    big_hitbox = { Position.x, Position.y, 110, 120 };
    override_jump_animation = false;
    override_left_animation = false;
    override_right_animation = false;
    // Camera setup
    camera.target = Position;
    camera.offset = { 400, 480 }; // Keep Mario centered
    camera.rotation = 0.0f;
    camera.zoom = 0.7f; // Wider zoom for aesthetics
}

Mario::~Mario() {
    UnloadTexture(sprite);
    UnloadTexture(jump_sprite);
    UnloadTexture(jump_sprite_left);
    UnloadTexture(right_sprite);
    UnloadTexture(left_idle_sprite);
    UnloadTexture(left_sprite);
    UnloadTexture(bigMario_sprite);
    UnloadTexture(bigMarioLeft_sprite);
    UnloadTexture(bigMarioWalkLeft_sprite);
    UnloadTexture(bigMarioWalkRight_sprite);
    UnloadTexture(bigMarioJumpRight_sprite);
    UnloadTexture(bigMarioJumpLeft_sprite);
    UnloadTexture(marioDeath_sprite);
    UnloadTexture(marioPowerUp_sprite);
}

Camera2D& Mario::GetCamera() {
    return camera;
}

void Mario::Update() {
	Draw();
	Movement();
	Jumping();
	Camera();
}

void Mario::PowerUpAnimation() {
float timer = GetTime() - start_timer;
if (IsBig and playedPoweredUp == false) {
	if (timer <= 0.2) {
	std::cout << "here1\n";
  	//play the base sprite for 0.2s
   	PlaySound(powerUp);
	std::cout << "playing sound\n";
	DrawTexture(sprite, Position.x, Position.y, WHITE);
	}
	else if (timer <= 0.4) {
	std::cout << "here2\n";
	//play the second between this time
  	DrawTexture(marioPowerUp_sprite, Position.x, Position.y - 10, WHITE);
	}
	else if(timer > 0.6) {
	std::cout << "here3\n";
   	DrawTexture(bigMario_sprite, Position.x, Position.y - 35, WHITE);
        playedPoweredUp = true;
     		}	
	}
}

void Mario::Draw() {
  //DrawTexture(marioPowerUp_sprite, 100, 100, WHITE);
  PowerUpAnimation(); 
  if (IsBig == false) {
      if (override_jump_animation) { 
	   if (GetForwardVector().x == 1 and GetForwardVector().y == 0) {
	 	 DrawTexture(jump_sprite, Position.x, Position.y, WHITE);
   	    }
	   else	 DrawTexture(jump_sprite_left, Position.x, Position.y, WHITE);
            
     }
     else if (override_left_animation) { 
   	frameCounter ++;
        //Alternate between base and right sprite
        if ((frameCounter / switchRate) % 2 == 0) {
            DrawTexture(left_idle_sprite, Position.x, Position.y, WHITE);
        } else {
            DrawTexture(left_sprite, Position.x, Position.y, WHITE);
        }

    }
     else if (override_right_animation) { 
    	   frameCounter ++;
       // Alternate between base and right sprite
        if ((frameCounter / switchRate) % 2 == 0) {
            DrawTexture(sprite, Position.x, Position.y, WHITE);
        } else {
            DrawTexture(right_sprite, Position.x, Position.y, WHITE);
        }
    }
     else if (IsAlive == false) {
   	DrawTexture(marioDeath_sprite, Position.x, Position.y, WHITE);
   
	float air_time = 0.5f;
   	double elapsed = GetTime() - start_timer;
   	if (elapsed <= air_time) {
		std::cout << "here\n";
      		Position.y -= 4;
   	  }
         if (elapsed > air_time) {
		 Position.y += GetGravity() * 0.55;
   	}
   }
   else	{ 
	   if (GetForwardVector().x == 1 and GetForwardVector().y == 0) {
	   	DrawTexture(sprite, Position.x, Position.y, WHITE);
  	   }
	   else DrawTexture(left_idle_sprite, Position.x, Position.y, WHITE);
		}
	}
   if (IsBig and playedPoweredUp) {
	   if (override_jump_animation) { 
	   	if (GetForwardVector().x == 1) {
	 	  DrawTexture(bigMarioJumpRight_sprite, Position.x, Position.y - 35, WHITE);
   	    	}
	    else  DrawTexture(bigMarioJumpLeft_sprite, Position.x, Position.y - 35, WHITE);
     	}
	else if (override_left_animation) { 
	 	frameCounter ++;
		if ((frameCounter / switchRate) % 2 == 0) {
    			DrawTexture(bigMarioLeft_sprite, Position.x, Position.y - 35, WHITE);
		}
		else {
    			DrawTexture(bigMarioWalkLeft_sprite, Position.x, Position.y - 35, WHITE);
		}
	     }
	 else if (override_right_animation) {
	 	frameCounter ++;
		if ((frameCounter / switchRate) % 2 == 0) {
    			DrawTexture(bigMario_sprite, Position.x, Position.y - 35, WHITE);
		}
		else {
    			DrawTexture(bigMarioWalkRight_sprite, Position.x, Position.y - 35, WHITE);
		}
	 }
    else {
		if (GetForwardVector().x == 1) {
    			DrawTexture(bigMario_sprite, Position.x, Position.y - 35, WHITE);
	 	}
		   else DrawTexture(bigMarioLeft_sprite, Position.x, Position.y -  35, WHITE);
   		}	
	}
}

void Mario::Movement() {
   hitbox.x = Position.x;
   hitbox.y = Position.y;

   if (IsKeyDown(KEY_LEFT)) {
	SetForwardVector({-1, 0}); //set forward to -1
        if (Position.x <= 0) Position.x = 0;
	else {
		override_left_animation = true;
		override_right_animation = false;
	 	Position.x -= speed;
    	}
   }
   else if (IsKeyDown(KEY_RIGHT)) {
	        SetForwardVector({1, 0}); //set forward to 1
       		override_left_animation = false;
		override_right_animation = true;
		Position.x += speed;
    }
   else {
   	override_left_animation = false;
	override_right_animation = false;
   }
    //need to add air physics
    if (IsKeyDown(KEY_SPACE) and !IsJumping) {
	    IsJumping = true;
	    IsFalling = false;
	    override_left_animation = false;
	    override_right_animation = false;
	    start_timer = GetTime();
    }
    if (IsJumping) {
    	Jumping();
    }
}


void Mario::Camera() {
    // Smoothly update camera position
    camera.target.x += (Position.x - camera.target.x) * 0.1f;
    // Prevent camera from going left past 575
    if (camera.target.x <= 575) {
        camera.target.x = 575;
    }
}

void Mario::Jumping() {
   //Handle when mario jumps
   float air_time = 0.5f;
   double elapsed = GetTime() - start_timer;
  // std::cout << "Clock: " << elapsed << std::endl;
   if (elapsed <= air_time) {
      override_jump_animation = true;	
      Position.y -= jump * (1.0f - pow(elapsed / air_time, 2));
      jumpCycle = false;
   }
   //now when mario reaches his peak he must come down
   //so when mario exceeds his air time, he must travel down 9.8f
   else {
    	IsFalling = true;	   
   	Position.y += GetGravity() * 0.55;
   }
   // Stop jumping when Mario reaches the ground (adjust Y value as needed)
   if (Position.y >= 415) {
        Position.y = 415;
        override_jump_animation = false; 
	IsFalling = false;
	IsJumping = false; // Allow jumping again
        jumpCycle = true;
      }   
}





