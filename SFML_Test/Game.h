#pragma once
#include "Player.h"
#include "Background.h"
#include <iostream>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Texture* playerTexture;
	sf::View* view;
	sf::Font* font;
	sf::Text* playTime;
	/*pilot*/
	Player* player;
	float deltaTime;
	sf::Clock* clock;
	sf::Clock* clocktime;
	Background* background;
	sf::Time* time;
	unsigned long long showtime;
	//float showtime;

	void initialWindow();
	void initialPlayer();
	void initialView();
	void initialBackground();
	void initialTime();
	void initialFont();
	void initialPlaytime();

public:
	Game();
	virtual ~Game();

	/*FUNCTIONS*/
	void run();
	void updatePollEvents();
	void updateInput();

	void update();
	void render();
};

