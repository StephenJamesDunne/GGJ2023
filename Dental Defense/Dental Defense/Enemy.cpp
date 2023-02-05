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
	auto tx = TextureManager::getInstance()->getTexture("germ");

	m_sprite.setTexture(*tx);
	m_sprite.setOrigin(tx->getSize().x / 2.f, tx->getSize().y / 2.f);
	m_sprite.setScale(0.1f, 0.1f);

	m_hitbox.setPosition({ -100.f, -100.f });
	m_hitbox.setOrigin(70.f, 50.f);
	m_hitbox.setFillColor(sf::Color::Red);
	m_hitbox.setRadius(50.f);
}

////////////////////////////////////////////////////////////////////////////////

void Enemy::spawn(sf::Vector2f t_position)
{
	init();


	sf::Vector2f randomOffset = { float(rand() % 300) - 151.f, float(rand() % 300) - 151.f };
	setPosition(t_position + randomOffset);

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
	m_hitbox.setPosition(m_position);
	t_window.draw(m_sprite);
}
