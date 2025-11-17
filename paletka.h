#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

class paletka {

private:

	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float v;

	sf::RectangleShape shape;

public:

	paletka(float x_in, float y_in, float v_in, float h_in, float w_in);

	void moveLeft();
	void moveRight();
	void clampToBounds(float szerokoscPola);
	void draw(sf::RenderTarget& target);

	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }

};

paletka::paletka(float x_in, float y_in, float v_in, float h_in, float w_in) {

	x = x_in;
	y = y_in;
	v = v_in;
	szerokosc = w_in;
	wysokosc = h_in;

	shape.setSize({ szerokosc, wysokosc });
	shape.setOrigin({ szerokosc / 2.f, wysokosc / 2.f });
	shape.setPosition({ x, y });
	shape.setFillColor(sf::Color::Blue);


}

void paletka::moveLeft() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		x -= v;
		shape.setPosition({ x, y });
	}
}

void paletka::moveRight() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		x += v;
		shape.setPosition({ x, y });
	}
}

void paletka::clampToBounds(float szerokoscPola) {
	if (x - szerokosc/2.f <= 0.f) {
		x = szerokosc / 2.f;
		shape.setPosition({ x,y });
	}
	if (x + szerokosc / 2.f >= szerokoscPola) {
		x = szerokoscPola - szerokosc / 2.f;
		shape.setPosition({ x,y });
	}

}
void paletka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}