#pragma once
#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "pilka.h"
#include "stone.h"
#include <fstream>
#include <string>

/**
 * @brief struktura reprezentujaca dane pojedynczego bloku
 */
struct BlockData {
    float x;
    float y;
    int hp;
};

/**
 * @brief klasa reprezentujaca i zapisujaca stan gry
 */
class gameState
{
private:
    /** pozycja paletki */
    sf::Vector2f paddlePosition;

    /** pozycja pilki */
    sf::Vector2f ballPosition;

    /** predkosc pilki */
    sf::Vector2f ballVelocity;

    /** dane wszystkich blokow */
    std::vector<BlockData> blocks;

public:

    /**
     * @brief konstruktor domyslny
     */
    gameState() = default;

    /**
     * @brief konstruktor zapisujacy aktualny stan gry
     */
    gameState(const paletka& paddle,
        const pilka& ball,
        const std::vector<Stone>& stones)
    {
        capture(paddle, ball, stones);
    }

    /**
     * @brief kopiuje stan gry z podanych obiektow
     */
    void capture(const paletka& paddle,
        const pilka& ball,
        const std::vector<Stone>& stones)
    {
        paddlePosition = paddle.getPosition();
        ballPosition = ball.getPosition();
        ballVelocity = ball.getVelocity();

        blocks.clear();
        blocks.reserve(stones.size());

        for (const auto& s : stones)
        {
            BlockData data;
            data.x = s.getPosition().x;
            data.y = s.getPosition().y;
            data.hp = s.getHP();
            blocks.push_back(data);
        }
    }

    /** @brief pobiera pozycje paletki */
    const sf::Vector2f& getPaddlePos() const { return paddlePosition; }

    /** @brief pobiera pozycje pilki */
    const sf::Vector2f& getBallPos() const { return ballPosition; }

    /** @brief pobiera predkosc pilki */
    const sf::Vector2f& getBallVel() const { return ballVelocity; }

    /** @brief pobiera dane blokow */
    const std::vector<BlockData>& getBlocks() const { return blocks; }

    /**
     * @brief zapisuje stan gry do pliku
     * @param filename nazwa pliku
     * @return true jesli zapis sie powiodl
     */
    bool saveToFile(const std::string& filename)
    {
        std::ofstream file(filename);

        if (!file.is_open())
            return false;

        file << paddlePosition.x << " " << paddlePosition.y << "\n";
        file << ballPosition.x << " " << ballPosition.y << " "
            << ballVelocity.x << " " << ballVelocity.y << "\n";

        file << blocks.size() << "\n";

        for (const auto& b : blocks)
        {
            file << b.x << " " << b.y << " " << b.hp << "\n";
        }

        file.close();
        return true;
    }

    /**
     * @brief wczytuje stan gry z pliku
     * @param filename nazwa pliku
     * @return true jesli odczyt sie powiodl
     */
    bool loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        if (!(file >> paddlePosition.x >> paddlePosition.y))
            return false;

        if (!(file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y))
            return false;

        int blocksCount;
        if (!(file >> blocksCount))
            return false;

        blocks.clear();
        for (int i = 0; i < blocksCount; ++i)
        {
            float x, y;
            int hp;
            if (!(file >> x >> y >> hp))
                return false;

            blocks.push_back({ x, y, hp });
        }

        file.close();
        return true;
    }

    /**
     * @brief naklada zapisany stan gry na obiekty w programie
     */
    void apply(paletka& p, pilka& b, std::vector<Stone>& stones)
    {
        p.setPosition(paddlePosition);
        b.reset(ballPosition, ballVelocity);

        stones.clear();

        sf::Vector2f blocksize(105.f, 25.f);

        for (const auto& data : blocks)
        {
            if (data.hp > 0)
                stones.emplace_back(sf::Vector2f(data.x, data.y), blocksize, data.hp);
        }
    }
};
