#include "PlayerController.h"

#include "Vector.h"
#include "MathUtils.h"

#include "mouse.h"

#include "GameObject.h"

PlayerController::PlayerController()
	: mouseMinDistance_(0),
	mouseFarDistance_(12),
	speed_(1.0f),
	speedAdjust_(1.0f, 1.0f),
	deceleration_(0.2f)
{

}

Vector2 PlayerController::ParseMouse()
{
	Vector2 velocity;
	float dist = Util::Distance(Vector2(Mouse::Get_Pos().x, Mouse::Get_Pos().y), get_parent()->)

}