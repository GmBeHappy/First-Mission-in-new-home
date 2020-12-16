#pragma once
#include <SFML\Graphics.hpp>
#include<SFML/System.hpp>
#include "Background.h"
//#include "Plane.h"
#include <fstream>
#include <iostream>

class MainMenu
{
private:
	//Plane* leaderboard;
	sf::Texture* menuBackgroung;
	sf::Font* font;
	sf::Text* playBtn;
	sf::Text* scoreBtn;
	sf::Text* exitBtn;
	sf::Text* howtoBtn;
	Background* background;
	sf::RenderWindow* window;
	sf::Mouse* mouse;
	sf::Text* name;
	
	sf::RectangleShape textBox;
	
	sf::RectangleShape shape;
	sf::Text* header;
	sf::Text* content;
	

	void initialTexture();
	void initialFont();
	void initialText();
	void initialNameInput();
	void initialReadScore();

public:
	MainMenu(sf::RenderWindow* window, sf::Mouse* mouse);
	virtual ~MainMenu();
	sf::Text* nameInput;
	bool isPlay=false;
	bool isNameInput = false;
	bool isFinishNameInput = false;
	bool toggleLeaderboard = false;
	void update();
	void render();
};

