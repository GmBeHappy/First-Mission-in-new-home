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

void Game::updateMousePosition()
{
	
}


void Game::update()
{	
	this->updatePollEvents();
	this->mainMenu->update();
	deltaTime = this->clock->restart().asSeconds();
	this->player->update(deltaTime);
	this->view->setCenter(this->player->GetPosition());
	this->time = &this->clocktime->getElapsedTime();
	this->showtime = this->time->asSeconds();
	this->playTime->setString("Time : "+std::to_string(this->showtime)+"s");
	this->playTime->setPosition(sf::Vector2f(this->player->GetPosition().x-930.0f, this->player->GetPosition().y-520.0f));
}
void Game::render()
{
	this->window->clear();
	
	if (this->mainMenu->isPlay) {
		this->window->setView(*this->view);
		this->background->render(*this->window);
		this->window->draw(*this->playTime);
		this->player->render(*this->window);
	}
	else {
		this->mainMenu->render();
	}
	this->window->display();
}
