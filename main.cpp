#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "pilka.h"
#include <iostream>
#include "stone.h"
#include <vector>


int main() {
	const float WIDTH = 640.f;
	const float HEIGHT = 480.f;

	const int ILOSC_KOLUMN = 6;
	const int ILOSC_WIERSZY = 7;
	const float ROZMIAR_BLOKU_Y = 25.f;
	const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

	const float PRZERWA = 2.f;

	std::vector<Stone> bloki;

	for (int y = 0; y < ILOSC_WIERSZY; ++y)
	{
		for (int x = 0; x < ILOSC_KOLUMN; ++x)
		{
			float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
			float posY = 50.f + y * (ROZMIAR_BLOKU_Y + PRZERWA);

			int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

			bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
		}
	}

	sf::RenderWindow window(sf::VideoMode({ (unsigned)WIDTH, (unsigned)HEIGHT }), "Arkanoid"); 
	window.setFramerateLimit(60);

	paletka pal(320.f, 440.f, 8.f, 20.f, 200.f); // x,y,szer,wys, predkosc 
	pilka pilka(320.f, 250.f, 8.f, 6.f, 8.f); // x,y,vx,vy,radius

	int licznikKlatek = 0;


	while (window.isOpen()) {


		pal.moveLeft();
		pal.moveRight();
		pal.clampToBounds(WIDTH);
		pilka.move();
		pilka.collideWalls(WIDTH, HEIGHT);


		if (pilka.collideStone(bloki)) { 
			std::cout << "HIT BLOCK\n"; 
		}

		if (pilka.collidePaddle(pal)) {
			std::cout << "HIT PADDLE\n";
		}

		if (pilka.getY() - pilka.getRadius() > HEIGHT) {
			std::cout << "MISS! KONIEC GRY\n";
			window.close();
		}

		if (licznikKlatek % 60 == 0) {
			std::cout << "x=" << pilka.getX() << " y=" << pilka.getY() << " vx=" << pilka.getVX() << " vy=" << pilka.getVY() << std::endl;
		}

		licznikKlatek++;

		window.clear(sf::Color(20, 20, 30));
		pal.draw(window);
		pilka.draw(window);
		for (const auto& b : bloki) {
			b.draw(window);
		}
		window.display();

	}

}