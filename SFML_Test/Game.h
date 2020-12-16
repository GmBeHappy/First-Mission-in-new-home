#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
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

	std::string playerName = "";
	bool isTypeName = false;
	
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
	sf::RectangleShape restartHitbox;
	sf::Text* backToMenu;
	sf::RectangleShape endingPlan;

	// Time
	float deltaTime;
	sf::Clock* clock;
	sf::Clock* clocktime;
	sf::Time* time;
	unsigned int showtime;

	// Menu
	MainMenu* mainMenu;
	sf::Mouse* mouse;
	bool isEnding = false;

	// SOUND hit
	sf::SoundBuffer bufferHit;
	sf::Sound hitSound;

	// BG music
	sf::Music music;
	sf::Music menuMusic;

	// Take damage
	sf::SoundBuffer buffHurt;
	sf::Sound soundHurt;

	// game over haha
	sf::SoundBuffer bufflol;
	sf::Sound haha;

	// SCORE
	int points;
	int save_point;
	int numShield = 3;
	bool haveShield = false;

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
	void initialBGSound();
	void initialSound();

	void clearAllEnemies();

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
	void updateAndSaveScore(std::string playerName, int score, int time);

	void updateNameInput();

	void update();
	void render();
};

