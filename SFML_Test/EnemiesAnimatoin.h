#pragma once
#include <SFML\Graphics.hpp>
class EnemiesAnimatoin
{
public:
	EnemiesAnimatoin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	virtual ~EnemiesAnimatoin();

	void Update(int row, float deltaTime, bool faceRight);

	sf::IntRect uvRect;
	int imageCountt = 0;
	void updateSwitchTime(float newSwitchTime);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;


	float totalTime;
	float switchTime;
};

