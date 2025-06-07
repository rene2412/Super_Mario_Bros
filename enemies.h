#pragma once
#include "raylib.h"
#include "mario.h"
#include <memory>
#include <vector>

class Enemies {
    protected:
	 Image img, img2, img3, img4, img5, img6;
	 Texture2D sprite, sprite1, sprite2, sprite3, sprite4;
         Vector2 Position;
	 Rectangle HitBox;
	 float speed;
	 float frame_speed;
	 bool IsAlive;
   	 bool IsMoving;
	 bool IsDamageValid;
	 int frameCounter;
	 const int switchRate = 5; 
    public:
	 Enemies() {}
	 virtual ~Enemies() {}
         Vector2 GetPosition() const { return Position; }
	 Rectangle GetHitBox() const {
   		 return Rectangle{ Position.x, Position.y, HitBox.width, HitBox.height };
	}
	 float GetSpeed() const { return speed; }
     float GetFrameSpeed() const { return frame_speed; }
	 bool GetIsAlive() const { return IsAlive; }
     bool GetIsMoving() const { return IsMoving; }
	 int GetFrameCounter() const { return frameCounter; }
 	 const int GetSwitchRate() const { return switchRate; }
	 bool GetIsDamageValid() const { return IsDamageValid; }

     void SetPosition(const Vector2& pos) { Position = pos; }
   	 void SetHitBox(const Rectangle& box) { HitBox = box; }
     void SetSpeed(float s) { speed = s; }
     void SetFrameSpeed(float fs) { frame_speed = fs; }
   	 void SetIsAlive(bool state) { IsAlive = state; }
   	 void SetIsMoving(bool state) { IsMoving = state; }
 	 void SetIsDamageValid(bool state) { IsDamageValid = state; }

	 virtual void Draw() {};
	 virtual void Update() {};
     virtual void Movement() {};
	 virtual void Animations() {};
	 virtual void Spawn() {};
};

//Goomba inherits everything from Enemies
class Goomba : public Enemies {
    private:
	static Image img, img2, img3, img4;
	static Texture2D sprite, sprite1, sprite2, sprite3, sprite4;

    public:
	 Goomba();
	 ~Goomba();
	 static void LoadTextures(); 
	 static void FreeTextures();

	 void Draw() override;
	 void Animations() override;
	 static void Spawn(std::vector<std::shared_ptr<Goomba>>& goomba); 
	 void Update(Mario &mario);
	 void Movement(Mario &mario);
};

extern std::vector<std::shared_ptr<Goomba>> goomba;
