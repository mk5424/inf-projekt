#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {

private:
	int m_punktyZycia;
	bool m_jestZniszczony;
	static const std::array<sf::Color, 4> m_colorLUT;

public:

	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
	void trafienie();
	void aktualizujKolor();

	void draw(sf::RenderTarget& target) const;

	bool isDestroyed() const { return m_jestZniszczony; };
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) {
	m_punktyZycia = L;
	m_jestZniszczony = false;

	this->setPosition(startPos);
	this->setSize(rozmiar);
	this->aktualizujKolor();
	
}

void Stone::trafienie() {
	if (m_jestZniszczony) {
		return;
	}
	--m_punktyZycia;
	if (m_punktyZycia <= 0) {
		m_jestZniszczony = true;
	}
	aktualizujKolor();
}
void Stone::aktualizujKolor() {
	for (int i = 0; i < m_colorLUT.size(); i++) {
		if (m_punktyZycia == i){
			this->setFillColor(m_colorLUT[i]);
		}
	}

}

void Stone::draw(sf::RenderTarget& target) const {
	target.draw(static_cast<const sf::RectangleShape&>(*this));
}



const std::array<sf::Color, 4> Stone::m_colorLUT = {
	sf::Color::Transparent, // L = 0
	sf::Color::Red,         // L = 1
	sf::Color::Yellow,      // L = 2
	sf::Color::Blue         // L = 3
};