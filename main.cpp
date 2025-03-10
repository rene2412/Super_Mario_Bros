#include "raylib.h"
#include "load_map.h"
#include "mario.h"
#include <iostream>
using namespace std;


int main() {
   InitWindow(800, 600, "Raylib Test");

   Mario mario;
   MapAssets map;
   while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
	map.Draw(); //draw brick
	mario.Draw(); //DrawMario
        mario.MoveLeft();
	EndDrawing();
    }
 
    CloseWindow();
    return 0;
}

