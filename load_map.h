#pragma once

#include "raylib.h"

class MapAssets {
private:
    Texture2D brick, hill, question, tube, tube2, tube3, tube4, hardbrick, cloud, mushroom, stairs;
    Rectangle hitbox_hardbrick, hitbox_question, hitbox_tube, hitbox_tube2, hitbox_tube3, hitbox_tube4, hitbox_mushroom, hitbox_stairs;
    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when done

public:
    MapAssets();  // Constructor to initialize textures
    ~MapAssets(); // Destructor to unload textures

    void Draw();  // Draw the map assets
    Rectangle GetTube() const { return hitbox_tube; }
    Rectangle GetTube2() const { return hitbox_tube2; }
    Rectangle GetTube3() const { return hitbox_tube3; }
    Rectangle GetTube4() const { return hitbox_tube4; }
    Rectangle GetHardBrick() const { return hitbox_hardbrick; }
    Rectangle GetQuestionBrick() const { return hitbox_question; }
    Rectangle GetStairs() const { return hitbox_stairs; }
};

