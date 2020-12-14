
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Animation.h"
#include <iostream>
#include <map>

class Player
{
private:
	// player model
	sf::RectangleShape body;
	sf::RectangleShape bodyHitbox;
	sf::RectangleShape spaceship;
	Animation animation;

	// player variable
	sf::Vector2f spawnPoint = { 1850.0f, 2200.0f };

	// HP
	int hp;
	int hpMax;

	// attack & max speed
	float attackCooldown;
	float attackCooldownMax;

	// Mouse
	sf::Mouse* mouse;
	
	// Window
	sf::RenderWindow* window;
	
	// Movement
	unsigned int row;
	float movementSpeed;
	bool faceRight;
	float suitPower=2000;
	
	/*private function*/
	void initialBodyHitbox();
	void updateHitbox();
	void initialVariables();
	void initObject();
	void updateMovement(float deltatime);
	

public:
	Player(sf::RenderWindow* window, sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Mouse* mouse);
	virtual ~Player();

	// Access
	const sf::Vector2f& getPos() const;
	sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}

	// modify
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, float y);
	void setHP(const int hp);
	void loseHP(const int value);

	// attack
	const bool canAttack();
	void updateAttack();
	
	// update and render
	void update(float deltatime);
	void render(sf::RenderTarget& target);

};

