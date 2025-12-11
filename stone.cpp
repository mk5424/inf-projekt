#include"stone.h"

/** @brief konstruktor inicjuje polozenie rozmiar i liczbe punktow zycia */
Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) {
    m_punktyZycia = L;
    m_jestZniszczony = false;

    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->aktualizujKolor();
}

/** @brief zmniejsza punkty zycia i aktualizuje kolor obiektu */
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

/** @brief ustawia kolor w zaleznosci od liczby punktow zycia */
void Stone::aktualizujKolor() {
    for (int i = 0; i < m_colorLUT.size(); i++) {
        if (m_punktyZycia == i) {
            this->setFillColor(m_colorLUT[i]);
        }
    }
}

/** @brief rysuje obiekt na render target */
void Stone::draw(sf::RenderTarget& target) const {
    target.draw(static_cast<const sf::RectangleShape&>(*this));
}

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};
