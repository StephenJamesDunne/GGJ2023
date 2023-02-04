#include "Incisor.h"

Incisor::Incisor()
{
	m_hitbox = new sf::RectangleShape();

	auto* hb = dynamic_cast<sf::RectangleShape*>(m_hitbox);
	hb->setSize({80.f, 160.f});
	hb->setOrigin(20.f, 40.f);
	hb->setFillColor(sf::Color(255, 255, 255, 128));
	hb->setOutlineColor(sf::Color(0, 0, 0, 128));
	hb->setOutlineThickness(8.0f);
}

////////////////////////////////////////////////////////////////////////////////

bool Incisor::contains(sf::Vector2f t_point)
{
	return m_hitbox->getGlobalBounds().contains(t_point);
}
