#pragma once

#include "Component.h"
#include "keyboard.h"
#include "Transform.h"
#include "Vector.h"


class PlayerShooting : public Component
{
public:
	PlayerShooting(GameObject* parent);

	void update(float) override;
	void start() override;

	//properties
	unsigned ShootKey{ SDL_SCANCODE_SPACE };
	unsigned AnimeShipKey{ '1' };
	//unsigned MachoCheeseShipKey{ '2' };
	unsigned ReaganShipKey{ '2' };
	unsigned ScoutShipKey{ '3' };

	Vector2 BulletSpawnOffset{ 75, 0 };
	float BulletSpeedAnime{ 12 };
	float BulletFireDelayAnime{ 0.1f };
	float BulletSpreadAnime{ 0.02f };

	unsigned MachoBombFireDelay{ 240 };
	float MachoBombVelocity{ 5 };

	unsigned RandalFireDelay{ 4 };
	float RandalFireSpeed{ 8 };

private:
	Transform* transform{ nullptr };

	float TimeSinceLastBullet{ 0 };
	unsigned BombCooldown{ 0 };
	enum class Ship {
		Anime,
	} CurrentShip{ Ship::Anime };
	Vector2 ScoutShootingOffset{ 0 };

	void Shoot();
	void ChangeShip(Ship);
	void CheckKeyboard();
	Ship NextShip();
	Ship PrevShip();
	void CheckMouse();

};