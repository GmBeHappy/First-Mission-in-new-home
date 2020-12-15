#include "Game.h"

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
}

void Game::initialFont()
{
	this->font = new sf::Font;
	if(!this->font->loadFromFile("Cloud.ttf")){
		printf("Load font fail\n");
	}
}

void Game::initialPlaytime()
{
	this->playTime = new sf::Text();
	this->playTime->setPosition(sf::Vector2f(0.0f,0.0f));
	this->playTime->setCharacterSize(40);
	this->playTime->setFont(*this->font);
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

/*GAME WINDOW*/
Game::Game(){
	this->initialWindow();
	this->initialPlayer();
	this->initialBackground();
	this->initialView();
	this->initialTime();
	this->initialFont();
	this->initialPlaytime();
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
		std::cout << "enemy spawn\n";
		float enemyPosY = rand() % (int)this->player->GetPosition().y;
		float enemyPosX = rand() % (int)this->player->GetPosition().x;
		std::cout << "x : ";
		std::cout << enemyPosX;
		std::cout << "\t";
		std::cout << "y : ";
		std::cout << enemyPosY;
		std::cout << "\n";
		this->enemies.push_back(new Enemies(enemyPosY, enemyPosY + 100.f,this->enemyTexture,sf::Vector2u(3, 4), 0.3f));
		this->enemySpawnTimer = 0.f;
	}

	// update
	unsigned Fcounter = 0;
	for (auto* enemie : this->enemies)
	{
		enemie->update(deltaTime,this->player->GetPosition());

		//// enemies culling (top screen)
		//if (enemie->getBounds().left < this->window->getSize().y - 1700.f)
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

void Game::update()
{	
	
	this->updatePollEvents();
	if (this->mainMenu->isPlay) {
		this->player->update(deltaTime);
		this->view->setCenter(this->player->GetPosition());
		this->updateBullets();
		this->updateEnemies();
		this->updateTimeScore();
		this->updateTime();
	}
	else {
		this->mainMenu->update();
	}
	
}
void Game::render()
{
	this->window->clear();
	
	// draw game
	if (this->mainMenu->isPlay) {
		this->window->setView(*this->view);
		this->background->render(*this->window);
		this->window->draw(*this->playTime);
		this->player->render(*this->window);
		for (auto* bullet : this->bullets)		// bullets
		{
			bullet->render(*this->window);
		}
		for (auto* enemie : this->enemies)		// enemies
		{
			enemie->render(*this->window);
		}
	}
	else { // draw main menu
		this->mainMenu->render();
	}
	this->window->display();
}
