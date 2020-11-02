
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Animation.h"


class Player
{
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float movementSpeed;
	bool faceRight;
	/*private function*/
	void initialAnimation();
	void initialTexture();
	void initialSprite();

public:
	Player(sf::Texture* &texture, sf::Vector2u imageCount, float switchTime, float speed);
	virtual ~Player();

	void update(float deltatime);
	void render(sf::RenderTarget& target);

};

