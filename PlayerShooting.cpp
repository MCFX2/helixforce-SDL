#include "PlayerShooting.h"
#include "ComponentRegistry.h"
#include "Physics.h"
#include "MathUtils.h"

REGISTER_COMPONENT("PlayerShooting", PlayerShooting);

REGISTER_SIMPLE_PROPERTY(PlayerShooting, "ShootKey", ShootKey);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "AnimeShipKey", AnimeShipKey);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "ReaganShipKey", ReaganShipKey);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "ScoutShipKey", ScoutShipKey);

REGISTER_SIMPLE_PROPERTY(PlayerShooting, "BulletSpawnOffset", BulletSpawnOffset);

REGISTER_SIMPLE_PROPERTY(PlayerShooting, "BulletSpeedAnime", BulletSpeedAnime);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "BulletFireDelayAnime", BulletFireDelayAnime);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "BulletSpreadAnime", BulletSpreadAnime);

REGISTER_SIMPLE_PROPERTY(PlayerShooting, "MachoBombFireDelay", MachoBombFireDelay);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "MachoBombVelocity", MachoBombVelocity);

REGISTER_SIMPLE_PROPERTY(PlayerShooting, "RandalFireDelay", RandalFireDelay);
REGISTER_SIMPLE_PROPERTY(PlayerShooting, "RandalFireSpeed", RandalFireSpeed);

PlayerShooting::PlayerShooting(GameObject* parent) : Component(parent)
{
}

void PlayerShooting::start()
{
	transform = get_component<Transform>();
	ScoutShootingOffset = transform->translation - Vector2(57, 52);
}

void PlayerShooting::Shoot()
{
	if (CurrentShip == Ship::Anime)
	{
		if (TimeSinceLastBullet >= BulletFireDelayAnime)
		{
			GameObject* n_bullet = new GameObject("animebullet.dat", get_parent()->get_level());
			n_bullet->get_component<Transform>()->translation = transform->translation + BulletSpawnOffset;
			float spread_angle = Util::Random(-90, 90) * BulletSpreadAnime;
			float velY = BulletSpeedAnime * BulletSpeedAnime * sin(Util::Radians(spread_angle));
			float velX = BulletSpeedAnime * BulletSpeedAnime * cos(Util::Radians(spread_angle));
			n_bullet->get_component<Physics>()->velocity = Vector2(velX, velY);
			TimeSinceLastBullet = 0;
		}
	}
}

void PlayerShooting::CheckKeyboard()
{
	if (Keyboard::Get_KeyPressed(ShootKey))
	{
		Shoot();
	}
}

void PlayerShooting::CheckMouse()
{

}

void PlayerShooting::update(float dt)
{
	CheckMouse();
	CheckKeyboard();
	TimeSinceLastBullet += dt;
	++BombCooldown;
}