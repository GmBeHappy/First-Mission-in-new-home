#include "Enemies.h"

void Enemies::initialVariables()
{
	this->pointCount = rand() % 8 + 3; // is 0->7 : min 3 point, max 10 point
	this->type = 0;
	this->hpmax = static_cast<int>(this->pointCount);
	this->hp = this->hpmax;
	this->damage = 20;
	this->points = 50;

	this->speed = 7.f;
}

void Enemies::initialTexture(sf::Texture*& texture)
{
	this->enemySprite.setTexture(texture);
}

void Enemies::initialSprite()
{
	this->enemySprite.setSize(sf::Vector2f(80.0f, 80.0f));
	this->enemySprite.setOutlineColor(sf::Color::Green);
	this->enemySprite.setFillColor(sf::Color::Transparent);
	this->enemySprite.setOutlineThickness(2.0f);
}

Enemies::Enemies(float posX, float posY)
{
	this->initialVariables();
	this->initialSprite();

	//this->initialShape();
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

void Enemies::update()
{
	this->enemySprite.move(-this->speed, 0.f);
}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
}
