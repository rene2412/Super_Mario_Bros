#pragma once

#include "raylib.h"
#include <iostream>

class Mario {
private:
    Image img, left_idle, jump_img, jump_img_left, right_img, left_img;
    Texture2D sprite, left_idle_sprite, jump_sprite, jump_sprite_left, right_sprite, left_sprite;
    Vector2 Position;
    Vector2 Forward;
    Rectangle hitbox;
    Camera2D camera;
    float speed;
    float jump;
    float const gravity = 9.8f;
    bool IsJumping;
    bool override_jump_animation;
    bool override_left_animation;
    bool override_right_animation;
    float start_timer;
    int frameCounter = 0 ;
    const int switchRate = 5; 

public:
    Mario();
    ~Mario();

    Camera2D& GetCamera();
    Vector2 GetForwardVector() { return Forward; }
    const float GetGravity() const { return gravity; }
    Rectangle GetHitBox() const { return hitbox; }

    void SetForwardVector(Vector2 newForward) { Forward = newForward; }
    
    void Update();
    void Combat();
    void Draw();
    void Movement();
    void Camera();
    void Jumping();
};

