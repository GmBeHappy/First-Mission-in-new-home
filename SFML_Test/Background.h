#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
class Background
{
private:
	sf::Sprite  bgsprite;
	sf::Texture bgtexture;

	/*private function*/
	void bgTexture();
	void bgSprite();

public:
	Background();
	virtual ~Background();

	/*FUNCTIONS*/

	void update();
	void render(sf::RenderTarget& target);

};

