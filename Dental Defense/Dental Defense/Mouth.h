#ifndef MOUTH_H
#define MOUTH_H

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Molar.h>
#include <Incisor.h>
#include <Enemy.h>
#include <TextureManager.h>

class Mouth
{
public:
	Mouth();
	~Mouth() = default;

	void init();

	void setPosition(sf::Vector2f t_position);

	void update(sf::Time t_dT);

	void check(Enemy& t_enemy);

	void click(sf::Vector2f t_position);

	void draw(sf::RenderWindow& t_window);

private:

	void loadTextures();

	std::array<sf::Vector2f, 8> m_topIncisorOffsets {
		sf::Vector2f(-340.f, -360.f),
		sf::Vector2f(-270.f, -420.f),
		sf::Vector2f(-180.f, -440.f),
		sf::Vector2f(-80.f, -460.f),
		sf::Vector2f(20.f, -460.f),
		sf::Vector2f(120.f, -450.f),
		sf::Vector2f(200.f, -430.f),
		sf::Vector2f(280.f, -360.f)
	};

	std::array<sf::Vector2f, 8> m_bottomIncisorOffsets{
		sf::Vector2f(-320.f, 400.f),
		sf::Vector2f(-260.f, 420.f),
		sf::Vector2f(-180.f, 440.f),
		sf::Vector2f(-100.f, 450.f),
		sf::Vector2f(0.f, 450.f),
		sf::Vector2f(80.f, 440.f),
		sf::Vector2f(150.f, 420.f),
		sf::Vector2f(210.f, 400.f)
	};

	std::array<sf::Vector2f, 8> m_topMolarOffsets {
		sf::Vector2f(-450.f, -35.f),
		sf::Vector2f(-430.f, -100.f),
		sf::Vector2f(-390.f, -160.f),
		sf::Vector2f(-370.f, -230.f),
		sf::Vector2f(340.f, -230.f),
		sf::Vector2f(360.f, -160.f),
		sf::Vector2f(380.f, -100.f),
		sf::Vector2f(400.f, -35.f),
	};

	std::array<sf::Vector2f, 8> m_bottomMolarOffsets{
		sf::Vector2f(-450.f, 160.f),
		sf::Vector2f(-430.f, 230.f),
		sf::Vector2f(-390.f, 300.f),
		sf::Vector2f(-340.f, 360.f),
		sf::Vector2f(320.f, 360.f),
		sf::Vector2f(360.f, 300.f),
		sf::Vector2f(380.f, 230.f),
		sf::Vector2f(400.f, 160.f),
	};

	sf::Vector2f m_position;

	sf::Sprite m_sprite;

	std::array<Molar*, 8> m_topMolars;
	std::array<Molar*, 8> m_bottomMolars;

	std::array<Incisor*, 8> m_topIncisors;
	std::array<Incisor*, 8> m_bottomIncisors;

	std::vector<Tooth*> m_teeth;
};

#endif