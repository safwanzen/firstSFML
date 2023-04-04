#include "GameObject.h"

GameObject::GameObject()
{
	texture = new sf::Texture;
	drawable = new sf::Sprite;
}

GameObject::~GameObject()
{
	delete drawable;
}

void GameObject::loadSprite(const std::string& filename)
{
	sf::Image img;
	if (!img.loadFromFile(filename)) return;

    sf::Texture tx;
    img.createMaskFromColor(sf::Color(32, 128, 192));
    tx.loadFromImage(img);
    //tx.create(sw, sh);
    sf::Sprite sprite(tx);
}
