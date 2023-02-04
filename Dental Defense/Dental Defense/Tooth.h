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

	void draw(sf::RenderWindow& t_window) { t_window.draw(*m_hitbox); }

private:

protected:

	sf::Shape* m_hitbox;
	
	//health values
	
	//sprite, possibly sized all the same 
	//separate textures for different health stages
	//when the tooth dies, gains wings and flies off to heaven (+= y coord)
	//on click function for gameplay
};

