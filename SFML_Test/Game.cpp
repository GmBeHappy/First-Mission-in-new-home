#include "Game.h"

//setup game window default config
void Game::initialWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "First mission in New Home", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

// player
void Game::initialPlayer()
{
	this->playerTexture = new sf::Texture;
	this->playerTexture->loadFromFile("Textures/player.png");
	this->player = new Player(this->playerTexture, sf::Vector2u(5, 5), 0.3f, 100.0f);
	this->clock = new sf::Clock;
}

/* --- SKY BACKGROUND ---*/

void Game::initialBackground()
{
	this->background = new Background;
}


/*GAME WINDOW*/
Game::Game(){
	this->initialWindow();
	this->initialPlayer();
	this->initialBackground();
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
	}
}


void Game::update()
{	
	this->updatePollEvents();
	deltaTime = this->clock->restart().asSeconds();
	this->player->update(deltaTime);
}
void Game::render()
{
	this->window->clear();
	this->background->render(*this->window);
	/*display*/
	this->player->render(*this->window);
	this->window->display();
}
