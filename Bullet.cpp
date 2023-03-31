#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{
	ID++;
}

Bullet::~Bullet()
{
	delete circle;
}

Bullet::Bullet(float x, float y, float vx, float vy, uint32_t id)
{
	circle = new sf::CircleShape(5);
	circle->setOrigin(5, 5);
	circle->setFillColor(sf::Color::Yellow);
	circle->setPosition(x, y);
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	ID = id;
}

void Bullet::Update() {
	x += vx;
	y += vy;
	lifetime--;
	std::cout << "bullet " << ID << " life " << lifetime << "\n";
}

void Bullet::Draw(sf::RenderWindow& window)
{
	circle->setPosition(x, y);
	window.draw(*circle);
}

