#ifndef MOUTH_H
#define MOUTH_H

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Molar.h>
#include <Incisor.h>

class Mouth
{
public:
	Mouth();
	~Mouth() = default;

	void setPosition(sf::Vector2f t_position);

	void clicked(sf::Vector2f t_position);

	void draw(sf::RenderWindow& t_window);
private:

	void loadTextures();

	sf::Vector2f m_position;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	std::array<Molar*, 8> m_topMolars;
	std::array<Molar*, 8> m_bottomMolars;

	std::array<Incisor*, 8> m_topIncisors;
	std::array<Incisor*, 8> m_bottomIncisors;

	std::vector<Tooth*> m_teeth;
};

#endif