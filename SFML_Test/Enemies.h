#pragma once
#include <SFML\Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Enemies
{
private:

	unsigned pointCount;
	sf::CircleShape shape; // sprite

	// ADD NEW TEXTURE & SPRITE --> Yellow Flappy
	sf::Texture enemyTexture;
	sf::RectangleShape  enemySprite;


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
	void initialTexture(sf::Texture*& texture);
	void initialSprite();
	

public:
	Enemies(float posX, float posY);

	virtual ~Enemies();


	// access
	const sf::FloatRect getBounds() const;

	const int& getPoints() const;

	const int& getDamage() const;

	// functions


	void update();
	void render(sf::RenderTarget& target);
};


