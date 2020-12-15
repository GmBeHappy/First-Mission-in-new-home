#include "Enemies.h"

void Enemies::initialVariables()
{
	this->pointCount = rand() % 8 + 3; // is 0->7 : min 3 point, max 10 point
	this->type = 0;
	this->hpmax = static_cast<int>(this->pointCount);
	this->hp = this->hpmax;
	this->damage = 5;
	this->points = 50;

	this->speed = 1.f;
}

void Enemies::initialSprite()
{
	this->enemyHitbox.setSize(sf::Vector2f(50.0f, 50.0f));
	this->enemyHitbox.setOutlineColor(sf::Color::Red);
	this->enemyHitbox.setFillColor(sf::Color::Transparent);
	this->enemyHitbox.setOutlineThickness(2.0f);

	this->enemySprite.setSize(sf::Vector2f(80.0f, 80.0f));
	this->enemySprite.setTextureRect(animation.uvRect);
}

void Enemies::updateHitbox()
{
	this->enemyHitbox.setPosition(sf::Vector2f(this->enemySprite.getPosition().x + 15.0f , this->enemySprite.getPosition().y + 5.0f));
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
	this->updateHitbox();
	this->enemySprite.setTextureRect(animation.uvRect);
	if (abs(player.x - this->enemySprite.getPosition().x) <= 1000.0f)
	{
		if (player.x > this->enemySprite.getPosition().x)
		{
			this->enemySprite.move(this->speed, 0.f);
		}
		 if (player.x < this->enemySprite.getPosition().x)
		{
			this->enemySprite.move(-this->speed, 0.f);
		}
		if (player.y > this->enemySprite.getPosition().y)
		{
			this->enemySprite.move(0.0f, this->speed);

		}
		 if (player.y < this->enemySprite.getPosition().y)
		{

			this->enemySprite.move(0.0f, -this->speed);
		}
	}
	//this->enemySprite.move(-this->speed, 0.f);

}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
		target.draw(this->enemyHitbox);
	}
}
