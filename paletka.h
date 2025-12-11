#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @brief klasa reprezentujaca paletke gracza
 */
class paletka
{
private:
    /**
     * @brief pozycja x paletki
     */
    float x;

    /**
     * @brief pozycja y paletki
     */
    float y;

    /**
     * @brief szerokosc paletki
     */
    float szerokosc;

    /**
     * @brief wysokosc paletki
     */
    float wysokosc;

    /**
     * @brief predkosc ruchu paletki
     */
    float v;

    /**
     * @brief graficzna reprezentacja paletki jako prostokat
     */
    sf::RectangleShape shape;

public:
    /**
     * @brief konstruktor ustawiajacy parametry paletki
     * @param x_in pozycja x
     * @param y_in pozycja y
     * @param v_in predkosc
     * @param h_in wysokosc
     * @param w_in szerokosc
     */
    paletka(float x_in, float y_in, float v_in, float h_in, float w_in);

    /**
     * @brief przesuwa paletke w lewo
     */
    void moveLeft();

    /**
     * @brief przesuwa paletke w prawo
     */
    void moveRight();

    /**
     * @brief ogranicza ruch paletki do szerokosci okna
     * @param szerokoscPola maksymalna szerokosc pola gry
     */
    void clampToBounds(float szerokoscPola);

    /**
     * @brief rysuje paletke
     * @param target obiekt renderujacy
     */
    void draw(sf::RenderTarget& target);

    /**
     * @brief ustawia pozycje paletki
     */
    void setPosition(const sf::Vector2f& pos)
    {
        shape.setPosition(pos);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }

    /**
     * @brief zwraca aktualna pozycje paletki jako wektor
     */
    sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }
};
