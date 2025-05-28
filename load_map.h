#pragma once

#include "raylib.h"
#include "mario.h"
#include <vector>
class MapAssets {
private:
    Texture2D brick, hill, question, tube, tube2, tube3, tube4, hardbrick, cloud, mushroom, stairs, coin, completedBrick;
    Rectangle hitbox_tube, hitbox_tube2, hitbox_tube3, hitbox_tube4, hitbox_mushroom;
    Vector2 MushroomPos;

    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when donere 

    std::vector<Rectangle> hitbox_hardbricks;
    std::vector<Rectangle> question_bricks;
    std::vector<Rectangle> hitbox_stairs;
 
    std::vector<Vector2> allCoinPositions;    

    std::vector<bool> removeQuestionBricks; 
    std::vector<bool> hasQuestionPassed; 
    std::vector<bool> haveCoinsPassed;
    std::vector<bool> showCoin;

    std::vector<float> coinTimer;


    bool mushroomCollided = false;
    int questionIndex;

public:
    MapAssets();  
    ~MapAssets(); 

    void Draw();  
    void CoinAnimation();
    void DrawStairs();     
    void MushroomAnimation();    
    void CompletedBrick();

    bool GetMushroomCollided() const { return mushroomCollided; }
    void SetMushroomCollided(bool m) { mushroomCollided = m; } 

    const std::vector<bool>& GetRemoveQuestionBricks() const { return removeQuestionBricks; } 
    void SetRemoveQuestionBricks(int value, int index) { removeQuestionBricks[index] = value; }
    
    const std::vector<bool>& GetHasQuestionPassed() const { return hasQuestionPassed; }
    void SetHasQuestionPassed(int value, int index) { hasQuestionPassed[index] = value; }

    const std::vector<bool>& GetHaveCoinsPassed() const { return haveCoinsPassed; }
    void SetHaveCoinsPassed(int value, int index) { haveCoinsPassed[index] = value; } 

    const std::vector<bool>& GetShowCoin() const { return showCoin; }
    void SetShowCoin(int value, int index) { showCoin[index] = value; }		
     
    const std::vector<float>& GetCoinTimer() const { return coinTimer; }
    void SetCoinTimer(float c, int index) { coinTimer[index] = c; }

    int GetQuestionIndex() const { return questionIndex; }
    void SetQuestionIndex(int i) { questionIndex = i;  }

    
    Texture2D GetCoin() const { return coin; } 
    
    Vector2 GetMushroomPos() const { return MushroomPos; }
    void SetMushroomPos(Vector2 newMushroomPos) { MushroomPos = newMushroomPos; }

    Rectangle GetMushroom() { 
	     hitbox_mushroom.x = MushroomPos.x;
             hitbox_mushroom.y = MushroomPos.y;
	    return hitbox_mushroom; 
    }
    Rectangle GetTube() const { return hitbox_tube; }
    Rectangle GetTube2() const { return hitbox_tube2; }
    Rectangle GetTube3() const { return hitbox_tube3; }
    Rectangle GetTube4() const { return hitbox_tube4; }
    
    const std::vector<Rectangle> &GetHardBrick() const { return hitbox_hardbricks; }
    const std::vector<Rectangle> &GetQuestionBrick() const { return question_bricks; }
    const std::vector<Rectangle> &GetStairs() const { return hitbox_stairs; }
    
    void AddHardBrick(float posX, float posY, float width, float height) { hitbox_hardbricks.push_back({posX, posY, width, height}); }
    void AddQuestionBrick(float posX, float posY, float width, float height) { question_bricks.push_back({posX, posY, width, height}); }
    void AddStairs(float posX, float posY, float width, float height) { hitbox_stairs.push_back({posX, posY, width, height}); }



};

