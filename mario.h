#pragma once

#include "raylib.h"
#include "load_map.h"
#include <iostream>

class Mario {
private:
    Image img, left_idle, jump_img, jump_img_left, right_img, left_img, bigMario_img, bigMarioWalk_img, marioDeath_img;
    Texture2D sprite, left_idle_sprite, jump_sprite, jump_sprite_left, right_sprite, left_sprite, bigMario_sprite, bigMarioWalk_sprite, marioDeath_sprite;
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
    bool IsAlive;
    bool IsOnGround;
    bool IsOnAsset;
    bool IsOnStairs;
    bool IsOnBricks;
    bool usingHead;
    bool jumpCycle;
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
    float GetTimer() const { return start_timer; }

    bool GetIsJumping() const { return IsJumping; }
    bool GetIsFalling() const { return IsFalling; }
    bool GetOverrideJumpAnimation() const { return override_jump_animation; }
    bool GetIsOnGround() const { return IsOnGround; }
    bool GetIsOnAsset() const { return IsOnAsset; }
    bool GetIsOnStairs() const { return IsOnStairs; }
    bool GetIsOnBricks() const { return IsOnBricks; }
    bool GetIsUsingHead() const { return usingHead; }
    bool GetJumpCycle() const { return jumpCycle; }
    bool GetIsAlive() const { return IsAlive; }

    void SetTimer(float newTimer) {start_timer = newTimer; }
    void SetPosition(Vector2 newPosition)  { Position = newPosition; }    
    void SetForwardVector(Vector2 newForward) { Forward = newForward; }
    void SetIsJumping(bool j) { IsJumping = j; }
    void SetOverrideJumpAnimation(bool o) { override_jump_animation = o; }
    void SetIsOnGround(bool ground)  { IsOnGround = ground; }
    void SetIsFalling(bool f) { IsFalling = f; }
    void SetIsOnAsset(bool a) { IsOnAsset = a; }
    void SetIsOnStairs(bool s) { IsOnStairs = s; }
    void SetIsOnBricks(bool b) { IsOnBricks = b; }
    void SetHitBox(Rectangle newHitBox) { hitbox = newHitBox; }
    void SetIsUsingHead(bool h) { usingHead = h; }
    void SetIsAlive(bool a)  { IsAlive = a; } 

    void Update();
    void Combat();
    void Draw();
    void Movement();
    void Camera();
    void Jumping();
    
};

