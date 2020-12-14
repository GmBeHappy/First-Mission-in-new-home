#include "Player.h"

void Player::initialBodyHitbox()
{
	this->bodyHitbox.setSize(sf::Vector2f(85.0f, 105.0f));
	this->bodyHitbox.setOutlineColor(sf::Color::Green);
	this->bodyHitbox.setFillColor(sf::Color::Transparent);
	this->bodyHitbox.setOutlineThickness(2.0f);
}

void Player::updateHitbox()
{
	this->bodyHitbox.setPosition(sf::Vector2f(this->body.getPosition().x - 50.0f ,this->body.getPosition().y - 50.0f));
}

void Player::initialVariables()
{
	
	// attack per time
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	// HP
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initObject()
{
	//this->body.setOutlineColor(sf::Color::Green);
	//this->body.setOutlineThickness(2.0f);
	this->spaceship.setSize(sf::Vector2f(245.0f, 255.0f));
	this->spaceship.setOutlineColor(sf::Color::Green);
	this->spaceship.setFillColor(sf::Color::Transparent);
	this->spaceship.setOutlineThickness(2.0f);
	this->spaceship.setPosition(sf::Vector2f(1490.0f, 2100.0f));
}

void Player::updateMovement(float deltatime)
{
	// update movement
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
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

	// animation
	if (movement.x == 0.0f) { // IDLE
		row = 0;
	}
	else { // walking ar running
		row = 1;
		if (movement.x > 0.0f) {
			faceRight = true;  // face right
		}
		else {
			faceRight = false; // face left
		}
	}
	// update animation
	animation.Update(row, deltatime, faceRight);
	body.setTextureRect(animation.uvRect);

	// update player movement
	body.move(movement);
}

Player::Player(sf::RenderWindow* window,sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Mouse* mouse): 
	animation(texture, imageCount, switchTime)
{
	this->movementSpeed = speed;
	row = 0;
	faceRight = true;

	// initial player
	body.setSize(sf::Vector2f(150.0f, 150.0f));
	body.setOrigin(body.getSize()/2.0f);
	body.setPosition(this->spawnPoint);
	body.setTexture(texture);
	
	this->initObject();
	this->initialBodyHitbox();
	
	this->window = window;
	this->mouse = mouse;

}

Player:: ~Player()
{
	
}

const sf::Vector2f& Player::getPos() const
{
	return this->body.getPosition();
}

sf::FloatRect Player::getBounds() const
{
	return this->bodyHitbox.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->body.setPosition(pos);
}

void Player::setPosition(const float x, float y)
{
	this->body.setPosition(x, y);
}

void Player::setHP(const int hp)
{
	this->hp = hp;
}

void Player::loseHP(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
	{
		this->hp = 0;
	}

	if (this->hp > 100)
	{
		this->hp = 100;
	}
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += 0.25f;
	}
}

void Player::update(float deltatime)
{
	this->updateMovement(deltatime);
	this->updateAttack();
	this->updateHitbox();

	// simple collision check
	if (!body.getGlobalBounds().intersects(this->spaceship.getGlobalBounds())) {
		printf("Collision!!\n");
	}
}

void Player::render(sf::RenderTarget& target)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
		target.draw(this->spaceship);
		target.draw(this->bodyHitbox);
	}
	target.draw(body);
	
}
