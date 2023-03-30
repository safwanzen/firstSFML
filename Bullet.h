#pragma once
#include <SFML/Graphics.hpp>

struct Bullet
{
	Bullet();
	~Bullet();
	Bullet(float x, float y, float vx = 0, float vy = 0);
	
	float vx;
	float vy;
	float x;
	float y;

	sf::CircleShape* circle;

	void Update();
	void Draw(sf::RenderWindow&);
};

