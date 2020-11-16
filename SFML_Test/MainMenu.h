#pragma once
#include <SFML\Graphics.hpp>
#include<SFML/System.hpp>
#include "Background.h"

class MainMenu
{
private:
	sf::Texture* menuBackgroung;
	sf::Font* font;
	sf::Text* playBtn;
	sf::Text* scoreBtn;
	sf::Text* exitBtn;
	sf::Text* howtoBtn;
	Background* background;
	sf::RenderWindow* window;
	sf::Mouse* mouse;

	void initialTexture();
	void initialFont();
	void initialText();

public:
	MainMenu(sf::RenderWindow* window, sf::Mouse* mouse);
	virtual ~MainMenu();

	bool isPlay=false;

	void update();
	void render();
};

