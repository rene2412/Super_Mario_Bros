#include "raylib.h"
#include "enemies.h"
#include <memory>

Image Goomba::img, Goomba::img2, Goomba::img3, Goomba::img4;
Texture2D Goomba::sprite, Goomba::sprite1, Goomba::sprite2, Goomba::sprite3, Goomba::sprite4;

std::vector<std::shared_ptr<Goomba>> goomba;

Goomba::Goomba() {
LoadGoombaTextures();
   Position = {0, 0};
   speed = 1.5f;
   frameCounter = 0;
   IsMoving = false;
   IsAlive = true;
   IsDamageValid = true;
   HitBox = { Position.x, Position.y, 55, 40 };
}
Goomba::~Goomba() {}

void Goomba::LoadGoombaTextures() {
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

}


void Goomba::FreeGoombaTextures() {
	std::cout << "called???\n"; 
   UnloadTexture(sprite);
   UnloadTexture(sprite2);
   UnloadTexture(sprite3);
   UnloadTexture(sprite4);
}

void Goomba::Spawn(std::vector<std::shared_ptr<Goomba>>& goomba) {
    std::vector<float> positionsX = { 500, 1680, 2400, 2500, 3850, 3920};
    std::vector<float> positionsY = { 446, 446, 446, 446, 72, 72 };
	int N = positionsX.size();
	for (int i = 0; i < N; i++) {
	//shared smart pointer since all goombas do the same thing
    	auto g = std::make_shared<Goomba>();
		g->SetPosition({positionsX[i], positionsY[i]});	
   	 	g->SetHitBox({positionsX[i], positionsY[i], 55, 40});
		g->SetSpeed(1.5);
		g->SetIsAlive(true);
		g->SetIsMoving(false);
		g->SetIsDamageValid(true);
		g->SetIsFalling(false);
		g->SetIsOnBricks(false);
    		goomba.push_back(g);
    }
}

void Goomba::Update(Mario &mario)  {
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

void Goomba::Movement(Mario &mario)  {
	float distance = Position.x - mario.GetPosition().x;
		if (distance <= 100 and IsAlive) {
	        IsMoving = true;
		Position.x -= GetSpeed();
		HitBox.x = Position.x;
       		HitBox.y = Position.y;
		}
		if (distance > 250) { 
			IsMoving = false;
	}
}

Koopa::Koopa() {
  LoadTextures();
  Position = {5110, 415};
  speed = 1.5f;
  frameCounter = 0;
  IsMoving = false;
  IsAlive = true;
  IsDamageValid = true;
  HitBox = { Position.x, Position.y, 55, 40 };
}

Koopa::~Koopa() {
	FreeTextures();
}

void Koopa::LoadTextures() {
img = LoadImage("images/koopaIdle.png");
ImageResize(&img, 80, 70);
sprite = LoadTextureFromImage(img);
UnloadImage(img);

img2 = LoadImage("images/koopaLeft.png");
ImageResize(&img2, 80, 70);
sprite1 = LoadTextureFromImage(img2);
UnloadImage(img2);
}

void Koopa::FreeTextures() {
	UnloadTexture(sprite);
	UnloadTexture(sprite1);
}

void Koopa::Update(Mario &mario) {
	Draw();
	Movement(mario);
	Animations();
}

void Koopa::Draw() {
	if (IsAlive) {
		DrawTexture(sprite, Position.x, Position.y, WHITE);
	}
}

void Koopa::Animations() {
	if (IsMoving and IsAlive) {
		frameCounter ++;
		if ((frameCounter / switchRate) % 2 == 0) {	
			 DrawTexture(sprite, Position.x, Position.y, WHITE);
		 }
		else DrawTexture(sprite1, Position.x, Position.y, WHITE);
	}
	if (!IsAlive) {

	}
}

void Koopa::Movement(Mario &mario) {
	 float Distance =  Position.x - mario.GetPosition().x;
	if (Distance <= 500) {
		IsMoving = true;
		Position.x -= speed;	
	}
	if (Distance > 500) {
		IsMoving = false;
	}
}