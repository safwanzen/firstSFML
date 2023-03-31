#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"

struct Bullet
{
	Bullet();
	~Bullet();
	Bullet(float x, float y, float vx = 0, float vy = 0, uint32_t id = 0);

	Vector position;
	Vector velocity;

	float vx;
	float vy;
	float x;
	float y;
	uint32_t ID;
	int lifetime = 25;

	sf::CircleShape* circle;

	void Update();
	void Draw(sf::RenderWindow&);

};

