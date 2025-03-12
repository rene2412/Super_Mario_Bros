#pragma once

#include "raylib.h"
#include <iostream>

class Mario {
private:
    Image img;
    Texture2D sprite;
    Vector2 Position;
    Rectangle hitbox;
    Camera2D camera;
    int speed;

public:
    Mario();
    ~Mario();

    Camera2D& GetCamera();
    void Draw();
    void Movement();
    void Camera();
};

