#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void loadSprite(const std::string& filename);

	float xpos = 0;
	float ypos = 0;

	sf::Drawable* drawable;
	sf::Texture* texture;
};

