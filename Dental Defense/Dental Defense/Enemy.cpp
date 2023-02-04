#include "Enemy.h"

Enemy::Enemy()
{
	m_texture.loadFromFile("ASSETS\\IMAGES\\germ.png");
	m_sprite.setTexture(m_texture);

	sf::FloatRect bounds = m_sprite.getGlobalBounds();

	m_sprite.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });
}

void Enemy::update(sf::Time t_dT)
{
	m_position += m_velocity * m_speed * t_dT.asSeconds();
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	m_sprite.setPosition(m_position);
	t_window.draw(m_sprite);
}
