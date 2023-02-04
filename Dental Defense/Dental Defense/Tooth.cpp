#include "Tooth.h"

Tooth::Tooth()
{
	m_sprite.setRadius(100.0f);
	m_sprite.setOrigin(100.f, 100.f);
	m_sprite.setFillColor(sf::Color::White);
	m_sprite.setOutlineColor(sf::Color:: Black);
	m_sprite.setOutlineThickness(8.0f);
}

bool Tooth::contains(sf::Vector2f t_point)
{
	sf::Vector2f lineToPoint = m_sprite.getPosition() - t_point;
	float distanceToPoint = sqrtf(powf(lineToPoint.x, 2) + powf(lineToPoint.y, 2));

	//std::cout << distanceToPoint << std::endl;

	return distanceToPoint < m_sprite.getRadius();
}

void Tooth::onClick()
{
	m_sprite.setFillColor(sf::Color::Red);	
}
