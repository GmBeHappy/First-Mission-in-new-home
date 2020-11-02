#include "Background.h"

void Background::bgTexture()
{
	/*load texture pilot picture file*/
	if (!this->bgtexture.loadFromFile("Textures/bg.jpg"))
	{
		std::cout << "ERROR::SKY::INITIALTEXTURE::could not load." << "\n";
	}
}

void Background::bgSprite()
{
	/*set texture to sprite*/
	this->bgsprite.setTexture(this->bgtexture);
}

Background::Background()
{
	this->bgTexture();
	this->bgSprite();

}

Background:: ~Background()
{

}

void Background::update()
{

}

void Background::render(sf::RenderTarget& target)
{
	target.draw(this->bgsprite);
}
