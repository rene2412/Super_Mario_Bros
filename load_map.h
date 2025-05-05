#pragma once

#include "raylib.h"
#include <vector>
class MapAssets {
private:
    Texture2D brick, hill, question, tube, tube2, tube3, tube4, hardbrick, cloud, mushroom, stairs;
    Rectangle hitbox_question, hitbox_tube, hitbox_tube2, hitbox_tube3, hitbox_tube4, hitbox_mushroom, hitbox_stairs;
    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when done

    std::vector<Rectangle> hitbox_hardbricks;

public:
    MapAssets();  // Constructor to initialize textures
    ~MapAssets(); // Destructor to unload textures

    void Draw();  // Draw the map assets
    Rectangle GetTube() const { return hitbox_tube; }
    Rectangle GetTube2() const { return hitbox_tube2; }
    Rectangle GetTube3() const { return hitbox_tube3; }
    Rectangle GetTube4() const { return hitbox_tube4; }
    Rectangle GetQuestionBrick() const { return hitbox_question; }
    Rectangle GetStairs() const { return hitbox_stairs; }
    
    const std::vector<Rectangle> &GetHardBrick() const { return hitbox_hardbricks; }
    void AddHardBrick(float posX, float posY, float width, float height) { hitbox_hardbricks.push_back({posX, posY, width, height}); }
};

