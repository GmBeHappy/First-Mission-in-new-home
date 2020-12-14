#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	virtual ~Animation();

	void Update(int row, float deltaTime, bool faceRight);

	sf::IntRect uvRect;
	int imageCountt=0;
	void updateSwitchTime(float newSwitchTime);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	
	float totalTime;
	float switchTime;
};

