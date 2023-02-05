#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>

class Tooth
{
public:
	Tooth();
	~Tooth() { delete m_hitbox; }

	sf::Vector2f  getPosition() { return m_hitbox->getPosition(); }
	void setPosition(sf::Vector2f t_position) { m_hitbox->setPosition(t_position); }

	virtual bool contains(sf::Vector2f t_point) = 0;

	void onClick();

	void germLatchedOn() { ++m_numGermsOnTooth; }

	void takeDamage();

	void die();

	void draw(sf::RenderWindow& t_window) { t_window.draw(*m_hitbox); }

private:

protected:

	sf::Shape* m_hitbox{ nullptr };

	const int MAX_HEALTH{ 20 };
	int m_health{ MAX_HEALTH };

	int m_numGermsOnTooth{ 0 };
};

