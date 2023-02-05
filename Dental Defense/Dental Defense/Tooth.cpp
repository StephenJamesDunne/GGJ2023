#include "Tooth.h"

Tooth::Tooth()
{
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::onClick()
{
	if (!m_germsOnTooth.empty())
	{
		EnemyPool::getInstance()->restore(m_germsOnTooth.top());
		m_germsOnTooth.pop();
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::takeDamage()
{
	int germCount = m_germsOnTooth.size();

	if (germCount)
	{
		if (m_health > germCount)
			m_health -= germCount;
		else
			die();
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::die()
{
	std::cout << "Tooth died :(" << std::endl;
	m_health = 0;
	m_sprite.setColor({ 0,0,0,0 });
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
	//t_window.draw(*m_hitbox);

	std::vector<Enemy*> toDraw;
	while (!m_germsOnTooth.empty())
		toDraw.push_back(m_germsOnTooth.top()), m_germsOnTooth.pop();

	for (Enemy* enemy : toDraw)
		enemy->draw(t_window);

	// abeer was here :) <3 
	for (Enemy* enemy : toDraw) m_germsOnTooth.push(enemy);
}
