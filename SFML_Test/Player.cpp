#include "Player.h"

Player::Player(sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->movementSpeed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(140.0f, 140.0f));
	body.setTexture(texture);
	
}

Player:: ~Player()
{
	
}


void Player::update(float deltatime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= movementSpeed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += movementSpeed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= movementSpeed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += movementSpeed * deltatime;

	if (movement.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;
		if (movement.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	animation.Update(row, deltatime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(body);
}
