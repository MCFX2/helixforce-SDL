#include "Player.h"

#include "mouse.h"

#include "Vector.h"

static const float mouseAccel = 0.05f;

static MousePos mPos;


Player::Player() : GameObject("./assets/bullet.png")
{
	
}

void Player::update(float dt)
{
	dt;
	//follow mouse
	mPos = Mouse::Get_Pos();

	int dX = mPos.x - sprite_.getX();
	int dY = mPos.y - sprite_.getY();

	dY = (int)(dY * mouseAccel);
	dX = (int)(dX * mouseAccel);
	if (dX == 0) dX = mPos.x - sprite_.getX();
	if (dY == 0) dY = mPos.y - sprite_.getY();

	sprite_.setPos(sprite_.getX() + dX, sprite_.getY() + dY);
}
