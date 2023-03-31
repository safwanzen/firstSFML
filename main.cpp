#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Bullet.h"

float radius = 10.f;
constexpr sf::Int64 ticktimems = 1000000 / 60;
unsigned int width = 500, height = 500;

float x = 100, y = 100;
float vx = 0.f, vy = 0.f;
float ax = 0.f, ay = 0.f;
float a = .5f;
float maxv = 5.f;

bool u = false, d = false, l = false, r = false;
float dir = 0;
bool drag = false;
float bulletspeed = 10;

std::vector<Bullet*> bullets;

float distance(sf::Vector2f v1, sf::Vector2f v2) {
    auto diff = v2 - v1;
    float dist = std::sqrt(diff.y * diff.y + diff.x * diff.x);
    return std::abs(dist);
}

void fire(float xpos, float ypos, float vx = 0, float vy = 0) {
    bullets.push_back(new Bullet(xpos, ypos, vx, vy));
}

int main()
{
    sf::CircleShape shape(radius);

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    sf::Clock clock;

    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::Green);

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
                    sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2f dir = mousepos - shape.getPosition();
                    float dist = distance(mousepos, shape.getPosition());
                    float dirx = dir.x / dist * bulletspeed;
                    float diry = dir.y / dist * bulletspeed;
                    fire((float)x, (float)y, dirx, diry);
                    //fire(event.mouseButton.x, event.mouseButton.y, dir.x, dir.y);
                    /*sf::Vector2f mousepos(event.mouseButton.x, event.mouseButton.y);
                    float dist = distance(mousepos, shape.getPosition());
                    std::cout << "distance -> " << dist << "\n";
                    if (dist < radius + 4.f) { drag = true; }*/
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    drag = false;
                }
            }
        }

        // update
        if (!drag) {
            if (u) vy -= a;
            if (d) vy += a;
            if (l) vx -= a;
            if (r) vx += a;

            if (vx > maxv) vx = maxv;
            if (vy > maxv) vy = maxv;
            if (vx < -maxv) vx = -maxv;
            if (vy < -maxv) vy = -maxv;

            x += vx;
            y += vy;
        }
        else {
            vx = vy = 0;
            auto pos = sf::Mouse::getPosition(window);
            x = pos.x;
            y = pos.y;
        }

        shape.setPosition(sf::Vector2f(x, y));

        // update bullets
        int i = 0;
        for (auto b : bullets) { 
            b->Update(); 
            if (b->lifetime < 0) bullets.erase(bullets.begin() + i);
            i++;
        }

        // draw
        window.clear();
        window.draw(shape);
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

void update(sf::RenderWindow& window, float deltaTime) {
    
}

void bounceToRandomDir() {

}