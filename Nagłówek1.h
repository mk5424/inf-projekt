#pragma once
// Pliki: Stone.h, Stone.cpp oraz snippet do wstawienia w main.cpp
// Instrukcja: Wklej Stone.h i Stone.cpp do swojego projektu, do³¹cz do main.cpp i skompiluj z SFML
// (np. g++ main.cpp Stone.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system)

// ===== Stone.h =====
#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;

public:
    // Konstruktor
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);

    // Metody
    void trafienie();
    void aktualizujKolor();
    bool isDestroyed() const { return m_jestZniszczony; }

    // W³asna metoda rysuj¹ca (nie nadpisujemy wirtualnego draw SFML, tylko udostêpniamy pomocnicz¹)
    void draw(sf::RenderTarget& target) const;
};

// ===== Stone.cpp =====
#include "Stone.h"

// Definicja statycznej tablicy kolorów
const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, // L = 0
    sf::Color::Red,         // L = 1
    sf::Color::Yellow,      // L = 2
    sf::Color::Blue         // L = 3
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
    : sf::RectangleShape(rozmiar)
    , m_punktyZycia(L)
    , m_jestZniszczony(false)
{
    this->setPosition(startPos);
    this->setSize(rozmiar); // konstruktor ju¿ ustawi³ rozmiar, ale to jest zgodne z wymaganiem
    this->setOutlineThickness(2.f);
    this->setOutlineColor(sf::Color::Black);
    this->aktualizujKolor();
}

void Stone::trafienie()
{
    if (m_jestZniszczony)
        return;

    --m_punktyZycia;
    aktualizujKolor();

    if (m_punktyZycia <= 0)
    {
        m_jestZniszczony = true;
        // opcjonalnie: ukryj wype³nienie
        this->setFillColor(sf::Color::Transparent);
    }
}

void Stone::aktualizujKolor()
{
    // zabezpieczenie przed wyjœciem poza zakres
    if (m_punktyZycia >= 0 && m_punktyZycia < static_cast<int>(m_colorLUT.size()))
    {
        this->setFillColor(m_colorLUT[m_punktyZycia]);
    }
    else if (m_punktyZycia < 0)
    {
        this->setFillColor(sf::Color::Transparent);
    }
    else
    {
        // je¿eli liczba punktów ¿ycia wiêksza ni¿ LUT, u¿yj koloru najwy¿szego indeksu
        this->setFillColor(m_colorLUT.back());
    }
}

void Stone::draw(sf::RenderTarget& target) const
{
    if (!m_jestZniszczony)
    {
        // rysujemy jako RectangleShape (rzutujemy const)
        target.draw(static_cast<const sf::RectangleShape&>(*this));
    }
}

// ===== Snippet do main.cpp (wstaw przed pêtl¹ g³ówn¹) =====

#include "Stone.h"
#include <vector>

// Zak³adam, ¿e masz zdefiniowane SZEROKOSC i WYSOKOSC (np. const unsigned int SZEROKOSC = 800;)

//std::vector<Stone> bloki;

const int ILOSC_KOLUMN = 6;
const int ILOSC_WIERSZY = 7;
const float ROZMIAR_BLOKU_Y = 25.f;
const float PRZERWA = 2.f; // odstêp miêdzy blokami

const float ROZMIAR_BLOKU_X = (static_cast<float>(SZEROKOSC) - (ILOSC_KOLUMN - 1) * GAP) / ILOSC_KOLUMN;

for (int y = 0; y < ILOSC_WIERSZY; ++y)
{
    for (int x = 0; x < ILOSC_KOLUMN; ++x)
    {
        float posX = x * (ROZMIAR_BLOKU_X + GAP);
        float posY = 50.f + y * (ROZMIAR_BLOKU_Y + GAP); // offset od góry = 50.f

        int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

        bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
    }
}

// W pêtli rysowania (np. przed rysowaniem pi³ki i paletki):
for (const auto &b : bloki)
    b.draw(window);

// Przy kolizji pi³ki z blokiem: wywo³aj b.trafienie();
// Jeœli chcesz usuwaæ zniszczone bloki z wektora, mo¿esz filtr(erase-remove) je po pêtli kolizji:
// bloki.erase(std::remove_if(bloki.begin(), bloki.end(), [](const Stone &s){ return s.isDestroyed(); }), bloki.end());
*/

// ===== Koniec =====
