#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }

	void update(sf::Time t_dT);

	void draw(sf::RenderWindow& t_window);

private:


	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	//spawn in at the center of the screen, move out towards random sprites, stay on sprite and deal damage to sprite health
	//maybe different health values per size of enemy? one click removes HP and scales down texture
	//collision check of enemy sprite against teeth sprites



};

