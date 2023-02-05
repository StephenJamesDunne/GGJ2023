#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <set>
#include <filesystem>
#include <sstream>
#include <TextureManager.h>
#include <Mouth.h>
#include <EnemyPool.h>

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
	void setupMusic();
	void setupFontAndText();

	std::vector<Enemy*> m_enemies;
	Mouth m_mouth; // All our teeth live here

	float m_speed = 5.0f;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_mouthTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::SoundBuffer m_buffer; //music buffer
	sf::Music m_music; //music file
	bool m_exitGame; // control exiting game

	int currentFrame = 0;

};

#endif 

