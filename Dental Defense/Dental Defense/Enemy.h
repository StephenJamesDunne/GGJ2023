#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TextureManager.h>

class Enemy
{
public:
	Enemy();

	void init();

	void spawn(sf::Vector2f t_position);

	sf::Vector2f getPosition() { return m_position; }
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }

	void setDirection(sf::Vector2f t_velocity) { m_velocity = t_velocity; }
	void setSpeed(float t_speed) { m_speed = t_speed; }

	void update(sf::Time t_dT);

	void draw(sf::RenderWindow& t_window);

private:

	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_speed;

	//spawn in at the center of the screen, move out towards random sprites, stay on sprite and deal damage to sprite health
	//maybe different health values per size of enemy? one click removes HP and scales down texture
	//collision check of enemy sprite against teeth sprites



};

