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

		auto redVal = 255 - ((255 / float(MAX_HEALTH)) * m_health);
		std::cout << "Taking damage! Health: " << m_health << " Red value: " << redVal << std::endl;
		m_hitbox->setFillColor({ sf::Uint8(redVal), 0, 0, 128 });
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::die()
{
	m_health = 0;
}
