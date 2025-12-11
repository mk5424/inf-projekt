#pragma once
#include <SFML/Graphics.hpp>
#include <array>

/**
 * @brief klasa reprezentuje pojedynczy blok w grze
 */
class Stone : public sf::RectangleShape {

private:
	int m_punktyZycia;                /**< liczba punktow zycia bloku */
	bool m_jestZniszczony;            /**< czy blok zostal zniszczony */
	static const std::array<sf::Color, 4> m_colorLUT; /**< tabela kolorow zalezne od hp */

public:

	/**
	 * @brief konstruktor ustawia pozycje rozmiar i hp bloku
	 */
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);

	/**
	 * @brief zmniejsza hp bloku po trafieniu
	 */
	void trafienie();

	/**
	 * @brief aktualizuje kolor bloku zalezne od hp
	 */
	void aktualizujKolor();

	/**
	 * @brief rysuje blok na ekranie
	 */
	void draw(sf::RenderTarget& target) const;

	bool isDestroyed() const { return m_jestZniszczony; };

	int getHP() const { return m_punktyZycia; }
};
