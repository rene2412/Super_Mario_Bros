#include "raylib.h"
#include "load_map.h"
#include "mario.h"
#include <iostream>
using namespace std;


int main() {
  const int screenWidth = 1000;
  const int screenHeight = 600;
       
  InitWindow(screenWidth, screenHeight, "Raylib Test");
  SetTargetFPS(60);

  Mario mario;
  MapAssets map;
   while (!WindowShouldClose()) {
        mario.Camera();
        mario.Movement();
	BeginDrawing();
        ClearBackground(BLUE);
	BeginMode2D(mario.GetCamera());
	map.Draw(); //draw brick
	mario.Draw(); //DrawMario
	EndMode2D();
	EndDrawing();
    }
 
    CloseWindow();
    return 0;
}

