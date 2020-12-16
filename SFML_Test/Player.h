
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
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

	// Window
	sf::RenderWindow* window;
	
	// Movement
	unsigned int row;
	float movementSpeed;
	bool faceRight;
	
	/*private function*/
	void initialBodyHitbox();
	void updateHitbox();
	void initialVariables();
	void initObject();
	void updateMovement(float deltatime);
	

public:
	Player(sf::RenderWindow* window, sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed);
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
	void finishAttack();
	void updateAttack();
	void reloadCooldown();
	void isFinishAttack();
	const bool getFaceRight();
	void reset();
	
	// update and render
	void update(float deltatime);
	void render(sf::RenderTarget& target);

};

