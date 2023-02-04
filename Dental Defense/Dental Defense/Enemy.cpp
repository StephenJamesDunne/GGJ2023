#include "Enemy.h"

Enemy::Enemy()
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });

	setPosition({ -100,-100 });
}

////////////////////////////////////////////////////////////////////////////////

void Enemy::init()
{
	auto tx = TextureManager::getInstance()->getTexture("mouth");

	m_sprite.setTexture(*tx);
	m_sprite.setScale(0.1f, 0.1f);
}

////////////////////////////////////////////////////////////////////////////////

void Enemy::spawn(sf::Vector2f t_position)
{
	setPosition(t_position);

	float angleToMove = rand() % 360;
	setDirection({ cos(angleToMove), sin(angleToMove) });
	setSpeed((rand() % 100) + 20); // between 20-120
}

////////////////////////////////////////////////////////////////////////////////

void Enemy::update(sf::Time t_dT)
{
	m_position += m_velocity * m_speed * t_dT.asSeconds();
}

////////////////////////////////////////////////////////////////////////////////

void Enemy::draw(sf::RenderWindow& t_window)
{
	m_sprite.setPosition(m_position);
	t_window.draw(m_sprite);
}
