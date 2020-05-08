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

PlayerController::PlayerController(GameObject* parent)
	: Component(parent)
{
	parent->get_source().read_properties("PlayerController", mouseMinDistance_, mouseFarDistance_,
		speed_, speedAdjust_, deceleration_, maxLVelocity_, maxRVelocity_, maxVVelocity_);
}

void PlayerController::update(float dt)
{
	Accelerate();
	ClampPosition();
	ClampVelocity();
}

void PlayerController::ClampPosition()
{

}

void PlayerController::ClampVelocity()
{
	Vector2 translation = get_component<Transform>()->translation;
	Vector2 correctiveFactor = Util::Abs(Vector2::normalized(translation - Mouse::Get_LastPos()));
	Physics* phys = get_component<Physics>();
	Util::ClampInPlace(phys->velocity.x, -maxLVelocity_, maxRVelocity_);
	Util::ClampInPlace(phys->velocity.y, -maxVVelocity_, maxVVelocity_);
	phys->velocity *= correctiveFactor;
}

void PlayerController::Accelerate()
{
	//in the future this may be updated to support other control options
	get_component<Physics>()->velocity += ParseMouse();
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
	Vector2 translation = get_component<Transform>()->translation;
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