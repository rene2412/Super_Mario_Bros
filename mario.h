#pragma once

#include "raylib.h"
#include "load_map.h"
#include <iostream>

class Mario {
private:
    Image img, left_idle, jump_img, jump_img_left, right_img, left_img, marioPowerUp_img, bigMario_img, bigMarioLeft_img,
    bigMarioWalk_img, bigMarioWalkLeft_img, bigMarioWalkRight_img, bigMarioJumpRight_img, bigMarioJumpLeft_img, marioDeath_img;
    Texture2D sprite, left_idle_sprite, jump_sprite, jump_sprite_left, right_sprite, left_sprite, marioPowerUp_sprite, bigMario_sprite, bigMarioLeft_sprite,
    bigMarioWalk_sprite, bigMarioWalkRight_sprite, bigMarioWalkLeft_sprite, bigMarioJumpRight_sprite, bigMarioJumpLeft_sprite, marioDeath_sprite;
    Sound powerUp, jumpSound;
    Vector2 Position;
    Vector2 Forward;
    Rectangle hitbox;
    Rectangle big_hitbox;
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
    bool IsBig;
    bool playedPoweredUp;
    bool usingHead;
    bool jumpCycle;
    bool showMushroom;
    float start_timer;
    int frameCounter = 0;
    int switchRate = 10;
public:
    Mario();
    ~Mario();

    Camera2D& GetCamera();
    Vector2 GetForwardVector() { return Forward; }
    Vector2 GetPosition () { return Position; }
    const float GetGravity() const { return gravity; }
    Rectangle GetHitBox() const { return hitbox; }
    Rectangle GetBigHitBox() const { return big_hitbox; }
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
    bool GetIsBig() const { return IsBig; }
    bool GetIsPoweredUp() const { return playedPoweredUp; }
    bool GetShowMushroom() const { return showMushroom; }    

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
    void SetIsBig(bool b) { IsBig = b; }
    void SetIsPoweredUp(bool p) { playedPoweredUp = p; }
    void SetShowMushroom(bool s) { showMushroom = s; }

    void Update();
    void Combat();
    void Draw();
    void Movement();
    void Camera();
    void Jumping();
    void Mushroom();   
    void PowerUpAnimation();
};

