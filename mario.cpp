#include "mario.h"
#include <cmath>

Mario::Mario() {
    // Load Mario's sprite
    img = LoadImage("images/mario64.png");
    ImageResize(&img, img.width / 24, img.height / 24);
    sprite = LoadTextureFromImage(img);
    UnloadImage(img);
    
    jump_img = LoadImage("images/mariojump.png");
    ImageResize(&jump_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    jump_sprite = LoadTextureFromImage(jump_img);
    UnloadImage(jump_img);

    right_img = LoadImage("images/marioright.png");
    ImageResize(&right_img, 50, 66); // 50 width and 66 height are just the values from the base animation
    right_sprite = LoadTextureFromImage(right_img);
    UnloadImage(right_img);


    Position.x = 50;
    Position.y = 415;
    speed = 5.0f;
    jump = 8.0f;
    IsJumping = false;
    override_animation = false;
    // Camera setup
    camera.target = Position;
    camera.offset = { 400, 480 }; // Keep Mario centered
    camera.rotation = 0.0f;
    camera.zoom = 0.7f; // Wider zoom for aesthetics
}

Mario::~Mario() {
    UnloadTexture(sprite);
    UnloadTexture(jump_sprite);
    UnloadTexture(right_sprite);
}

Camera2D& Mario::GetCamera() {
    return camera;
}


void Mario::Draw() {
   if (override_animation == false) { 
    	DrawTexture(sprite, Position.x, Position.y, WHITE);
   }
   else	DrawTexture(jump_sprite, Position.x, Position.y, WHITE);
}

void Mario::Movement() {
   if (IsKeyDown(KEY_LEFT)) {
        if (Position.x <= 0) Position.x = 0;
        else Position.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        Position.x += speed;
    }
    //need to add air physics
    if (IsKeyDown(KEY_SPACE) and !IsJumping) {
	    IsJumping = true;
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
   std::cout << "Clock: " << elapsed << std::endl;
   if (elapsed <= air_time) {
      override_animation = true;	
      Position.y -= jump * (1.0f - pow(elapsed / air_time, 2));
   }
   //now when mario reaches his peak he must come down
   //so when mario exceeds his air time, he must travel down 9.8f
   else {	
   	Position.y += GetGravity() * 0.55;
   }
   // Stop jumping when Mario reaches the ground (adjust Y value as needed)
   if (Position.y >= 415) {
        Position.y = 415;
        override_animation = false; 
	IsJumping = false; // Allow jumping again
   }
   
}
