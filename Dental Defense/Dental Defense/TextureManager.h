#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>

using namespace std;

class TextureManager
{
public:
	static TextureManager* const getInstance() {
		static TextureManager* const instance = new TextureManager();
		return instance;
	}

	TextureManager(TextureManager&) = delete;
	TextureManager& operator=(TextureManager&) = delete;

	void loadTexture(std::string t_id, std::string t_path);
	sf::Texture* loadTexture(std::string t_path);

	void addTexture(const char* t_id, sf::Texture* t_texure) { m_textureMap[t_id] = t_texure; }
	sf::Texture* getTexture(std::string t_id);

private:
	TextureManager() {}

	unordered_map<std::string, sf::Texture*> m_textureMap;
};

#endif