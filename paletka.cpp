#include "paletka.h"

/**
 * @brief konstruktor ustawiajacy parametry i wyglad paletki
 */
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

/**
 * @brief przesuwa paletke w lewo przy wcisnieciu klawiszy A lub LEFT
 */
void paletka::moveLeft() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        x -= v;
        shape.setPosition({ x, y });
    }
}

/**
 * @brief przesuwa paletke w prawo przy wcisnieciu klawiszy D lub RIGHT
 */
void paletka::moveRight() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        x += v;
        shape.setPosition({ x, y });
    }
}

/**
 * @brief zatrzymuje paletke na granicach pola gry
 * @param szerokoscPola szerokosc planszy
 */
void paletka::clampToBounds(float szerokoscPola) {
    if (x - szerokosc / 2.f <= 0.f) {
        x = szerokosc / 2.f;
        shape.setPosition({ x, y });
    }
    if (x + szerokosc / 2.f >= szerokoscPola) {
        x = szerokoscPola - szerokosc / 2.f;
        shape.setPosition({ x, y });
    }
}

/**
 * @brief rysuje paletke na ekranie
 */
void paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}
