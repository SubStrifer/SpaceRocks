#pragma once

#include "ecm.h"
#include "cmp_physics.h"
#include "maths.h"
#include <Box2D\Dynamics\b2Fixture.h>
#include "..\bullet_factory.h"
#include "cmp_bullet.h"

class ShipComponent : public Component {

public:
	ShipComponent() = delete;
	explicit ShipComponent(Entity* d, const float speed, const float angularSpeed, const float reload);
	void setBullet(float damage, unsigned int id);
	Bullet getBullet() { return _bullet; }
	void render() override { }
	void update(double dt) override;
	void thrust(double dt);
	void rotate(bool right);
	void shoot();

	~ShipComponent() override = default;

protected:
	float _speed;
	float _angularSpeed;
	float _reload;
	float _time;
	Bullet _bullet = {1.0f, 14};

	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<SpriteComponent> _thrusterSpriteComponent;
};