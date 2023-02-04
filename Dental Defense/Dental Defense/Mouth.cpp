#include "Mouth.h"

Mouth::Mouth()
{
	loadTextures();

	for (auto& t : m_topMolars) { t = new Molar(), m_teeth.push_back(t); }
	for (auto& t : m_topIncisors) { t = new Incisor(), m_teeth.push_back(t); }
	for (auto& t : m_bottomMolars) { t = new Molar(), m_teeth.push_back(t); }
	for (auto& t : m_bottomIncisors) { t = new Incisor(), m_teeth.push_back(t); }
}

////////////////////////////////////////////////////////////////////////////////



void Mouth::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;


	float angleBetweenTeeth = (6.28 / 360.f) * 12; // 5 degrees :)
	float distanceFromTongue = 420.f;

	// Top row
	for (int i = 0; i < m_teeth.size() / 2; ++i)
	{
		float angle = ((6.28 / 360.f) * -180) + (angleBetweenTeeth * i);

		sf::Vector2f position = sf::Vector2f(
			cosf(angle) * distanceFromTongue,
			sinf(angle) * distanceFromTongue
		) + m_position;

		m_teeth[i]->setPosition(position);
	}

	sf::Vector2f bottomRowOffset = { 0.f, 200.f };

	// Bottom row
	for (int i = m_teeth.size() / 2; i < m_teeth.size(); ++i)
	{
		float angle = ((6.28 / 360.f) * 169) + (angleBetweenTeeth * i);

		sf::Vector2f position = sf::Vector2f(
			cosf(angle) * distanceFromTongue,
			sinf(angle) * distanceFromTongue
		) + m_position;

		m_teeth[i]->setPosition(position + bottomRowOffset);
	}

	m_sprite.setPosition(m_position);
}

void Mouth::clicked(sf::Vector2f t_position)
{
	for (Tooth* t : m_teeth)
		if (t->contains(t_position))
			t->onClick();
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);

	for (Tooth* t : m_teeth)
		t->draw(t_window);
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::loadTextures()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\mouth.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading mouth texture" << std::endl;
	};

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize()) / 2.f);
	m_sprite.setScale(2.0f, 2.0f);
}
