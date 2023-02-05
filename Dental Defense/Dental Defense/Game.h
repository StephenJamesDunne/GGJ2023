#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <filesystem>
#include <sstream>
#include <TextureManager.h>
#include <Mouth.h>
#include <Enemy.h>

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	void loadTextures();
	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePress(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	std::array<Enemy, 10> m_enemies;
	Mouth m_mouth; // All our teeth live here
	
	//sf::Texture m_enemyTexture;
	//sf::Sprite  m_enemySprite;
	sf::Vector2f m_enemyLocation{ 200.0f, 200.0f };
	sf::Vector2f m_enemyVelocity{ 1.0f, 1.0f };

	float m_speed = 5.0f;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_mouthTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	int currentFrame = 0;

};

#endif 

