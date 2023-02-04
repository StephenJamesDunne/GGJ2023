#include "Mouth.h"

Mouth::Mouth()
{
	for (auto& t : m_topMolars) { t = new Molar(), m_teeth.push_back(t); }
	for (auto& t : m_topIncisors) { t = new Incisor(), m_teeth.push_back(t); }
	for (auto& t : m_bottomMolars) { t = new Molar(), m_teeth.push_back(t); }
	for (auto& t : m_bottomIncisors) { t = new Incisor(), m_teeth.push_back(t); }
}

////////////////////////////////////////////////////////////////////////////////


void Mouth::init()
{
	loadTextures();
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;

	for (int i = 0; i < m_topIncisors.size(); ++i)
		m_topIncisors[i]->setPosition(m_position + m_topIncisorOffsets[i]);

	for (int i = 0; i < m_bottomIncisors.size(); ++i)
		m_bottomIncisors[i]->setPosition(m_position + m_bottomIncisorOffsets[i]);

	for (int i = 0; i < m_topMolars.size(); ++i)
		m_topMolars[i]->setPosition(m_position + m_topMolarOffsets[i]);

	for (int i = 0; i < m_bottomMolars.size(); ++i)
		m_bottomMolars[i]->setPosition(m_position + m_bottomMolarOffsets[i]);


	m_sprite.setPosition(m_position);
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::check(Enemy& t_enemy)
{
	for (Tooth* t : m_teeth)
		if (t->contains(t_enemy.getPosition()))
		{
			t->onClick();
			t_enemy.setSpeed(0.f);
			t_enemy.setPosition(t->getPosition());
		}
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::click(sf::Vector2f t_position)
{
	for (Tooth* t : m_teeth)
		if (t->contains(t_position))
			t->onClick();
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);

	for (Tooth* t : m_teeth)
		t->draw(t_window);
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::loadTextures()
{
	auto tx = TextureManager::getInstance()->getTexture("mouth");

	m_sprite.setTexture(*tx);
	m_sprite.setOrigin(sf::Vector2f(tx->getSize()) / 2.f);
	m_sprite.setScale(0.75f, 0.75f);
}
