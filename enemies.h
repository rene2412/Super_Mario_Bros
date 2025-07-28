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
	 virtual void LoadTextures() {};
	 virtual void FreeTextures() {};

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
		os << vec.x << ", " << vec.y << std::endl;
	}
};

class Goomba : public Enemies {
    private:
	static Image img, img2, img3, img4;
	static Texture2D sprite, sprite1, sprite2, sprite3, sprite4;
	bool IsFalling;
	bool IsOnBricks;
	bool IsOnQuestion;

    public:
	 Goomba();
	 ~Goomba();

	 bool GetIsFalling() const { return IsFalling; }
	 bool GetIsOnBricks() const { return IsOnBricks; }
	 bool GetIsOnQuestion() const { return IsOnQuestion; }
	 void SetIsFalling(bool f)  { IsFalling = f; }
	 void SetIsOnBricks(bool b) { IsOnBricks = b; }
	 void SetIsOnQuestion(bool q) { IsOnQuestion = q; }

	 static void LoadGoombaTextures();
	 static void FreeGoombaTextures();
	 void Draw() override;
	 void Animations() override;
	 static void Spawn(std::vector<std::shared_ptr<Goomba>>& goomba); 
	 void Update(Mario &mario);
	 void Movement(Mario &mario);
	 
};

extern std::vector<std::shared_ptr<Goomba>> goomba;

class Koopa : public Enemies {
	public:
	Koopa();
	~Koopa();

	void Draw() override;
	void Animations() override;
	void Update(Mario &mario);
	void Movement(Mario &mario);
	void LoadTextures() override;
	void FreeTextures() override;

};
