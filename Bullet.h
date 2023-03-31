#pragma once
#include <SFML/Graphics.hpp>

struct Bullet
{
	Bullet();
	~Bullet();
	Bullet(float x, float y, float vx = 0, float vy = 0);
	
	static unsigned int ID;
	float vx;
	float vy;
	float x;
	float y;
	int lifetime = 25;

	sf::CircleShape* circle;

	void Update();
	void Draw(sf::RenderWindow&);

};

