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
    bool IsFalling;
    bool override_jump_animation;
    bool override_left_animation;
    bool override_right_animation;
    bool IsOnGround;
    bool IsOnAsset;
    float start_timer;
    int frameCounter = 0 ;
    const int switchRate = 5; 
public:
    Mario();
    ~Mario();

    Camera2D& GetCamera();
    Vector2 GetForwardVector() { return Forward; }
    Vector2 GetPosition () { return Position; }
    const float GetGravity() const { return gravity; }
    Rectangle GetHitBox() const { return hitbox; }
    bool GetIsJumping() const { return IsJumping; }
    bool GetIsFalling() const { return IsFalling; }
    bool GetOverrideJumpAnimation() const { return override_jump_animation; }
    bool GetIsOnGround() const { return IsOnGround; }
    bool GetIsOnAsset() const { return IsOnAsset; }
    
    void SetPosition(Vector2 newPosition)  { Position = newPosition; }    
    void SetForwardVector(Vector2 newForward) { Forward = newForward; }
    void SetIsJumping(bool j) { IsJumping = j; }
    void SetOverrideJumpAnimation(bool o) { override_jump_animation = o; }
    void SetIsOnGround(bool ground)  { IsOnGround = ground; }
    void SetIsFalling(bool f) { IsFalling = f; }
    void SetIsOnAsset(bool a) { IsOnAsset = a; }

    void Update();
    void Combat();
    void Draw();
    void Movement();
    void Camera();
    void Jumping();
    
};

