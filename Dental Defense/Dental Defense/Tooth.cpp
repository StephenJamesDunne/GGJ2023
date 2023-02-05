#include "Tooth.h"

Tooth::Tooth()
{
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::onClick()
{	
}

////////////////////////////////////////////////////////////////////////////////

void Tooth::takeDamage()
{
	if (m_numGermsOnTooth)
	{
		if (m_health > m_numGermsOnTooth)
			m_health -= m_numGermsOnTooth;
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
