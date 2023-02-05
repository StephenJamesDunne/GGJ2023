#include <TextureManager.h>

void TextureManager::loadTexture(std::string t_id, std::string t_path)
{
	if (m_textureMap.count(t_id))
		delete m_textureMap.at(t_id);

	m_textureMap[t_id] = loadTexture(t_path);
}

////////////////////////////////////////////////////////////

sf::Texture* TextureManager::loadTexture(std::string t_path)
try
{
	sf::Texture* tx = new sf::Texture();
	tx->loadFromFile(t_path);
	tx->setSmooth(true);
	return tx;
}
catch (const std::exception& e)
{
	cout << e.what() << endl;
	return nullptr;
}

////////////////////////////////////////////////////////////

sf::Texture* TextureManager::getTexture(std::string t_id)
try
{
	return m_textureMap.at(t_id);
}
catch (const out_of_range& e)
{
	cout << e.what() << endl;
	return nullptr;
}