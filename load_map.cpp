#include "load_map.h"
#include "mario.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor: Loads textures once
MapAssets::MapAssets() : removeQuestionBricks(4, true), hasQuestionPassed(4, false) {
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
    ImageResize(&img6, img6.width / 3 , img6.height / 2);
    hitbox_tube = {880, 293, float(img6.width), float(img6.height) }; //this code is from the future spookyyyyyyyy
    tube = LoadTextureFromImage(img6);
    UnloadImage(img6);

    Image img7 = LoadImage("images/mushroom.png");
    ImageResize(&img7, img7.width / 7, img7.height / 6);
    MushroomPos = {630, 210}; 
    hitbox_mushroom = {MushroomPos.x, MushroomPos.y, float(img7.width), float(img7.height) }; //this code is from the future spookyyyyyyyy
    mushroom = LoadTextureFromImage(img7);
    UnloadImage(img7);
   
    Image img8 = LoadImage("images/stairs.png");
    ImageResize(&img8, img8.width / 5, img8.height / 5);
    stairs = LoadTextureFromImage(img8);
    UnloadImage(img8);

    Image img9 = LoadImage("images/tube.png");
    ImageResize(&img9, img9.width / 3, img9.height - 100);
    hitbox_tube2 = {1515, 220, float((img9.width /  4) + 40) , float(img9.height - 100) }; 
    hitbox_tube3 = {2000, 220, float((img9.width /  4) + 40) , float(img9.height - 100) }; 
    tube2 = LoadTextureFromImage(img9);
    tube3 = LoadTextureFromImage(img9);
    UnloadImage(img9);

    Image img10 = LoadImage("images/coin.png");
    ImageResize(&img10, img10.width / 13, img10.height / 13);
    coin = LoadTextureFromImage(img10);
    UnloadImage(img10);

    Image img11 = LoadImage("images/completedBrick.png");
    ImageResize(&img11, img11.width / 2, img11.height / 2);
    completedBrick = LoadTextureFromImage(img11);
    UnloadImage(img11);
    questionIndex = -1;
    //load in the collision hit boxed for the bricks 
    int posX = 530;
    for (int i = 0; i < 3; i++) {  
	 AddHardBrick(posX, 250, hardbrick.width, hardbrick.height); 
	 posX += 100;
    }
    
    AddQuestionBrick(330, 250, question.width, question.height);
    posX = 580;
    for (int i = 0; i < 2; i++) {
    	AddQuestionBrick(posX, 250, question.width, question.height); 
	 posX += 100;
    }
    AddQuestionBrick(630, 100, question.width, question.height); 

   float width = stairs.width;
   float height = stairs.height;
   float startingX = 1160;
   float startingY = 452;

   /*
   for (int row = 0; row < 4; row++) {
	      int x = startingX + (width * row);
	      int y = startingY - (height * row); 
	  for (int col = 0; col < 4 - row; col++) {
		    AddStairs(x, y, width, height);
		    x += width;
	  	}
	}
	*/
    hasQuestionPassed.resize(question_bricks.size(), false);
    haveCoinsPassed.resize(3, false);

    allCoinPositions = {
    	{330, 250},
	{680, 100},
	{680, 250}
    };

    showCoin = {false, false, false};
    coinTimer = {0.0f, 0.0f, 0.0f};
}

// Destructor: Unloads textures when the object is destroyed
MapAssets::~MapAssets() {
    UnloadTextures();
}

// Draw function
void MapAssets::Draw(Mario &mario) {
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
    //this is the first question block brick
    if(removeQuestionBricks[0] == true) {
	    DrawTexture(question, 330, 250, WHITE);
    }
    int posX = 580;
    for (int i = 1; i < 3; i++) {
	if (removeQuestionBricks[i] == true) {
    		DrawTexture(question, posX, 250, WHITE);
	}
		posX += 100;
    }
    
    if (removeQuestionBricks[3] == true) {
   	 DrawTexture(question, 630, 100, WHITE);
    } 
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
   	 DrawTexture(tube, 880, 283, WHITE);
   	 DrawTexture(tube2, 1500, 180, WHITE);
   	 DrawTexture(tube3, 2000, 180, WHITE);
	 CoinAnimation();
	// DrawStairs();
	 if (GetMushroomCollided()) {
		 MushroomAnimation(mario);
	     }	
	 CompletedBrick();
}

static bool beginning = true;
void MapAssets::MushroomAnimation(Mario &mario) {
	//std::cout << MushroomPos.x << ", " << MushroomPos.y << std::endl;
if (mario.GetIsPoweredUp() == false) { 	 
       	if (beginning) {   
		MushroomPos.x += 1.2;
		}
	 if (mario.GetShowMushroom()) { 
	 	DrawTexture(mushroom, MushroomPos.x, MushroomPos.y, WHITE);
	 }
	if (MushroomPos.x >= 765) {
		MushroomPos.y += 4.3;
		if (MushroomPos.y >= 443) {
			MushroomPos.y = 443;
		}
	}
	//when the mushroom hits the tube reverse its direction
	if (CheckCollisionRecs(GetMushroom(), GetTube())) {
			beginning = false;
	      }
	if (!beginning) {
		MushroomPos.x -= 2.5;
		}
	}
}

void MapAssets::CompletedBrick() {
	if (hasQuestionPassed[0] == true) {
	       	DrawTexture(completedBrick, 330, 250, WHITE);
	}
	if (hasQuestionPassed[1] == true) { 
		DrawTexture(completedBrick, 580, 250, WHITE);
	}
	if (hasQuestionPassed[2] == true) {
	       	DrawTexture(completedBrick, 680, 250, WHITE);
	}
	if ( hasQuestionPassed[3] == true) { 
		DrawTexture(completedBrick, 630, 100, WHITE);
	}
}

void MapAssets::CoinAnimation() {
	 //std::cout << "Drawing coin at: " << CoinPos.x << ", " << CoinPos.y << "\n";
 		for (size_t i = 0; i < haveCoinsPassed.size(); i++) {
       		   if (showCoin[i] and haveCoinsPassed[i] == false) { 
			allCoinPositions[i].y -= 4;
		   	DrawTexture(coin, allCoinPositions[i].x, allCoinPositions[i].y, WHITE);
		        coinTimer[i] += GetFrameTime(); 
  		        if (coinTimer[i] >= 0.4f) {
    		       	   showCoin[i] = false;
		           coinTimer[i] = 0.0f; 
     			 }
			      
		}
	}
}

void MapAssets::DrawStairs() {
   float width = stairs.width;
   float height = stairs.height;
   float startingX = 1160;
   float startingY = 452;

   for (int row = 0; row < 4; row++) {
	      int x = startingX + (width * row);
	      int y = startingY - (height * row); 
	  for (int col = 0; col < 4 - row; col++) {
		   DrawTexture(stairs, x, y, WHITE);
		   x += width;
	  	}
	}
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
    UnloadTexture(coin);
    UnloadTexture(completedBrick);
}

