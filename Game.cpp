#include "Game.h"
#include <iostream>

/**
 * @brief konstruktor gry inicjalizuje paletke, pilke oraz bloki
 */
Game::Game()
    : m_paletka(320.f, 440.f, 0.4, 20.f, 200.f)
    , m_pilka(320.f, 250.f, 0.3, 0.25, 16.f)
{
    Game::utworzBloki();
}

/**
 * @brief tworzy wszystkie bloki na planszy
 */
void Game::utworzBloki() {
    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + PRZERWA);

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
}

/**
 * @brief glowna petla aktualizacji gry
 * @param dt delta time
 */
void Game::update(sf::Time dt)
{
    m_paletka.moveLeft();
    m_paletka.moveRight();
    m_paletka.clampToBounds(WIDTH);

    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    if (m_pilka.collideStone(m_bloki))
        std::cout << "HIT BLOCK\n";

    if (m_pilka.collidePaddle(m_paletka))
        std::cout << "HIT PADDLE\n";

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        m_paletka.setPosition({ 320.f, 440.f });
        m_pilka.reset({ 320.f, 250.f }, { 0.3, 0.25 });
        m_bloki.clear();
        utworzBloki();
        m_gameOver = true;
        std::cout << "MISS KONIEC GRY\n";
    }

    if (licznikKlatek % 240 == 0)
        std::cout << "x=" << m_pilka.getX()
        << " y=" << m_pilka.getY()
        << " vx=" << m_pilka.getVX()
        << " vy=" << m_pilka.getVY()
        << std::endl;

    licznikKlatek++;
}

/**
 * @brief renderuje wszystkie obiekty gry
 * @param target obiekt renderujacy
 */
void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (const auto& b : m_bloki)
        b.draw(target);
}
