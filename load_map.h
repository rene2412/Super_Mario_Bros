#pragma once

#include "raylib.h"
#include <iostream>

class MapAssets {
public:

Texture2D Brick() {
    Image img = LoadImage("images/brick.png");
    ImageResize(&img, img.width / 10, img.height / 10);  // Use integer division
    Texture2D brick = LoadTextureFromImage(img); // Convert to texture
    UnloadImage(img);  // Free image from memory after loading into texture
    return brick;
}

void Draw() {
     int x = 0;
     int y = 599;

     Texture2D brick = Brick();
        for (int cols = 0; cols < 3; cols++) {
            y -= brick.height; // Move up for each row
            for (int rows = 0; rows < 24; rows++) {
                DrawTexture(brick, x, y, WHITE);
                x += brick.width; // Move right for each row
            }
	        x = 0;
        }
}

};
