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
	loadTextures();
	setupMusic();
	setupFontAndText(); // load font
	

	auto tm = TextureManager::getInstance();

	m_playButton.setTexture(*tm->getTexture("playButton"));
	m_playButton.setOrigin({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) });
	m_playButton.setPosition({ (WINDOW_WIDTH / 2.f) + 20.0f, (WINDOW_HEIGHT / 2.f) + 190.f });
	m_playButton.setScale(0.8f, 0.8f);

	m_background.setTexture(*tm->getTexture("menuScreen"));
	m_background.setOrigin({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) });
	m_background.setPosition({ (WINDOW_WIDTH / 2.f) + 20.0f, (WINDOW_HEIGHT / 2.f) - 150.f });
	m_background.setScale(1.1f, 0.8f);

	m_gameOverScreen.setTexture(*tm->getTexture("gameOver"));
	m_gameOverScreen.setOrigin({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) });
	m_gameOverScreen.setPosition({ (WINDOW_WIDTH / 2.f) + 20.0f, (WINDOW_HEIGHT / 2.f) - 150.f });
	m_gameOverScreen.setScale(1.1f, 0.8f);

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

		switch (m_state)
		{
		case GameState::MENU:
			updateMenu();

			break;
		case GameState::GAMEPLAY:
			

			break;
		}
	
			
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

	Enemy* newEnemy{ nullptr };

	switch (t_event.key.code)
	{
	case sf::Keyboard::Escape:
		m_exitGame = true;
		break;
	case sf::Keyboard::Space:
		// Do nothing
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Game::processMousePress(sf::Event t_event)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(m_window));
	m_mouth.click(mousePosition);

	std::set<Enemy*> toRemove;
	for (auto& e : m_enemies)
	{
		if (e->getBounds().contains(mousePosition))
		{
			EnemyPool::getInstance()->restore(e);
			toRemove.insert(e);
		}
	}
	m_enemies.erase(
		std::remove_if(m_enemies.begin(), m_enemies.end(),
			[&](Enemy* e) -> bool { return toRemove.count(e); }),
		m_enemies.end()
	);
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

	if (m_state == GameState::GAMEPLAY)
	{
		static int spawnChance{ 40 };

		if (!(rand() % spawnChance)) {
			auto newEnemy = EnemyPool::getInstance()->spawn();

			auto validTeeth = m_mouth.getTeethPositions();

			if (validTeeth.empty())
			{
				m_state = GameState::GAME_OVER;
				return;
			}

			if (newEnemy)
			{
				sf::Vector2f target = validTeeth[rand() % validTeeth.size()];

				newEnemy->spawn({ (WINDOW_WIDTH / 2.f), (WINDOW_HEIGHT / 2.f) }, target);
				m_enemies.push_back(newEnemy);

				if (!(rand() % 5))
					if (spawnChance > 5)
						--spawnChance;
			}
		}

		std::set<Enemy*> toRemove;
		for (auto& e : m_enemies)
		{
			e->update(t_deltaTime);
			if (m_mouth.check(*e))
				toRemove.insert(e);
		}

		m_enemies.erase(
			std::remove_if(m_enemies.begin(), m_enemies.end(),
				[&](Enemy* e) -> bool { return toRemove.count(e); }),
			m_enemies.end()
		);

		m_mouth.update(t_deltaTime);
	}
}

////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	if (m_state == GameState::MENU)
	{
		m_window.draw(m_background);
		m_window.draw(m_playButton);
		updateMenu();
	}
	else if (m_state == GameState::GAMEPLAY)
	{
		m_window.draw(m_logoSprite);
		m_mouth.draw(m_window);

		for (Enemy* enemy : m_enemies)
			enemy->draw(m_window);
	}
	else if (m_state == GameState::GAME_OVER)
	{
		m_window.draw(m_gameOverScreen);
	}
	

	m_window.display();
}

void Game::setupMusic()
{
	
	if (!m_music.openFromFile("ASSETS\\AUDIO\\nova.ogg"))
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

void Game::updateMenu()
{
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(m_window);

	if (m_playButton.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_state = GameState::GAMEPLAY;
		}
	}
}
