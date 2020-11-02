#pragma once
#include "Player.h"
#include "Background.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Texture* playerTexture;
	/*pilot*/
	Player* player;
	float deltaTime;
	sf::Clock* clock;
	Background* background;
	void initialWindow();
	void initialPlayer();
	void initialBackground();
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

