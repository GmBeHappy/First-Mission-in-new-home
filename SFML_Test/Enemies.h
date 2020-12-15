#pragma once
#include <SFML\Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include "EnemiesAnimatoin.h"

class Enemies
{
private:

	unsigned pointCount;
	sf::Texture enemyTexture;
	sf::RectangleShape  enemySprite;
	sf::RectangleShape  enemyHitbox;
	EnemiesAnimatoin animation;

	unsigned int row;
	float movementSpeed;
	bool faceRight=false;

	int type;
	int hp;
	int hpmax;
	int damage;
	int points;
	float speed;

	float posX;
	float posY;
	int ability;

	void initialVariables();
	void initialSprite();
	void updateHitbox();

public:
	Enemies(float posX, float posY, sf::Texture*& texture, sf::Vector2u imageCount, float switchTime);

	virtual ~Enemies();


	// access
	const sf::FloatRect getBounds() const;

	const int& getPoints() const;

	const int& getDamage() const;

	// functions

	
	void update(float deltatime,sf::Vector2f player);
	void render(sf::RenderTarget& target);
};


