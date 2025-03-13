#pragma once

#include "raylib.h"
#include <iostream>

class Mario {
private:
    Image img, jump_img, right_img;
    Texture2D sprite, jump_sprite, right_sprite;
    Vector2 Position;
    Rectangle hitbox;
    Camera2D camera;
    float speed;
    float jump;
    float const gravity = 9.8f;
    bool IsJumping;
    bool override_animation;
    float start_timer;
public:
    Mario();
    ~Mario();

    Camera2D& GetCamera();
    const float GetGravity() const { return gravity; }
    void tick();
    void Draw();
    void Movement();
    void Camera();
    void Jumping();
};

