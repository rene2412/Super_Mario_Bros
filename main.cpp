#include "raylib.h"
#include <iostream>
using namespace std;


int main() {
    InitWindow(800, 600, "Raylib Test");
    BeginBlendMode(BLEND_ALPHA);
    Image img = LoadImage("brick.png");
    ImageResize(&img, img.width / 10, img.height / 10);  // Use integer division
    Texture2D texture = LoadTextureFromImage(img); // Convert to texture
    UnloadImage(img);  // Free image from memory after loading into texture
    
    Image img2 = LoadImage("mariosprite.png");
    ImageResize(&img2, img2.width / 6, img2.height / 6); 
    Texture2D mario = LoadTextureFromImage(img2); // Convert to texture
    UnloadImage(img2);  
    
    

   while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);

        int x = 0;
        int y = 599;

        for (int cols = 0; cols < 3; cols++) {
            y -= texture.height; // Move up for each row
            for (int rows = 0; rows < 24; rows++) {
                DrawTexture(texture, x, y, WHITE);
                x += texture.width; // Move right for each row
            }
	        x = 0;
        }
	DrawTexture(mario, 100, 400, WHITE);
        EndDrawing();
    }
 
    EndBlendMode();

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}

