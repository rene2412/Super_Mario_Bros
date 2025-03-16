#pragma once
#include "raylib.h"

class Enemies {
    protected:
	 Image img, img2;
	 Texture2D sprite, sprite2;
         Vector2 Position;
	 Rectangle HitBox;
	 float speed;
	 float frame_speed;
	 bool isAlive;
    public:
	 Enemies() {}
	 virtual ~Enemies() {}
         Vector2 GetPosition() const { return Position; }
	 Rectangle GetHitBox() const { return HitBox; }
	 float GetSpeed() const { return speed; }
         float GetFrameSpeed() const { return frame_speed; }
	 bool GetIsAlive() const { return isAlive; }
         
	 virtual void Draw() {};
	 virtual void Update() {};
         virtual void Movement() {};
};
//Goomba inherits everything from Enemies
class Goomba : public Enemies {
 public:
	 Goomba();
	 ~Goomba();

	 void Draw() override;
	 void Update() override;
	 void Movement() override;
}; 
