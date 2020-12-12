#pragma once
#include<SFML/Graphics.hpp>

class Bullet
{
private:
	
	sf::Texture* texture;
	

public:
	float maxSpeed;
	sf::Sprite shape;
	sf::Vector2f curveVelocity;
	Bullet(sf::Texture* texture, sf::Vector2f curveVelocity,float maxSpeed);
		
	virtual ~Bullet();
	void update();
	void render(sf::RenderTarget* target);
};

