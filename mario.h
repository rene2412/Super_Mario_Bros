#pragma once

#include "raylib.h"
#include <iostream>

class Mario {
private:
Image img;
Texture2D sprite;
Vector2 Position;
Rectangle hitbox;
int speed;

public:
 Mario() {
    //the main sprite of small mario	 
    img = LoadImage("images/mario64.png");
    ImageResize(&img, img.width / 24, img.height / 24); 
    sprite = LoadTextureFromImage(img); // Convert to texture
    UnloadImage(img);
    
    //the sprite to animate mario left

    
    
    
    
    
    
    Position.x = 50;
    Position.y = 415;
    speed = 3;
 }

 ~Mario() {
    UnloadTexture(sprite);  
}


 void Draw() { 
	DrawTexture(sprite, Position.x, Position.y, WHITE);
 }

 void MoveLeft() {
	if (IsKeyDown(KEY_LEFT)) {
		//if left arrow is down move
		Position.x -= speed;
	} 
 }
 
 

};
