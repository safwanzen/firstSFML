#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Bullet.h"
#include "Vector.h"
#include "GameObject.h"

#define PI 3.1425

enum State {
	STANDING,
	STANDING_SLASH,
	RUNNING,
	RUNNING_SLASH
};

State action = State::STANDING;
bool runningSlash = false;
int combo = 0;

float radius = 10.f;
constexpr sf::Int64 ticktimems = 1000000 / 60;
unsigned int width = 320, height = 240;
sf::RenderWindow window(sf::VideoMode(width, height), "testo");

float x = 100, y = 100;
float vx = 0.f, vy = 0.f;
float ax = 0.f, ay = 0.f;
float a = .5f;
float maxv = 5.f;

Vector acc;
Vector vel;

bool u = false, d = false, l = false, r = false;
float dir = 0;
bool drag = false;
float bulletspeed = 10;
uint32_t bulletID = 0;

std::vector<Bullet*> bullets;

void DrawObject(GameObject g);

float distance(sf::Vector2f v1, sf::Vector2f v2) {
	auto diff = v2 - v1;
	float dist = std::sqrt(diff.y * diff.y + diff.x * diff.x);
	return std::abs(dist);
}

void fire(float xpos, float ypos, float vx = 0, float vy = 0) {
	bullets.push_back(new Bullet(xpos, ypos, vx, vy, bulletID));
	bulletID++;
}

