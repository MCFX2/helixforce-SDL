#include "PlayerController.h"

#include "Vector.h"
#include "MathUtils.h"

#include "mouse.h"

#include "GameObject.h"

#include "fileman.h"

#include "ComponentRegistry.h"

static ComponentRegistry::RegisterComponent register_pc("PlayerController", []
(GameObject* parent) {return new PlayerController(parent); });

PlayerController::PlayerController(GameObject* parent)
	: Component(parent)
{
	parent->get_source().read_properties("PlayerController", mouseMinDistance_, mouseFarDistance_,
		speed_, speedAdjust_, deceleration_);
}

void PlayerController::update(float dt)
{

}

Vector2 PlayerController::ParseMouse()
{
	Vector2 velocity;
	//float dist = Util::Distance(Vector2(Mouse::Get_Pos().x, Mouse::Get_Pos().y), get_parent()->)
	return velocity;
}