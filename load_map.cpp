#include "load_map.h"
#include "mario.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

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

    Image img5 = LoadImage("images/cloud.png");
    ImageFormat(&img5, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); 
    std::cout << "Image format: " << img5.format << std::endl;
    ImageResize(&img5, img5.width / 3, img5.height / 3);
    cloud = LoadTextureFromImage(img5);
    UnloadImage(img5);

    Image img6 = LoadImage("images/tube.png");
    ImageResize(&img6, img6.width / 4 , img6.height / 2);
    hitbox_tube = {1100, 283, float(img6.width), float(img6.height) }; //this code is from the future spookyyyyyyyy
    tube = LoadTextureFromImage(img6);
    UnloadImage(img6);

    Image img7 = LoadImage("images/mushroom.png");
    ImageResize(&img7, img7.width / 7, img7.height / 6);
    hitbox_mushroom = {240, 250, float(img7.width), float(img7.height) }; //this code is from the future spookyyyyyyyy
    mushroom = LoadTextureFromImage(img7);
    UnloadImage(img7);
   
    Image img8 = LoadImage("images/stairs.png");
    ImageResize(&img8, img8.width / 7, img8.height / 6);
    hitbox_stairs = {900, 351, float(img8.width), float(img8.height) }; //this code is from the future spookyyyyyyyy
    stairs = LoadTextureFromImage(img8);
    UnloadImage(img8);

    Image img9 = LoadImage("images/tube.png");
    ImageResize(&img9, img9.width / 4 , img9.height - 100);
    hitbox_tube2 = {1500, 218, float(img9.width), float(img9.height) }; //this code is from the future spookyyyyyyyy
    tube2 = LoadTextureFromImage(img9);
    UnloadImage(img9);


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
        for (int rows = 0; rows < 85; rows++) {
            DrawTexture(brick, x, y, WHITE);
            x += brick.width; // Move right for each row
        }
        x = 0;
    }

    DrawTexture(hill, 230, 402, WHITE);
    
    DrawTexture(question, 330, 250, WHITE);
    int posX = 580;
    for (int i = 0; i < 3; i++) {
    	DrawTexture(question, posX, 250, WHITE);
    	posX += 100;
    }
    DrawTexture(question, 630, 100, WHITE);
    
    posX = 530;
    for (int i = 0; i < 3; i++) {  
   	 DrawTexture(hardbrick, posX, 250, WHITE);
	 posX += 100;
    }
    	posX = 200;
    for (int i = 0; i < 23; i++) {
   	 DrawTexture(cloud, posX, -60, WHITE);
    	 posX += 250;
    }
   	 DrawTexture(tube, 1100, 283, WHITE);
   	 DrawTexture(mushroom, 240, 250, WHITE);
	 DrawTexture(stairs, 1300, 351, WHITE);
   	 DrawTexture(tube2, 1500, 218, WHITE);

}

// Unload textures when no longer needed
void MapAssets::UnloadTextures() {
    UnloadTexture(brick);
    UnloadTexture(hill);
    UnloadTexture(question);
    UnloadTexture(hardbrick);
    UnloadTexture(cloud);
    UnloadTexture(tube);
    UnloadTexture(tube2);
    UnloadTexture(stairs);
}

