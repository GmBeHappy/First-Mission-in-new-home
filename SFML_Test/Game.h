#pragma once
#include "Player.h"
#include "Background.h"
#include"MainMenu.h"
#include <iostream>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Texture* playerTexture;
	sf::Texture* gameBackgroung;

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
	MainMenu* mainMenu;

	sf::Mouse* mouse;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//float showtime;

	void initialWindow();
	void initialPlayer();
	void initialView();
	void initialBackground();
	void initialTime();
	void initialFont();
	void initialPlaytime();
	void initialMainMenu();
	void initialMouse();

public:
	Game();
	virtual ~Game();

	/*FUNCTIONS*/
	void run();
	void updatePollEvents();
	void updateInput();
	void updateMousePosition();

	void update();
	void render();
};

