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

	auto tm = TextureManager::getInstance();

	m_topMolars[0]->setTexture(*tm->getTexture("MT8L"));
	m_topMolars[1]->setTexture(*tm->getTexture("MT7L"));
	m_topMolars[2]->setTexture(*tm->getTexture("PMT6L"));
	m_topMolars[3]->setTexture(*tm->getTexture("PMT5L"));
	m_topMolars[4]->setTexture(*tm->getTexture("PMT5R"));
	m_topMolars[5]->setTexture(*tm->getTexture("PMT6R"));
	m_topMolars[6]->setTexture(*tm->getTexture("MT7R"));
	m_topMolars[7]->setTexture(*tm->getTexture("MT8R"));

	m_topIncisors[0]->setTexture(*tm->getTexture("PMT4L"));
	m_topIncisors[1]->setTexture(*tm->getTexture("CT3L"));
	m_topIncisors[2]->setTexture(*tm->getTexture("INT2L"));
	m_topIncisors[3]->setTexture(*tm->getTexture("INT1L"));
	m_topIncisors[4]->setTexture(*tm->getTexture("INT1R"));
	m_topIncisors[5]->setTexture(*tm->getTexture("INT2R"));
	m_topIncisors[6]->setTexture(*tm->getTexture("INT3R"));
	m_topIncisors[7]->setTexture(*tm->getTexture("CT4R"));

	m_bottomMolars[0]->setTexture(*tm->getTexture("MB8L"));
	m_bottomMolars[1]->setTexture(*tm->getTexture("MB7L"));
	m_bottomMolars[2]->setTexture(*tm->getTexture("PMB6L"));
	m_bottomMolars[3]->setTexture(*tm->getTexture("PMB5L"));
	m_bottomMolars[4]->setTexture(*tm->getTexture("PMB5R"));
	m_bottomMolars[5]->setTexture(*tm->getTexture("PMB6R"));
	m_bottomMolars[6]->setTexture(*tm->getTexture("MB7R"));
	m_bottomMolars[7]->setTexture(*tm->getTexture("MB8R"));

	m_bottomIncisors[0]->setTexture(*tm->getTexture("PMB4L"));
	m_bottomIncisors[1]->setTexture(*tm->getTexture("CB3L"));
	m_bottomIncisors[2]->setTexture(*tm->getTexture("INB2L"));
	m_bottomIncisors[3]->setTexture(*tm->getTexture("INB1L"));
	m_bottomIncisors[4]->setTexture(*tm->getTexture("INB1R"));
	m_bottomIncisors[5]->setTexture(*tm->getTexture("INB2R"));
	m_bottomIncisors[6]->setTexture(*tm->getTexture("CB3R"));
	m_bottomIncisors[7]->setTexture(*tm->getTexture("PMB4R"));
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

void Mouth::update(sf::Time t_dT)
{
	static sf::Time tslu;
	tslu += t_dT;

	if (tslu > sf::seconds(1))
	{
		for (auto& t : m_teeth)
			t->takeDamage();
		tslu = sf::seconds(0);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Mouth::check(Enemy& t_enemy)
{
	for (Tooth* t : m_teeth)
		if (t->contains(t_enemy.getPosition()))
		{
			t->germLatchedOn(&t_enemy);
			t_enemy.setSpeed(0.f);
			t_enemy.setPosition(t->getPosition());

			return true;
		}
	return false;
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

std::vector<sf::Vector2f> Mouth::getTeethPositions()
{
	std::vector<sf::Vector2f> positions;

	for (Tooth* t : m_teeth)
		if (!t->isDead)
			positions.push_back(t->getPosition());
	
	return positions;
}

////////////////////////////////////////////////////////////////////////////////

void Mouth::loadTextures()
{
	auto tm = TextureManager::getInstance();
	auto tx = tm->getTexture("mouth");

	m_sprite.setTexture(*tx);
	m_sprite.setOrigin(sf::Vector2f(tx->getSize()) / 2.f);
	m_sprite.setScale(0.75f, 0.75f);
}
