#include "PlayerController.h"

#include "Vector.h"
#include "MathUtils.h"

#include "mouse.h"

#include "GameObject.h"

#include "fileman.h"

#include "ComponentRegistry.h"

#include "Transform.h"
#include "Physics.h"

REGISTER_COMPONENT("PlayerController", PlayerController);
REGISTER_SIMPLE_PROPERTY(PlayerController, "MouseMinDistance", mouseMinDistance_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "MouseFarDistance", mouseFarDistance_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "Speed", speed_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "SpeedMultipliers", speedAdjust_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "Deceleration", deceleration_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "MaxLVelocity", maxLVelocity_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "MaxRVelocity", maxRVelocity_);
REGISTER_SIMPLE_PROPERTY(PlayerController, "MaxVVelocity", maxVVelocity_);

PlayerController::PlayerController(GameObject* parent)
	: Component(parent)
{
}

void PlayerController::start()
{
	physics = get_component<Physics>();
	transform = get_component<Transform>();
}

void PlayerController::update(float dt)
{
	Accelerate();
	ClampPosition();
	ClampVelocity();
}

void PlayerController::ClampPosition()
{
	Util::ClampInPlace<float>(transform->translation.x, 0, 1280);
	Util::ClampInPlace<float>(transform->translation.y, 0, 720);
}

void PlayerController::ClampVelocity()
{
	Vector2 translation = transform->translation;
	Vector2 correctiveFactor = Util::Abs(Vector2::normalized(translation - Mouse::Get_LastPos()));
	Util::ClampInPlace(physics->velocity.x, -maxLVelocity_, maxRVelocity_);
	Util::ClampInPlace(physics->velocity.y, -maxVVelocity_, maxVVelocity_);
	physics->velocity *= correctiveFactor;
}

void PlayerController::Accelerate()
{
	//in the future this may be updated to support other control options
	physics->velocity += ParseMouse();
	Decelerate();
}

void PlayerController::Decelerate()
{
	Physics* phys = get_component<Physics>();
	if (Util::Abs(phys->velocity.x) < deceleration_.x)
	{ //to avoid sperging out we clear velocity when value is too small
		phys->velocity.x = 0;
	}
	else if (phys->velocity.x > 0)
	{ //accelerate towards zero otherwise
		phys->velocity.x -= deceleration_.x;
	}
	else
	{
		phys->velocity.x += deceleration_.x;
	}
	//repeat with Y values
	if (Util::Abs(phys->velocity.y) < deceleration_.y)
	{ //to avoid sperging out we clear velocity when value is too small
		phys->velocity.y = 0;
	}
	else if (phys->velocity.y > 0)
	{ //accelerate towards zero otherwise
		phys->velocity.y -= deceleration_.y;
	}
	else
	{
		phys->velocity.y += deceleration_.y;
	}
}

//calculate target movement vector assuming mouse control
Vector2 PlayerController::ParseMouse()
{
	Vector2 velocity(0);
	//always cache the result of get_component(), it is expensive.
	Vector2 translation = transform->translation;
	float dist = Vector2::distance(translation, Mouse::Get_LastPos());

	float distRatio = Util::Clamp<float>(dist / mouseFarDistance_, 0, 1);

	//determine direction to move and then calculate adjustment
	//there is probably a cleaner way to do this calculation but lazy
	if (translation.x > Mouse::Get_LastPos().x)
	{
		velocity.x -= speedAdjust_.x * speed_ * distRatio;
	}
	else
	{
		velocity.x += speedAdjust_.x * speed_ * distRatio;
	}

	if (translation.y > Mouse::Get_LastPos().y)
	{
		velocity.y -= speedAdjust_.y * speed_ * distRatio;
	}
	else
	{
		velocity.y += speedAdjust_.y * speed_ * distRatio;
	}

	return velocity;
}