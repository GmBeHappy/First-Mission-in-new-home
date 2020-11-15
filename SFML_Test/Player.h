
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Animation.h"

class Player
{
private:
	sf::RectangleShape body;
	sf::Clock* clock;
	sf::Time* time;
	Animation animation;
	//std::ostringstream showtime;
	unsigned long long showtime;
	unsigned int row;
	float movementSpeed;
	bool faceRight;
	float suitPower=2000;
	/*private function*/
	void initialAnimation();
	void initialTexture();
	void initialSprite();

public:
	Player(sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed);
	

	sf::Vector2f GetPosition() {
		return body.getPosition();
	}

	virtual ~Player();

	void update(float deltatime);
	void render(sf::RenderTarget& target);

};

