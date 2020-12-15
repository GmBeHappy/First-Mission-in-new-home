#include "Enemies.h"

void Enemies::initialVariables()
{
	this->pointCount = rand() % 8 + 3; // is 0->7 : min 3 point, max 10 point
	this->type = 0;
	this->hpmax = static_cast<int>(this->pointCount);
	this->hp = this->hpmax;
	this->damage = 20;
	this->points = 50;

	this->speed = 2.f;
}

void Enemies::initialSprite()
{
	this->enemySprite.setSize(sf::Vector2f(80.0f, 80.0f));
	this->enemySprite.setOutlineColor(sf::Color::Green);
	//this->enemySprite.setFillColor(sf::Color::Transparent);
	this->enemySprite.setOutlineThickness(2.0f);
	this->enemySprite.setTextureRect(animation.uvRect);
}

Enemies::Enemies(float posX, float posY, sf::Texture*& texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
	faceRight = true;
	this->initialVariables();
	this->initialSprite();
	this->enemySprite.setTexture(texture);
	this->enemySprite.setPosition(posX, posY);
}

Enemies::~Enemies()
{
}

const sf::FloatRect Enemies::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}

const int& Enemies::getPoints() const
{
	return this->points;
}

const int& Enemies::getDamage() const
{
	return this->damage;
}

void Enemies::update(float deltatime,sf::Vector2f player)
{
	this->animation.Update(2, deltatime, faceRight);
	this->enemySprite.setTextureRect(animation.uvRect);
	if (abs(player.x - this->enemySprite.getPosition().x) <= 500.0f)
	{
		if (player.x > this->enemySprite.getPosition().x)
		{
			this->enemySprite.move(this->speed, 0.f);
			faceRight = 1;

		}
		else if (player.x < this->enemySprite.getPosition().x)
		{

			this->enemySprite.move(-this->speed, 0.f);
			faceRight = 0;
		}
		if (player.y > this->enemySprite.getPosition().y)
		{
			this->enemySprite.move(0.0f, this->speed);
			faceRight = 1;

		}
		else if (player.y < this->enemySprite.getPosition().y)
		{

			this->enemySprite.move(0.0f, -this->speed);
			faceRight = 0;
		}
	}
	//this->enemySprite.move(-this->speed, 0.f);

}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
}
