#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "stone.h"

/**
 * @brief klasa odpowiedzialna za glowna logike gry
 */
class Game
{
public:
    /**
     * @brief konstruktor inicjalizujacy paletke, pilke i bloki
     */
    Game();

    /**
     * @brief aktualizuje stan gry
     * @param dt delta time
     */
    void update(sf::Time dt);

    /**
     * @brief renderuje wszystkie obiekty gry
     * @param target obiekt renderujacy
     */
    void render(sf::RenderTarget& target);

    /**
     * @brief informacja czy gra zostala zakonczona
     * @return true jesli koniec gry
     */
    bool isGameOver() const { return m_gameOver; }

    /**
     * @brief pobiera (const) paletke
     */
    const paletka& getPaddle() const { return m_paletka; }

    /**
     * @brief pobiera (const) pilke
     */
    const pilka& getBall() const { return m_pilka; }

    /**
     * @brief pobiera (const) bloki
     */
    const std::vector<Stone>& getBlocks() const { return m_bloki; }

    /**
     * @brief pobiera paletke
     */
    paletka& getPaddle() { return m_paletka; }

    /**
     * @brief pobiera pilke
     */
    pilka& getBall() { return m_pilka; }

    /**
     * @brief pobiera bloki
     */
    std::vector<Stone>& getBlocks() { return m_bloki; }

    bool m_gameOver = false;

private:

    /** szerokosc pola gry */
    const float WIDTH = 640.f;

    /** wysokosc pola gry */
    const float HEIGHT = 480.f;

    /** licznik klatek */
    int licznikKlatek = 0;

    /** paletka gracza */
    paletka m_paletka;

    /** pilka */
    pilka m_pilka;

    /** wektor blokow na planszy */
    std::vector<Stone> m_bloki;

    /** liczba kolumn blokow */
    const int ILOSC_KOLUMN = 6;

    /** liczba wierszy blokow */
    const int ILOSC_WIERSZY = 7;

    /** wysokosc bloku */
    const float ROZMIAR_BLOKU_Y = 25.f;

    /** odstep miedzy blokami */
    const float PRZERWA = 2.f;

    /** szerokosc bloku wyliczana automatycznie */
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    /**
     * @brief tworzy uklad blokow na planszy
     */
    void utworzBloki();
};