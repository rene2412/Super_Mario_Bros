#include "raylib.h"
#include "enemies.h"

Goomba::Goomba() {
img = LoadImage("images/goombaIdle.png");
ImageResize(&img, 55, 40);
sprite = LoadTextureFromImage(img);
UnloadImage(img);

img2 = LoadImage("images/goombaLeft.png");
ImageResize(&img2, 55, 40);
sprite2 = LoadTextureFromImage(img2);
UnloadImage(img2);

img3 = LoadImage("images/goombaRight.png");
ImageResize(&img3, 55, 40);
sprite3 = LoadTextureFromImage(img3);
UnloadImage(img3);

img4 = LoadImage("images/goombaDeath.png");
ImageResize(&img4, 55, 40);
sprite4 = LoadTextureFromImage(img4);
UnloadImage(img4);

Position.x = 500;
Position.y = 446;
speed = 1.5f;
frameCounter = 0;
IsMoving = false;
IsAlive = true;
IsDamageValid = true;
HitBox = { Position.x, Position.y, 55, 40 };
}

Goomba::~Goomba() {
   UnloadTexture(sprite);
   UnloadTexture(sprite2);
   UnloadTexture(sprite3);
   UnloadTexture(sprite4);
}

void Goomba::Update(Mario &mario) {
	Draw();
	Movement(mario);
	Animations();
}

void Goomba::Draw() {
	if (IsAlive) {
	DrawTexture(sprite, Position.x, Position.y, WHITE);
	}
}

void Goomba::Animations() {
	if (IsMoving and IsAlive) {
		std::cout << "MOVING\n";
		frameCounter ++;
		 if ((frameCounter / switchRate) % 2 == 0) {	
			DrawTexture(sprite2, Position.x, Position.y, WHITE);
		 }
		else DrawTexture(sprite3, Position.x, Position.y, WHITE);
	}
	if (!IsAlive) {
		DrawTexture(sprite4, Position.x, Position.y, WHITE);
	}
}

void Goomba::Movement(Mario &mario) {
	float distance = Position.x - mario.GetPosition().x;
		if (distance <= 250 and IsAlive) {
	        IsMoving = true;
		Position.x -= GetSpeed();
		HitBox.x = Position.x;
       		HitBox.y = Position.y;
		}
		if (distance > 250) { 
			IsMoving = false;
	}
}


