#include "EnemiesAnimatoin.h"

EnemiesAnimatoin::EnemiesAnimatoin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	imageCountt = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

EnemiesAnimatoin::~EnemiesAnimatoin()
{
}

void EnemiesAnimatoin::Update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;


	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		this->imageCountt++;

		if (currentImage.x >= imageCount.x) {
			this->imageCountt = 0;
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}

void EnemiesAnimatoin::updateSwitchTime(float newSwitchTime)
{
	this->switchTime = newSwitchTime;
}
