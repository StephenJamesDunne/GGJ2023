#include "Enemy.h"

Enemy::Enemy()
{
	m_texture.loadFromFile("ASSETS\\IMAGES\\plaque.jpg");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(200.0f, 200.0f);
}

void Enemy::update(sf::Time t_dT)
{
	m_position += m_velocity;
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	m_sprite.setPosition(m_position);
	t_window.draw(m_sprite);
}
