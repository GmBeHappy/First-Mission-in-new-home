#include "Game.h"
#include <time.h>

//setup game window default config
void Game::initialWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "First mission in New Home", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initialPlayer()
{
	this->playerTexture = new sf::Texture;
	this->playerTexture->loadFromFile("Textures/player.png");
	this->player = new Player(this->window,this->playerTexture, sf::Vector2u(5, 5), 0.3f, 100.0f);
	this->clock = new sf::Clock;
}

void Game::initialView()
{
	this->view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));

}

void Game::initialBackground()
{	
	this->gameBackgroung = new sf::Texture;
	this->gameBackgroung->loadFromFile("Textures/bg.jpg");
	this->background = new Background(this->gameBackgroung);
}

void Game::initialTime()
{
	this->time = new sf::Time;
	this->clocktime = new sf::Clock;
	srand(std::time(NULL));
}

void Game::initialFont()
{
	this->font = new sf::Font;
	if(!this->font->loadFromFile("Cloud.ttf")){
		printf("Load font fail\n");
	}
}

void Game::initialGUI()
{
	this->playTime = new sf::Text();
	this->playTime->setPosition(sf::Vector2f(0.0f,0.0f));
	this->playTime->setCharacterSize(40);
	this->playTime->setFont(*this->font);

	this->playerScore = new sf::Text();
	this->playerScore->setPosition(sf::Vector2f(0.0f, 20.0f));
	this->playerScore->setCharacterSize(40);
	this->playerScore->setFont(*this->font);

	// initial HP
	this->playerHpBar.setSize(sf::Vector2f(500.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::White);
	this->playerHpBar.setPosition(sf::Vector2f(1150.f, 20.f));
	this->playerHpBar.setOutlineColor(sf::Color::Black);
	this->playerHpBar.setOutlineThickness(2.f);

	this->endingPlan.setSize(sf::Vector2f(700.0f, 800.0f));
	this->endingPlan.setFillColor(sf::Color(25, 25, 25, 200));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	this->ending = new sf::Text();
	this->ending->setPosition(sf::Vector2f(0.0f, 0.0f));
	this->ending->setFillColor(sf::Color::Red);
	this->ending->setCharacterSize(80);
	this->ending->setFont(*this->font);
	this->ending->setString("GAME OVER");

	this->restart = new sf::Text();
	this->restart->setPosition(sf::Vector2f(0.0f, 0.0f));
	this->restart->setCharacterSize(60);
	this->restart->setFont(*this->font);
	this->restart->setString("press R to restart");

	this->restartHitbox.setSize(sf::Vector2f(180.0f, 50.0f));
	this->restartHitbox.setOutlineColor(sf::Color::Red);
	this->restartHitbox.setFillColor(sf::Color::Transparent);
	this->restartHitbox.setOutlineThickness(2.0f);

	this->backToMenu = new sf::Text();
	this->backToMenu->setPosition(sf::Vector2f(0.0f, 0.0f));
	this->backToMenu->setCharacterSize(60);
	this->backToMenu->setFont(*this->font);
	this->backToMenu->setString("press Enter to exit");
}

void Game::initialMainMenu()
{
	this->mainMenu = new MainMenu(this->window,this->mouse);
	
}

void Game::initialMouse()
{
	this->mouse = new sf::Mouse();
}

void Game::initialBulletTexture()
{
	this->bulletTexture = new sf::Texture;
	this->bulletTexture->loadFromFile("Textures/bullet.png");
}

void Game::initialEnemies()
{
	this->enemyTexture = new sf::Texture;
	this->enemyTexture->loadFromFile("Textures/alien.png");
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
}

void Game::clearAllEnemies()
{
	for (auto& enem : this->enemies)
	{
		// delete enemies
		delete enem;

	}
	this->enemies.clear();
}

/*GAME WINDOW*/
Game::Game(){
	this->initialWindow();
	this->initialPlayer();
	this->initialBackground();
	this->initialView();
	this->initialTime();
	this->initialFont();
	this->initialGUI();
	this->initialMainMenu();
	this->initialMouse();
	this->initialBulletTexture();
	this->initialEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->background;
}

/*FUNCTIONS*/
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.Event::type == sf::Event::Closed)
			this->window->close();
		if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack() ) //press Attack = attack; 
		{
			if (this->player->getFaceRight()) {
				this->bullets.push_back(
					new Bullet(
						this->bulletTexture,
						this->player->getPos().x + this->player->getBounds().height / 2.f,
						this->player->getPos().y - 5.0f, 1.f, 0.f, 35.f)
				);
			}
			else {
				this->bullets.push_back(
					new Bullet(
						this->bulletTexture,
						this->player->getPos().x - this->player->getBounds().height / 2.f,
						this->player->getPos().y - 5.0f, -1.f, 0.f, 35.f)
				);
			}
			
			this->player->finishAttack();
			printf("Shooted\n");
			
		}

		if (event.type == sf::Event::TextEntered && !this->mainMenu->isFinishNameInput) {
			switch (event.key.code) {
			case 8:
				if (playerName.size() == 0) {
					break;
				}
				playerName.pop_back();
				this->mainMenu->nameInput->setString(playerName);
				break;
			case 13:
				this->mainMenu->isFinishNameInput = true;
				this->mainMenu->isPlay = true;

			default:
				playerName += event.text.unicode;
				// play sound
				this->mainMenu->nameInput->setString(playerName);
			}
		}
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		// Bulet culling (top screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateMousePosition()
{
	
}

