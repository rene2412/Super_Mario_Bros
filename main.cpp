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
  InitAudioDevice();
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_WARNING);
  Game game;
  Mario mario;
  Goomba goomba;
  MapAssets map;
   while (!WindowShouldClose()) {
	BeginDrawing();
        ClearBackground(BLUE);
	BeginBlendMode(BLEND_ALPHA);
	mario.Camera();
        mario.Movement();
	game.Collisions(mario, goomba, map);
	BeginMode2D(mario.GetCamera());
	map.Draw(mario); 
	mario.Draw(); 
	goomba.Update(mario);
	EndMode2D();
	EndBlendMode();
	EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}

