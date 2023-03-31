#pragma once

struct Vector 
{
	float x = 0;
	float y = 0;

	Vector(float x, float y);
	Vector() {};

	float getAngle() const;
	float getLength() const;

	void setAngle(float angle);
	void setLength(float length);

	void add(const Vector&);
	void subtract(const Vector&);

	Vector operator+(const Vector&) const;
	Vector operator-(const Vector&) const;
	Vector operator*(const float&) const;
	Vector operator/(const float&) const;
};