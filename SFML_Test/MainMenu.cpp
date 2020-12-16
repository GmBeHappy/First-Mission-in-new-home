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

void MainMenu::initialNameInput()
{
	this->name = new sf::Text();
	this->name->setPosition(sf::Vector2f(1000.0f, 350.0f));
	this->name->setCharacterSize(40);
	this->name->setFont(*this->font);
	this->name->setString("name :");

	this->nameInput = new sf::Text();
	this->nameInput->setPosition(sf::Vector2f(1010.0f, 390.0f));
	this->nameInput->setCharacterSize(40);
	this->nameInput->setFont(*this->font);

	this->textBox.setPosition(sf::Vector2f(1000.0f, 400.0f));
	this->textBox.setSize(sf::Vector2f(500.0f,60.0f));
	this->textBox.setFillColor(sf::Color(25, 25, 25, 200));

}

void MainMenu::initialReadScore()
{
	this->shape.setPosition(sf::Vector2f(1000.0f, 300.0f));
	this->shape.setSize(sf::Vector2f(600.f, 500.f));
	this->shape.setFillColor(sf::Color(70, 70, 70, 200));

	std::string header = "SCORE BOARD";
	this->header = new sf::Text();
	this->header->setFont(*this->font);
	this->header->setString(header);
	this->header->setCharacterSize(40);
	//this->header.setFillColor(sf::Color(250, 250, 250, 250));
	this->header->setFillColor(sf::Color::White);
	this->header->setPosition(sf::Vector2f(1080.0f, 350.0f));
	
	std::ifstream ifs("score/score.txt");
	std::cout << "init content\n";
	if (ifs.is_open())
	{
		std::cout << "open file";
		std::string playerName = "";
		std::string playerScore = "";

		std::string content = "";
		int i = 1;
		while (ifs >> playerName >> playerScore)
		{
			content += (playerName + " - " + playerScore + "\n");
			++i;
		}
		this->content = new sf::Text();
		this->content->setFont(*this->font);
		std::cout << content;
		this->content->setString(content);
		this->content->setCharacterSize(40);
		this->content->setFillColor(sf::Color::White);
		this->content->setPosition(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->content->getGlobalBounds().width / 2.f,
			this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->content->getGlobalBounds().height / 2.f + 30.f
		);
		//this->content.setOutlineThickness(1.f);
		//this->content.setOutlineColor(sf::Color::Black);
	}

	ifs.close();
}

void MainMenu::initialHowto()
{
	this->howtoTexture = new sf::Texture;
	this->howtoTexture->loadFromFile("Textures/how_to_mini.jpg");
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*this->howtoTexture);
	this->sprite->setPosition(sf::Vector2f(1000.0f, 250.0f));
}




MainMenu::MainMenu(sf::RenderWindow* window,sf::Mouse* mouse)
{
	//this->leaderboard = new Plane(1000.0f, 300.0f, 600.f, 500.f, this->font, 40, 40);
	this->initialTexture();
	this->initialFont();
	this->initialText();
	this->initialNameInput();
	this->initialReadScore();
	this->initialHowto();
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
			this->isNameInput = true;
			this->toggleLeaderboard = false;
			this->toggleHowTo = false;
		}
	}
	else if(this->scoreBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y))
	{
		this->scoreBtn->setCharacterSize(80);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			this->toggleLeaderboard = true;
			this->isNameInput = false;
			this->toggleHowTo = false;
		}
	}
	else if (this->howtoBtn->getGlobalBounds().contains(this->mouse->getPosition(*this->window).x, this->mouse->getPosition(*this->window).y))
	{
		this->howtoBtn->setCharacterSize(80);
		if (this->mouse->isButtonPressed(this->mouse->Left)) {
			this->toggleLeaderboard = false;
			this->toggleHowTo = true;
			this->isNameInput = false;
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
	if (this->isNameInput) {
		this->window->draw(*this->name);
		this->window->draw(this->textBox);
		this->window->draw(*this->nameInput);
	}
	if (this->toggleLeaderboard) {
		this->window->draw(this->shape);
		this->window->draw(*this->header);
		this->window->draw(*this->content);
	}
	if (this->toggleHowTo) {
		this->window->draw(*this->sprite);
	}
}
