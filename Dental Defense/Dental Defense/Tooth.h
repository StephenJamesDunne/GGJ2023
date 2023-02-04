#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>

class Tooth
{
public:
	Tooth();

	void setPosition(sf::Vector2f t_position) { m_sprite.setPosition(t_position); }
	sf::Vector2f  getPosition(sf::Vector2f) { return m_sprite.getPosition(); }

	sf::FloatRect getBounds() { return m_sprite.getGlobalBounds(); }

	bool contains(sf::Vector2f t_point);

	void onClick(); 

	void draw(sf::RenderWindow& t_window) { t_window.draw(m_sprite); }

private:
	sf::CircleShape m_sprite;
	
	
	//health values
	
	//sprite, possibly sized all the same 
	//separate textures for different health stages
	//when the tooth dies, gains wings and flies off to heaven (+= y coord)
	//on click function for gameplay
};

