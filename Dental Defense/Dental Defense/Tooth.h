#pragma once

#include <stack>
#include <iostream>
#include<SFML/Graphics.hpp>

#include <EnemyPool.h>

class Enemy;

class Tooth
{
public:
	Tooth();
	~Tooth() { delete m_hitbox; }

	void setTexture(sf::Texture& t_tex) { 
		m_sprite.setTexture(t_tex);
		m_sprite.setScale(0.75f, 0.75f);
		m_sprite.setOrigin({ t_tex.getSize().x / 2.f, t_tex.getSize().y / 2.f });
	}

	sf::Vector2f  getPosition() { return m_hitbox->getPosition(); }
	void setPosition(sf::Vector2f t_position) { m_hitbox->setPosition(t_position); m_sprite.setPosition(t_position); }

	virtual bool contains(sf::Vector2f t_point) = 0;

	void onClick();

	void germLatchedOn(Enemy* t_enemy) { m_germsOnTooth.push(t_enemy); }

	void takeDamage();

	void die();

	void draw(sf::RenderWindow& t_window);

	bool isDead{ false };

private:

protected:

	sf::Sprite m_sprite;
	sf::Shape* m_hitbox{ nullptr };

	const int MAX_HEALTH{ 8 };
	int m_health{ MAX_HEALTH };

	std::stack<Enemy*> m_germsOnTooth;
};

#include <Enemy.h>
