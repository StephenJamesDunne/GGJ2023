#include "Game.h"

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
	auto tm = TextureManager::getInstance();
	tm->loadTexture("germ", "ASSETS\\IMAGES\\germ.png");
	tm->loadTexture("mouth", "ASSETS\\IMAGES\\mouth.png");
	
	loadTextures();
	setupMusic();
	setupFontAndText(); // load font

	m_mouth.init();
	
	m_mouth.setPosition({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) });
}

////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void Game::loadTextures()
{
	auto tm = TextureManager::getInstance();
	std::filesystem::directory_iterator dir{ "ASSETS\\IMAGES" };

	for (const auto& entry : dir)
	{
		auto name = entry.path().filename().string();
		auto path = entry.path().string();

		std::stringstream iss{name};
		std::getline(iss, name, '.');

		tm->loadTexture(name, path);
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

////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	static int x{ 0 };

	switch (t_event.key.code)
	{
	case sf::Keyboard::Escape:
		m_exitGame = true;
		break;
	case sf::Keyboard::Space:
		
		m_enemies[x++%10].spawn({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) });
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Game::processMousePress(sf::Event t_event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	m_mouth.click(sf::Vector2f(mousePosition));
}

////////////////////////////////////////////////////////////////////////////////

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
	
	for (auto& e : m_enemies)
	{
		e.update(t_deltaTime);
		m_mouth.check(e);
	}
}

////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	m_mouth.draw(m_window);
	
	for (Enemy& enemy : m_enemies)
		enemy.draw(m_window);

	m_window.display();
}

void Game::setupMusic()
{
	
	if (!m_music.openFromFile("ASSETS\\AUDIO\\nova.wav"))
	{
		std::cout << "problem loading music :(" << std::endl;
	}
	m_music.setVolume(50.0f);
	m_music.setLoop(true);
	m_music.play();

}

////////////////////////////////////////////////////////////////////////////////

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
