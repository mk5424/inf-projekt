#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"paletka.h"
#include"stone.h"

/**
 * @brief klasa reprezentuje pilke w grze
 */
class pilka {

private:

	float x, y;             /**< aktualna pozycja pilki */
	float vx, vy;           /**< predkosc pilki */
	float radius;           /**< promien pilki */
	sf::CircleShape shape;  /**< graficzna reprezentacja pilki */

public:

	/**
	 * @brief konstruktor inicjalizuje polozenie predkosc i promien pilki
	 */
	pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);

	/**
	 * @brief przesuwa pilke zgodnie z predkoscia
	 */
	void move();

	/**
	 * @brief odbija pilke wzgledem osi x
	 */
	void bounceX();

	/**
	 * @brief odbija pilke wzgledem osi y
	 */
	void bounceY();

	/**
	 * @brief sprawdza kolizje pilki ze scianami
	 */
	void collideWalls(float width, float height);

	/**
	 * @brief sprawdza kolizje pilki z paletka
	 */
	bool collidePaddle(const paletka& p);

	/**
	 * @brief sprawdza kolizje pilki z blokami
	 */
	bool collideStone(std::vector<Stone>& wektor);

	/**
	 * @brief rysuje pilke na ekranie
	 */
	void draw(sf::RenderTarget& target);

	/**
	 * @brief resetuje pozycje i predkosc pilki
	 */
	void reset(const sf::Vector2f& pos, const sf::Vector2f& vel)
	{
		shape.setPosition(pos);
		x = pos.x;
		y = pos.y;

		vx = vel.x;
		vy = vel.y;
	}

	float getX() const { return x; }
	float getY() const { return y; }
	float getVX() const { return vx; }
	float getVY() const { return vy; }
	float getRadius() const { return radius; }

	sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }
	sf::Vector2f getVelocity() const { return sf::Vector2f(vx, vy); }

};

