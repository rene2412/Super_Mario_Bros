#pragma once

#include "raylib.h"

class MapAssets {
public:
    MapAssets();  // Constructor to initialize textures
    ~MapAssets(); // Destructor to unload textures

    void Draw();  // Draw the map assets

private:
    Texture2D brick, hill, question, tube, hardbrick, cloud;

    void LoadTextures();   // Load textures once
    void UnloadTextures(); // Unload textures when done
};

