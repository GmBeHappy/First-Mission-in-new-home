#pragma once
#include <iostream>
#include<cstdlib>
#include <ctime>
#include "Player.h"
#include "Background.h"
#include "MainMenu.h"
#include "Bullet.h"
#include "Enemies.h"


class Game
{
private:
	// Window
	sf::RenderWindow* window;

	// Player
	sf::Texture* playerTexture;
	Player* player;
	sf::RectangleShape playerHpBar;			//MAX
	sf::RectangleShape playerHpBarBack;		// 
	
	// Background
	sf::Texture* gameBackgroung;
	Background* background;

	// View
	sf::View* view;

	// GUI
	sf::Font* font;
	sf::Text* playTime;
	sf::Text* playerScore;
	sf::Text* ending;
	sf::Text* restart;
	sf::Text* backToMenu;
	sf::RectangleShape endingPlan;

	// Time
	float deltaTime;
	sf::Clock* clock;
	sf::Clock* clocktime;
	sf::Time* time;
	unsigned long long showtime;

	// Menu
	MainMenu* mainMenu;
	sf::Mouse* mouse;
	bool isEnding = false;

	// SCORE
	int points;
	int save_point;
	int numShield = 3;
	bool haveShield = false;
	std::string playerName;

	// Bullet
	std::vector<Bullet*> bullets;
	sf::Texture* bulletTexture;

	// Enemies
	sf::Texture* enemyTexture;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	std::vector<Enemies*> enemies;

	// funtion
	void initialWindow();
	void initialPlayer();
	void initialView();
	void initialBackground();
	void initialTime();
	void initialFont();
	void initialGUI();
	void initialMainMenu();
	void initialMouse();
	void initialBulletTexture();
	void initialEnemies();

public:
	Game();
	virtual ~Game();

	/*FUNCTIONS*/
	void run();
	void updatePollEvents();
	void updateBullets();
	void updateMousePosition();
	void updateTimeScore();
	void updateTime();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	void updateEndGame();
	void updateEnding();

	void update();
	void render();
};

