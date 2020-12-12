
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Animation.h"
#include "Bullet.h"
#include <iostream>
#include <map>

class Player
{
private:
	sf::RectangleShape body;
	sf::Clock* clock;
	sf::Time* time;
	Animation animation;
	Bullet* b1;

	sf::Vector2f spawnPoint = { 1800.0f, 2200.0f };

	std::vector<Bullet> bullets;
	

	sf::Texture* bulletTexture;

	sf::Vector2f playerCenter;
	sf::Vector2f mousePosition;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalize;

	sf::Mouse* mouse;
	
	sf::RenderWindow* window;
	//std::ostringstream showtime;
	unsigned long long showtime;
	unsigned int row;
	float movementSpeed;
	bool faceRight;
	float suitPower=2000;
	/*private function*/
	void initialBulletTexture();
	

public:
	Player(sf::RenderWindow* window, sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Mouse* mouse);
	
	
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}

	virtual ~Player();

	void update(float deltatime);
	void render(sf::RenderTarget& target);

};

