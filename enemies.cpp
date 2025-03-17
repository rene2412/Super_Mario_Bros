#include "raylib.h"
#include "enemies.h"

Goomba::Goomba() {
img = LoadImage("images/plzz.png");
ImageResize(&img, 55, 40);
sprite = LoadTextureFromImage(img);
UnloadImage(img);

img2 = LoadImage("images/goomba_smashed.png");
ImageResize(&img2, 30, 40);
sprite2 = LoadTextureFromImage(img2);
UnloadImage(img2);

Position.x = 500;
Position.y = 446;
speed = 1.0f;

HitBox = { Position.x, Position.y, 55, 40 };
}

Goomba::~Goomba() {
   UnloadTexture(sprite);
   UnloadTexture(sprite2);
}

void Goomba::Draw() {
	DrawTexture(sprite, Position.x, Position.y, WHITE);
}

void Goomba::Movement(Mario &mario) {
	float distance = Position.x - mario.GetPosition().x;
		if (distance <= 250) {
	        Position.x -= GetSpeed();
		HitBox.x = Position.x;
       		HitBox.y = Position.y;
	}
}

void Goomba::Update(Mario &mario) {
	Draw();
	Movement(mario);
}
