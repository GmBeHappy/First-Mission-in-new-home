#include "Bullet.h"


Bullet::Bullet(sf::Texture* texture, sf::Vector2f curveVelocity, float maxSpeed):
	curveVelocity(0.0f,0.0f),maxSpeed(15.0f)
{
	this->shape.setTexture(*texture);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
