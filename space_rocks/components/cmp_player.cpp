#include "cmp_player.h"
#include "..\input.h"
#include <stdio.h>

PlayerComponent::PlayerComponent(Entity* p, const int player) : Component(p)
{
	_player = player;
	_shipComponent = _parent->getComponents<ShipComponent>()[0];
}

PlayerComponent::~PlayerComponent() {
	_shipComponent.reset();
}

// Update loop
void PlayerComponent::update(double dt)
{
	if (suppressPlayerControl)
	{
		_parent->getComponents<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(0.0f, 0.0f));
		return;
	}

	// Moving and shooting
	if (Input::isKeyDown(Input::KeyCode::P1_THRUST))
	{
		_shipComponent->thrust(dt);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_LEFT))
	{
		_shipComponent->rotate(false);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_RIGHT))
	{
		_shipComponent->rotate(true);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_FIRE))
	{
		_shipComponent->shoot();
	}
}

// Checks if player has enough coins
bool PlayerComponent::tryPurchase(int cost)
{
	if (_coins >= cost)
	{
		audioManager.playSound("upgrade_purchased_2");
		removeCoins(cost);
		return true;
	}
	else
	{
		//Play audio
		audioManager.playSound("not_enough_coins");
		return false;
	}
}

// Tries to upgrade player damage (bullet)
void PlayerComponent::tryUpgradeDamage()
{
	//Get current bullet
	Bullet curBullet = _shipComponent->getBullet();

	//If allready maxed (shouldn't ever run as button should be greyed out.)
	if(curBullet._id == 34)
		return;

	//Else try purchase
	if(tryPurchase(curBullet._id + 4))
		_shipComponent->setBullet(curBullet._damage + 0.5f, curBullet._id + 10);
}

//Try to purchase and upgrade the Weapon's Rate of Fire
void PlayerComponent::tryUpgradeROF()
{
	//If reload time > 0.1 and can afford cost, upgrade.
	if (_shipComponent->getReload() > 0.1f && tryPurchase(80 - 100 * _shipComponent->getReload()))
		_shipComponent->setReload(_shipComponent->getReload() - 0.1f);
}
