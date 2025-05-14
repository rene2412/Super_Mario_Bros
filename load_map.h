#pragma once

#include "raylib.h"
#include <vector>
class MapAssets {
private:
    Texture2D brick, hill, question, tube, tube2, tube3, tube4, hardbrick, cloud, mushroom, stairs, coin;
    Rectangle hitbox_tube, hitbox_tube2, hitbox_tube3, hitbox_tube4, hitbox_mushroom;
    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when done

    std::vector<Rectangle> hitbox_hardbricks;
    std::vector<Rectangle> question_bricks;
    std::vector<Rectangle> hitbox_stairs;
public:
    MapAssets();  // Constructor to initialize textures
    ~MapAssets(); // Destructor to unload textures

    void Draw();  // Draw the map assets
    void CoinAnimation();
    void DrawStairs();     
   
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

