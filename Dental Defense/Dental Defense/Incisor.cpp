#include "Incisor.h"

Incisor::Incisor()
{
	m_hitbox = new sf::RectangleShape();

	dynamic_cast<sf::RectangleShape*>(m_hitbox)->setSize({80.f, 160.f});
	dynamic_cast<sf::RectangleShape*>(m_hitbox)->setOrigin(20.f, 40.f);
	dynamic_cast<sf::RectangleShape*>(m_hitbox)->setFillColor(sf::Color::White);
	dynamic_cast<sf::RectangleShape*>(m_hitbox)->setOutlineColor(sf::Color::Black);
	dynamic_cast<sf::RectangleShape*>(m_hitbox)->setOutlineThickness(8.0f);
}

////////////////////////////////////////////////////////////////////////////////

bool Incisor::contains(sf::Vector2f t_point)
{
	return m_hitbox->getGlobalBounds().contains(t_point);
}
