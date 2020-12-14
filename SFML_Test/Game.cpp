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
	this->player = new Player(this->window,this->playerTexture, sf::Vector2u(5, 5), 0.3f, 100.0f,this->mouse);
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

void Game::update()
{	
	
	this->updatePollEvents();
	this->updateTimeScore();
	this->updateTime();
	this->mainMenu->update();
	this->player->update(deltaTime);
	this->view->setCenter(this->player->GetPosition());
	this->updateBullets();
	
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
	}
	else { // draw main menu
		this->mainMenu->render();
	}
	this->window->display();
}