int main()
{
	sf::CircleShape shape(radius);

	sf::Clock clock;

	shape.setOrigin(radius, radius);
	shape.setFillColor(sf::Color::Green);

	int sw = 39;
	int sh = 49;
	float rectx = 0, recty = 0;

	sf::Texture tx;
	sf::Image img;
	if (!img.loadFromFile("sprites/Untitledzz.png")) return EXIT_FAILURE;
	img.createMaskFromColor(sf::Color(32, 128, 192));
	tx.loadFromImage(img);
	//tx.create(sw, sh);
	sf::Sprite sprite(tx);
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(rectx * sw, recty), sf::Vector2i(sw, sh)));
	sprite.setOrigin(19, 25);
	sprite.setPosition(200, 200);
	int flip = 1;
	sprite.setScale(flip, 1);

	int sbw = 75;
	int sbh = 30;
	float rectbx = 0, rectby = 0;
	bool playsaber = false;

	// running slash
	sf::Texture txsaber;
	sf::Image imgsaber;
	if (!imgsaber.loadFromFile("sprites/Untitledsaber.png")) return EXIT_FAILURE;
	imgsaber.createMaskFromColor(sf::Color(32, 128, 192));
	txsaber.loadFromImage(imgsaber);
	//tx.create(sw, sh);
	sf::Sprite spritesaber(txsaber);
	spritesaber.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * sbw, rectby), sf::Vector2i(sbw, sbh)));
	spritesaber.setOrigin(32, 15);
	spritesaber.setPosition(200, 200);
	spritesaber.setScale(flip, 1);

	// combo 1
	sf::Texture txsaberc1;
	if (!imgsaber.loadFromFile("sprites/Untitledc1_8f.png")) return EXIT_FAILURE;
	imgsaber.createMaskFromColor(sf::Color(32, 128, 192));
	txsaberc1.loadFromImage(imgsaber);
	//tx.create(sw, sh);
	sf::Sprite spritesaberc1(txsaberc1);
	spritesaberc1.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 72, rectby), sf::Vector2i(72, 42)));
	spritesaberc1.setOrigin(15, 17);
	spritesaberc1.setPosition(200, 200);
	spritesaberc1.setScale(flip, 1);

	// combo 2
	sf::Texture txsaberc2;
	if (!imgsaber.loadFromFile("sprites/Untitledc2_9f.png")) return EXIT_FAILURE;
	imgsaber.createMaskFromColor(sf::Color(32, 128, 192));
	txsaberc2.loadFromImage(imgsaber);
	//tx.create(sw, sh);
	sf::Sprite spritesaberc2(txsaberc2);
	spritesaberc2.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 66, rectby), sf::Vector2i(66, 48)));
	spritesaberc2.setOrigin(10, 20);
	spritesaberc2.setPosition(200, 200);
	spritesaberc2.setScale(flip, 1);

	// combo 3
	sf::Texture txsaberc3;
	if (!imgsaber.loadFromFile("sprites/Untitledc3_11f.png")) return EXIT_FAILURE;
	imgsaber.createMaskFromColor(sf::Color(32, 128, 192));
	txsaberc3.loadFromImage(imgsaber);
	//tx.create(sw, sh);
	sf::Sprite spritesaberc3(txsaberc3);
	spritesaberc3.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 80, rectby), sf::Vector2i(80, 59)));
	spritesaberc3.setOrigin(20, 34);
	spritesaberc3.setPosition(200, 200);
	spritesaberc3.setScale(flip, 1);

	GameObject zero;
	zero.texture->loadFromImage(img);
	zero.drawable = new sf::Sprite(*zero.texture);

	sf::ConvexShape polygon;

	while (window.isOpen())
	{
		auto start = clock.getElapsedTime();

		// event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) { u = true; }
				if (event.key.code == sf::Keyboard::S) { d = true; }
				if (event.key.code == sf::Keyboard::A) { l = true; }
				if (event.key.code == sf::Keyboard::D) { r = true; }
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W) { u = false; }
				if (event.key.code == sf::Keyboard::S) { d = false; }
				if (event.key.code == sf::Keyboard::A) { l = false; }
				if (event.key.code == sf::Keyboard::D) { r = false; }
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (action == STANDING_SLASH) {
						if (combo == 0 && rectbx > 2) {
							combo++;
							rectbx = 0;
						}
						else if (combo == 1 && rectbx > 3) {
							combo++;
							rectbx = 0;
						}
					}
					if (action == STANDING) action = STANDING_SLASH;
					if (action == RUNNING) runningSlash = true;
					/*sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
					sf::Vector2f dir = mousepos - shape.getPosition();
					float dist = distance(mousepos, shape.getPosition());
					float dirx = dir.x / dist * bulletspeed;
					float diry = dir.y / dist * bulletspeed;
					if (dist < radius + 4.f) { drag = true; }
					else fire((float)x, (float)y, dirx, diry);*/
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					if (action == STANDING_SLASH && combo == 1 && rectbx > 3) {
						combo = 3; // rising slash
						rectbx = 0;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					drag = false;
				}
			}
		}

		// update
		if (action != State::STANDING_SLASH) {
			Vector aa;
			aa.setLength(2);
			if (u) aa.setAngle(PI * 1.5);
			else if (d) aa.setAngle(PI * .5);
			else if (l) {
				flip = -1;
				aa.setAngle(PI);
			}
			else if (r) {
				flip = 1;
				aa.setAngle(0);
			}

			if (u && r) aa.setAngle(PI * 1.75);
			else if (u && l) aa.setAngle(PI * 1.25);
			else if (d && r) aa.setAngle(PI * .25);
			else if (d && l) aa.setAngle(PI * .75);

			if (!u && !d && !l && !r) aa.setLength(0);

			vel.add(aa);
			if (vel.getLength() > 5) vel.setLength(5);

			x += vel.x;
			y += vel.y;

			// apply deceleration
			float _v = vel.getLength();
			_v -= 0.8;
			vel.setLength(_v);
			if (vel.getLength() < 0.9) vel.setLength(0);
		}
		/*else {
			vel.setLength(0);
			auto pos = sf::Mouse::getPosition(window);
			x = pos.x;
			y = pos.y;
		}*/

		shape.setPosition(x, y);
		sprite.setScale(flip, 1);
		sprite.setPosition(x, 200);

		// update rect
		if (vel.getLength() > 0 || l || r) {
			rectx += 0.1;
			if (rectx > 4) rectx = 0;
		}
		else rectx = 4; // standing sprite

		sprite.setTextureRect(sf::IntRect(sf::Vector2i((int)rectx * sw, recty), sf::Vector2i(sw, sh)));

		if (action == State::STANDING_SLASH) {
			vel.setLength(0);
			if (combo == 0) {
				rectbx += 0.5;
				if (rectbx > 7) {
					rectbx = 0;
					combo = 0;
					action = State::STANDING;
				}
				spritesaberc1.setPosition(x, 195);
				spritesaberc1.setScale(flip, 1);
				spritesaberc1.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 72, rectby), sf::Vector2i(72, 42)));
			}
			else if (combo == 1) {
				rectbx += 0.5;
				if (rectbx > 8) {
					rectbx = 0;
					combo = 0;
					action = State::STANDING;
				}
				spritesaberc2.setPosition(x, 195);
				spritesaberc2.setScale(flip, 1);
				spritesaberc2.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 66, rectby), sf::Vector2i(66, 48)));
			}
			else if (combo == 2) {
				rectbx += 0.48;
				if (rectbx > 11) {
					rectbx = 0;
					combo = 0;
					action = State::STANDING;
				}
				spritesaberc3.setPosition(x, 195);
				spritesaberc3.setScale(flip, 1);
				spritesaberc3.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * 80, rectby), sf::Vector2i(80, 59)));
			}
		}

		else if (runningSlash)
		{
			rectbx += 0.5;
			if (rectbx > 6) {
				rectbx = 0;
				runningSlash = false;
			}
			spritesaber.setPosition(x, 195);
			spritesaber.setScale(flip, 1);
			spritesaber.setTextureRect(sf::IntRect(sf::Vector2i((int)rectbx * sbw, rectby), sf::Vector2i(sbw, sbh)));
		}


		// update bullets
		int i = 0;
		for (auto b : bullets) {
			b->Update();
			if (b->lifetime < 0) bullets.erase(bullets.begin() + i);
			i++;
		}

		// polygon
		/*
		polygon.setPointCount(3);
		polygon.setPoint(0, sf::Vector2f(0, 0));
		polygon.setPoint(1, sf::Vector2f(0, 10));
		polygon.setPoint(2, sf::Vector2f(25, 5));
		polygon.setOutlineColor(sf::Color::Green);
		polygon.setFillColor(sf::Color::Green);
		polygon.setOutlineThickness(2);
		polygon.setPosition(300, 300);*/

		// draw
		window.clear();
		if (action == State::STANDING) window.draw(sprite);
		else if (action == State::STANDING_SLASH && combo == 0) window.draw(spritesaberc1);
		else if (action == State::STANDING_SLASH && combo == 1) window.draw(spritesaberc2);
		else if (action == State::STANDING_SLASH && combo == 2) window.draw(spritesaberc3);
		if (runningSlash) window.draw(spritesaber);
		//window.draw(shape);
		//window.draw(polygon);
		for (auto b : bullets) { b->Draw(window); }
		window.display();

		// sleep
		auto end = clock.restart();
		auto elapsed = end - start;

		sf::sleep(sf::microseconds(ticktimems - elapsed.asMicroseconds()));
		//std::cout << elapsed.asMilliseconds() << "\n";
	}

	return 0;
}

void DrawObject(GameObject obj) {
	window.draw(*obj.drawable);
}