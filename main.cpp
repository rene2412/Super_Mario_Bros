#include "raylib.h"
#include "load_map.h"
#include "mario.h"
#include "enemies.h"
#include "game.h"
#include <iostream>
using namespace std;


int main() {
  const int screenWidth = 1000;
  const int screenHeight = 600;
       
  InitWindow(screenWidth, screenHeight, "Super Mario Bros");
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_WARNING);
  Game game;
  Mario mario;
  Goomba goomba;
  MapAssets map;
   while (!WindowShouldClose()) {
	mario.Camera();
        mario.Movement();
	game.Collisions(mario, goomba);
	BeginDrawing();
        ClearBackground(BLUE);
	BeginBlendMode(BLEND_ALPHA);
	BeginMode2D(mario.GetCamera());
	map.Draw(); //draw brick
	mario.Draw(); //DrawMario
	goomba.Update();
	EndMode2D();
	EndBlendMode();
	EndDrawing();
    }
 
    CloseWindow();
    return 0;
}

