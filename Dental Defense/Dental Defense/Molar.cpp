#include "Molar.h"

Molar::Molar()
{
	m_hitbox = new sf::CircleShape();

	auto* hb = dynamic_cast<sf::CircleShape*>(m_hitbox);
	hb->setRadius(40.f);
	hb->setOrigin(40.f, 40.f);
	hb->setFillColor(sf::Color::White);
	hb->setOutlineColor(sf::Color::Black);
	hb->setOutlineThickness(8.0f);
}

////////////////////////////////////////////////////////////////////////////////

bool Molar::contains(sf::Vector2f t_point)
{
	sf::Vector2f lineToPoint = m_hitbox->getPosition() - t_point;
	float distanceToPoint = sqrtf(powf(lineToPoint.x, 2) + powf(lineToPoint.y, 2));

	return distanceToPoint < dynamic_cast<sf::CircleShape*>(m_hitbox)->getRadius();
}
