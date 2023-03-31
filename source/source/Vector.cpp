#include "Vector.h"
#include <math.h>
#include <iostream>

Vector::Vector(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(const float& mult) const
{
	return Vector(x * mult, y * mult);
}

Vector Vector::operator/(const float& div) const
{
	return Vector(x / div, y / div);
}

float Vector::getAngle() const
{
	return std::atan2(y, x);
}

float Vector::getLength() const
{
	return std::sqrt(x * x + y * y);
}

void Vector::setAngle(float angle)
{
	float length = this->getLength();
	x = std::cos(angle) * length;
	y = std::sin(angle) * length;
}

void Vector::setLength(float length)
{
	float angle = this->getAngle();
	x = std::cos(angle) * length;
	y = std::sin(angle) * length;
}

void Vector::add(const Vector& other)
{
	x += other.x;
	y += other.y;
}

void Vector::subtract(const Vector& other)
{ 
	x -= other.x;
	y -= other.y;
}