void Game::updateTimeScore()
{
	this->time = &this->clocktime->getElapsedTime();
	this->showtime = this->time->asSeconds();
	this->playTime->setString("Time : " + std::to_string(this->showtime) + "s");
	this->playTime->setPosition(sf::Vector2f(this->player->GetPosition().x - 930.0f, this->player->GetPosition().y - 520.0f));

}

void Game::updateTime()
{
	deltaTime = this->clock->restart().asSeconds();
}

void Game::updateEnemies()
{
	// enemies spawning
	this->enemySpawnTimer += 0.5f;
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		
		//std::cout << "enemy spawn\n";
		float enemyPosY = rand() % ((int)this->player->GetPosition().y)+600.0f;
		float enemyPosX = rand() % ((int)this->player->GetPosition().x)+500.0f;
		/*std::cout << "x : ";
		std::cout << enemyPosX;
		std::cout << "\t";
		std::cout << "y : ";
		std::cout << enemyPosY;
		std::cout << "\n";
		std::cout << "player : ";
		std::cout << "x : ";
		std::cout << this->player->GetPosition().x;
		std::cout << "\t";
		std::cout << "y : ";
		std::cout << this->player->GetPosition().y;
		std::cout << "\n";*/
		this->enemies.push_back(new Enemies(enemyPosY, enemyPosY ,this->enemyTexture,sf::Vector2u(3, 4), 0.3f));
		this->enemySpawnTimer = 0.f;
	}

	// update
	unsigned Fcounter = 0;
	for (auto* enemie : this->enemies)
	{
		enemie->update(deltaTime,this->player->GetPosition());

		//// enemies culling (top screen)
		//if (enemie->getBounds().left < this->window->getSize().y)
		//{
		//	// delete enemies
		//	std::cout << "enemy despawn\n";
		//	delete this->enemies.at(Fcounter);
		//	this->enemies.erase(this->enemies.begin() + Fcounter);
		//}
		//if (enemie->getBounds().left < this->window->getSize().x)
		//{
		//	// delete enemies
		//	std::cout << "enemy despawn\n";
		//	delete this->enemies.at(Fcounter);
		//	this->enemies.erase(this->enemies.begin() + Fcounter);
		//}

		// Enemies & Player colission
		/*else */if (enemie->getBounds().intersects(this->player->getBounds()))
		{
			// delete enemy W H I L E   H I T   T H E   P L A Y E R 
			//if (this->haveShield == false)
			//{
				this->player->loseHP(this->enemies.at(Fcounter)->getDamage());
				delete this->enemies.at(Fcounter);
				this->enemies.erase(this->enemies.begin() + Fcounter);
			//}

			/*else if (this->haveShield == true)
			{
				this->initialShieldSound();
				this->numShield -= 1;
				delete this->enemies.at(Fcounter);
				this->enemies.erase(this->enemies.begin() + Fcounter);
			}*/
		}

		++Fcounter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_removed = false;
		this->enemies[i]->update(deltaTime,this->player->GetPosition());

		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++) // has been shot
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) // IF bullet touch the enemies
			{
				std::cout << "killed\n";
				std::cout << this->points;
				std::cout << "\n";
				this->points += this->enemies[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);

				enemy_removed = true;
			}
		}
	}
}

void Game::updateGUI()
{
	this->playerScore->setString("Score : " + std::to_string(this->points));
	this->playerScore->setPosition(sf::Vector2f(this->player->GetPosition().x - 930.0f, this->player->GetPosition().y - 460.0f));
	
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(500.f * hpPercent, this->playerHpBar.getSize().y));

	this->playerHpBar.setPosition(sf::Vector2f(this->player->GetPosition().x + 400.0f, this->player->GetPosition().y - 500.0f));
	this->playerHpBarBack.setPosition(sf::Vector2f(this->player->GetPosition().x + 400.0f, this->player->GetPosition().y - 500.0f));
	
	this->ending->setPosition(sf::Vector2f(this->player->GetPosition().x - 200.0f, this->player->GetPosition().y - 300.0f));

	this->endingPlan.setPosition(sf::Vector2f(this->player->GetPosition().x -330.0f, this->player->GetPosition().y - 400.0f));

	this->restart->setPosition(sf::Vector2f(this->player->GetPosition().x - 285.0f, this->player->GetPosition().y + 100.0f));
	this->restartHitbox.setPosition(sf::Vector2f(this->restart->getPosition().x, this->restart->getPosition().y + 10.0f));

	this->backToMenu->setPosition(sf::Vector2f(this->player->GetPosition().x - 200.0f, this->player->GetPosition().y + 200.0f));
}

