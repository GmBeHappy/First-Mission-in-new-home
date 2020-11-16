#include "MainMenu.h"

void MainMenu::initialTexture()
{
	this->menuBackgroung = new sf::Texture;
	this->menuBackgroung->loadFromFile("Textures/bg_first_mission.jpg");
	this->background = new Background(this->menuBackgroung);
}

void MainMenu::initialFont()
{
	this->font = new sf::Font;
	if (!this->font->loadFromFile("ethnocentric_rg.ttf")) {
		printf("Load font fail\n");
	}
}

void MainMenu::initialText()
{
	this->playBtn = new sf::Text();
	this->playBtn->setPosition(sf::Vector2f(130.0f, 300.0f));
	this->playBtn->setCharacterSize(70);
	this->playBtn->setFont(*this->font);
	this->playBtn->setFillColor(sf::Color::Red);
	this->playBtn->setString("play");

	this->scoreBtn = new sf::Text();
	this->scoreBtn->setPosition(sf::Vector2f(130.0f, 400.0f));
	this->scoreBtn->setCharacterSize(70);
	this->scoreBtn->setFont(*this->font);
	this->scoreBtn->setString("score");

	this->howtoBtn = new sf::Text();
	this->howtoBtn->setPosition(sf::Vector2f(130.0f, 500.0f));
	this->howtoBtn->setCharacterSize(70);
	this->howtoBtn->setFont(*this->font);
	this->howtoBtn->setString("how to play");

	this->exitBtn = new sf::Text();
	this->exitBtn->setPosition(sf::Vector2f(130.0f, 850.0f));
	this->exitBtn->setCharacterSize(70);
	this->exitBtn->setFont(*this->font);
	this->exitBtn->setString("exit");
}




MainMenu::MainMenu(sf::RenderWindow* window,sf::Mouse* mouse)
{
	this->initialTexture();
	this->initialFont();
	this->initialText();
	this->window = window;
	this->mouse = mouse;
}

MainMenu::~MainMenu()
{
}

void MainMenu::update()
{
	if (this->playBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y)) {
		this->playBtn->setCharacterSize(80);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			this->isPlay = true;
		}
	}
	else if(this->scoreBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y))
	{
		this->scoreBtn->setCharacterSize(80);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			
		}
	}
	else if (this->howtoBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y))
	{
		this->howtoBtn->setCharacterSize(80);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			
		}
	}
	else if (this->exitBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y))
	{
		this->exitBtn->setCharacterSize(80);
		this->exitBtn->setFillColor(sf::Color::Red);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			this->window->close();
		}
	}
	else {
		this->initialText();
	}
}

void MainMenu::render()
{
	this->background->render(*this->window);
	this->window->draw(*this->playBtn);
	this->window->draw(*this->scoreBtn); 
	this->window->draw(*this->howtoBtn);
	this->window->draw(*this->exitBtn);
}
