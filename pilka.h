#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"paletka.h"
#include"stone.h"

class pilka {

	private:

	float x, y;
	float vx, vy;
	float radius;
	sf::CircleShape shape;
	
	public:

	pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);
	
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	bool collidePaddle(const paletka &p);
	bool collideStone(std::vector<Stone>& wektor);
	void draw(sf::RenderTarget& target);

	float getX() const { return x; }
	float getY() const { return y; }
	float getVX() const { return vx; }
	float getVY() const { return vy; }
	float getRadius() const { return radius; }


};

pilka::pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in) {
	x = x_in;
	y = y_in;
	vx = vx_in;
	vy = vy_in;
	radius = r_in;

	shape.setRadius(radius);
	shape.setOrigin({ radius, radius });
	shape.setPosition({ x, y });
	shape.setFillColor(sf::Color::Red);
}

void pilka::move() {
	x += vx;
	y += vy;
	shape.setPosition({ x, y });
}

void pilka::bounceX() {
	vx = -vx;
}

void pilka::bounceY() {
	vy = -vy;
}

void pilka::collideWalls(float width, float height) {
	if (x - radius <= 0.f || x + radius >= width) {
		bounceX();
	}
	if (y - radius <= 0.f) {
		bounceY();
	}
}

bool pilka::collidePaddle(const paletka& p) {
	float lewo = p.getX() - p.getSzerokosc() / 2.f;
	float prawo = p.getX() + p.getSzerokosc() / 2.f;
	float gora = p.getY() - p.getWysokosc() / 2.f;

	if (x >= lewo && x <= prawo) {
		if ((y + radius) >= gora && (y - radius) < gora) {
			vy = -std::abs(vy);
			y = gora - radius;
			shape.setPosition({ x,y });
			return true;
		}
	}
	return false;
}

bool pilka::collideStone(std::vector<Stone>& wektor) {


	for (auto& b : wektor)
	{
		if (b.isDestroyed())
			continue;

		float lewo = b.getPosition().x;
		float gora = b.getPosition().y;
		float prawo = lewo + b.getSize().x;
		float dol = gora + b.getSize().y;

		if((x + radius > lewo) && (x - radius < prawo) && (y + radius > gora) && (y - radius < dol))  {
			b.trafienie();
			if (y < gora || y > dol)
				bounceY();
			else
				bounceX();
			return true;
		}
	}
	return false;
}


void pilka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}