void Game::updateEndGame()
{
	if (this->player->getHp() == 0) {
		this->isEnding = true;
	}
	else {
		this->isEnding = false;
	}
}

void Game::updateEnding()

{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		this->player->reset();
		this->points = 0;
		this->initialTime();
		this->isEnding = false;
		this->clearAllEnemies();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		updateAndSaveScore(this->playerName, this->points, this->showtime);
		this->player->reset();
		this->clearAllEnemies();
		this->points = 0;
		this->isEnding = false;
		this->mainMenu->isPlay = false;
		this->view->setCenter(sf::Vector2f(960.0f,540.0f));
		this->window->setView(*this->view);
		this->window->clear();
		this->initialMainMenu();
		this->initialTime();
	}

}

void Game::updateAndSaveScore(std::string playerName, int score , int time)
{
	typedef struct NameWithScore {
		std::string name;
		int score;
	} NameWithScore;

	auto compareScores = [](NameWithScore p_1, NameWithScore p_2) {
		return p_1.score > p_2.score;
	};

	std::vector<NameWithScore> namesWithScore;

	NameWithScore currentPlayer;
	currentPlayer.name = playerName;
	currentPlayer.score = score;

	namesWithScore.push_back(currentPlayer);

	std::ifstream ifs("score/score.txt");

	if (ifs.is_open())
	{
		std::string playerName1 = "";
		std::string playerScore = "";

		while (ifs >> playerName1 >> playerScore )
		{

			std::cout << playerName1 << std::endl << playerScore << std::endl;
			NameWithScore temp;
			temp.name = playerName1;
			temp.score = std::stoi(playerScore);
			namesWithScore.push_back(temp);
		}


	}

	ifs.close();

	std::sort(namesWithScore.begin(), namesWithScore.end(), compareScores);

	while (namesWithScore.size() > 5) {
		namesWithScore.pop_back();
	}

	std::fstream ofs;

	ofs.open("score/score.txt", std::ios::out | std::ios::trunc);

	for (auto nameWithScore : namesWithScore) {
		std::cout << "write " << nameWithScore.name << std::endl << nameWithScore.score << std::endl;

		ofs << nameWithScore.name + "\t" + std::to_string(nameWithScore.score) + "\n";
	}

	ofs.close();
}

void Game::updateNameInput()
{
	
}

void Game::update()
{	
	
	this->updatePollEvents();
	if (this->mainMenu->isPlay && !this->isEnding && this->mainMenu->isFinishNameInput) {
		this->player->update(deltaTime);
		this->view->setCenter(this->player->GetPosition());
		this->updateBullets();
		this->updateEnemies();
		this->updateTimeScore();
		this->updateTime();
		this->updateCombat();
		this->updateGUI();
		this->updateEndGame();
	}
	else if (this->isEnding) {
		this->updateEnding();
	}
	else {
		//std::cout << "ex";

		this->mainMenu->update();
	}
	
}

void Game::render()
{
	this->window->clear();
	
	// draw game
	if (this->mainMenu->isPlay && !this->isEnding && this->mainMenu->isFinishNameInput) {
		this->window->setView(*this->view);
		this->background->render(*this->window);
		this->window->draw(*this->playTime);
		this->window->draw(*this->playerScore);
		this->player->render(*this->window);
		this->window->draw(this->playerHpBarBack);
		this->window->draw(this->playerHpBar);
		for (auto* bullet : this->bullets)		// bullets
		{
			bullet->render(*this->window);
		}
		for (auto* enemie : this->enemies)		// enemies
		{
			enemie->render(*this->window);
		}
	}
	else if (this->isEnding) {
		this->window->setView(*this->view);
		this->background->render(*this->window);
		this->window->draw(*this->playTime);
		this->window->draw(*this->playerScore);
		this->player->render(*this->window);
		this->window->draw(this->playerHpBarBack);
		this->window->draw(this->playerHpBar);
		for (auto* bullet : this->bullets)		// bullets
		{
			bullet->render(*this->window);
		}
		for (auto* enemie : this->enemies)		// enemies
		{
			enemie->render(*this->window);
		}
		this->window->draw(this->endingPlan);
		this->window->draw(*this->ending);
		this->window->draw(*this->restart);
		this->window->draw(*this->backToMenu);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
			this->window->draw(this->restartHitbox);
		}
	}
	else { // draw main menu
		//std::cout << "memu";
		//this->window->setView(*this->view);

		this->mainMenu->render();
	}
	this->window->display();
}
