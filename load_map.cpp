#include "load_map.h"

// Constructor: Loads textures once
MapAssets::MapAssets() {
    Image img = LoadImage("images/brick.png");
    ImageResize(&img, img.width / 10, img.height / 10);
    brick = LoadTextureFromImage(img);
    UnloadImage(img);

    Image img2 = LoadImage("images/hill.png");
    ImageResize(&img2, img2.width / 10, img2.height / 10);
    hill = LoadTextureFromImage(img2);
    UnloadImage(img2);

    Image img3 = LoadImage("images/question.png");
    ImageResize(&img3, img3.width / 12, img3.height / 12);
    question = LoadTextureFromImage(img3);
    UnloadImage(img3);

    Image img4 = LoadImage("images/hard_brick.png");
    ImageResize(&img4, img4.width / 24 , img4.height / 24);
    hardbrick = LoadTextureFromImage(img4);
    UnloadImage(img4);
}

// Destructor: Unloads textures when the object is destroyed
MapAssets::~MapAssets() {
    UnloadTextures();
}

// Draw function
void MapAssets::Draw() {
    int x = 0;
    int y = 599;

    for (int cols = 0; cols < 3; cols++) {
        y -= brick.height; // Move up for each row
        for (int rows = 0; rows < 50; rows++) {
            DrawTexture(brick, x, y, WHITE);
            x += brick.width; // Move right for each row
        }
        x = 0;
    }

    DrawTexture(hill, 230, 402, WHITE);
    int posX = 580;
    for (int i = 0; i < 2; i++) {
    	DrawTexture(question, posX, 250, WHITE);
    	posX += 100;
    }
    posX = 530;
    for (int i = 0; i < 3; i++) {  
   	 DrawTexture(hardbrick, posX, 250, WHITE);
	 posX += 100;
    }
}

// Unload textures when no longer needed
void MapAssets::UnloadTextures() {
    UnloadTexture(brick);
    UnloadTexture(hill);
    UnloadTexture(question);
    UnloadTexture(hardbrick);
}

