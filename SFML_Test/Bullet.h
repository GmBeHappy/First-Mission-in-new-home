#pragma once
#include<SFML/Graphics.hpp>

class Bullet
{
private:

	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;


public:
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//access
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

