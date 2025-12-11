#include"pilka.h"

/**
 * @brief konstruktor ustawia parametry pilki i przygotowuje jej wyglad graficzny
 */
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

/**
 * @brief przesuwa pilke o predkosc vx i vy
 */
void pilka::move() {
	x += vx;
	y += vy;
	shape.setPosition({ x, y });
}

/**
 * @brief odbija pilke poziomo
 */
void pilka::bounceX() {
	vx = -vx;
}

/**
 * @brief odbija pilke pionowo
 */
void pilka::bounceY() {
	vy = -vy;
}

/**
 * @brief kolizja pilki ze scianami ekranu
 */
void pilka::collideWalls(float width, float height) {
	if (x - radius <= 0.f || x + radius >= width) {
		bounceX();
	}
	if (y - radius <= 0.f) {
		bounceY();
	}
}

/**
 * @brief kolizja z paletka
 */
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

/**
 * @brief kolizja z blokami
 */
bool pilka::collideStone(std::vector<Stone>& wektor) {

	for (auto& b : wektor)
	{
		if (b.isDestroyed())
			continue;

		float lewo = b.getPosition().x;
		float gora = b.getPosition().y;
		float prawo = lewo + b.getSize().x;
		float dol = gora + b.getSize().y;

		if ((x + radius > lewo) && (x - radius < prawo) && (y + radius > gora) && (y - radius < dol)) {
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

/**
 * @brief rysuje pilke
 */
void pilka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}
