#include "Player.h"

void Player::initialBulletTexture()
{
	
}


Player::Player(sf::RenderWindow* window,sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Mouse* mouse): 
	animation(texture, imageCount, switchTime)
{
	this->movementSpeed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(150.0f, 150.0f));
	body.setOrigin(body.getSize()/2.0f);
	body.setPosition(this->spawnPoint);
	body.setFillColor(sf::Color::Red);
	
	this->clock = new sf::Clock;
	this->time = new sf::Time;

	this->initialBulletTexture();
	
	this->window = window;
	this->mouse = mouse;
	//body.setOrigin(sf::Vector2f(-250.0f, -450.0f));

	body.setTexture(texture);
	
}


Player:: ~Player()
{
	
}


void Player::update(float deltatime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	this->time = &this->clock->getElapsedTime();
	this->showtime = this->time->asSeconds();
	
	//printf("%llu\n", this->showtime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		if (body.getPosition().x > 0) {
			movement.x -= movementSpeed * deltatime;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (body.getPosition().x < 7521) {
			movement.x += movementSpeed * deltatime;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (body.getPosition().y > 0) {
			movement.y -= movementSpeed * deltatime;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (body.getPosition().y < 4234) {
			movement.y += movementSpeed * deltatime;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (body.getPosition().x > 0) {
			movement.x -= 130 * deltatime;
		}
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (body.getPosition().x < 7521) {
			movement.x += 130 * deltatime;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (body.getPosition().y > 0) {
			movement.y -= 130 * deltatime;
		}
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (body.getPosition().y < 4234) {
			movement.y += 130 * deltatime;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
		
	}

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
