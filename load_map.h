#pragma once

#include "raylib.h"

class MapAssets {
private:
    Texture2D brick, hill, question, tube, hardbrick, cloud, mushroom;
    Rectangle hitbox_hardbrick, hitbox_question, hitbox_tube;
    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when done

public:
    MapAssets();  // Constructor to initialize textures
    ~MapAssets(); // Destructor to unload textures

    void Draw();  // Draw the map assets
    Rectangle GetTube() const { return hitbox_tube; }
    Rectangle GetHardBrick() const { return hitbox_hardbrick; }
    Rectangle GetQuestionBrick() const { return hitbox_question; }

};

