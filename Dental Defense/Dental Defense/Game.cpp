#include "Game.h"

#include <iostream>

const unsigned WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height / 4.0f * 3.0f;
const unsigned WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width / 4.0f * 3.0f;
const float DEG_2_RAD = 3.14159265358979323 / 180.f;

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup the image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "Dental Defense" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	

	for (int i = 0; i < m_teeth.size() / 2; ++i)
	{
		m_teeth[i].setPosition({ 400.f + (200.f * i), 200.f });
	}

	for (int i = m_teeth.size() / 2; i < m_teeth.size(); ++i)
	{
		m_teeth[i].setPosition({ 400.f + (200.f * (i-4)), 400.f });
	}
	m_enemy[0].setPosition(sf::Vector2f(200.0f, 200.0f));

	float angle = rand() % 360;
	float x = cos(angle);
	float y = sin(angle);

	std::cout << x << y;


	m_enemy[0].setVelocity({x, y});

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePress(newEvent);
		}

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMousePress(sf::Event t_event)
{
	//if left click happens within m_teeth sprite, set sprite color to red
	t_event.mouseButton.x;
	t_event.mouseButton.y;

	// OR

	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

	for (Tooth& t : m_teeth)
	{
		if (t.contains(sf::Vector2f(mousePosition)))
		{
			t.onClick();
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_enemy[0].update(t_deltaTime);
	
	
		
	
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	
	for (Enemy& enemy : m_enemy)
	{
		enemy.draw(m_window);
	}

	for (Tooth& tooth : m_teeth)
	{
		tooth.draw(m_window);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Dental Defense");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition((WINDOW_WIDTH / 2.5f), 20.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Black);
	m_welcomeMessage.setFillColor(sf::Color::White);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>


bool Game::checkBounds()
{
	bool mouseOnSprite{ true };

	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

}
