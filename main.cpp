#include "Game.h"
#include "menu.h"
#include "gameState.h"

/** @brief funkcja glowna obsluguje petle gry i zdarzenia */
int main()
{
    enum class GameState
    {
        Menu,
        Playing,
        Scores,
        Exiting,
        Stop,
        Przegrana,
        Playing2
    };

    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "My window");
    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    gameState stop;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                /** @brief obsluguje przesuniecie wskaznika menu w gore */
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    myDelay(250);
                    menu.przesunG();
                }

                /** @brief obsluguje przesuniecie wskaznika menu w dol */
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    myDelay(250);
                    menu.przesunD();
                }

                /** @brief obsluguje zamkniecie gry */
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    myDelay(250);
                    currentState = GameState::Exiting;
                }

                /** @brief przelacza pauze */
                if (keyPressed->scancode == sf::Keyboard::Scancode::P)
                {
                    myDelay(250);

                    if (currentState == GameState::Stop)
                        currentState = GameState::Playing;
                    else if (currentState == GameState::Playing)
                        currentState = GameState::Stop;
                }

                /** @brief zapisuje aktualny stan gry do pliku */
                if (keyPressed->scancode == sf::Keyboard::Scancode::F5)
                {
                    myDelay(250);

                    stop.capture(
                        game.getPaddle(),
                        game.getBall(),
                        game.getBlocks()
                    );

                    if (stop.saveToFile("zapis.txt"))
                        std::cout << "Gra zapisana!\n";
                    else
                        std::cout << "Blad zapisu pliku!\n";
                }

                /** @brief obsluguje wybor opcji menu */
                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                {
                    if (menu.getSelectedItem() == 0) currentState = GameState::Playing;
                    if (menu.getSelectedItem() == 1) currentState = GameState::Scores;
                    if (menu.getSelectedItem() == 2) currentState = GameState::Playing2;
                    if (menu.getSelectedItem() == 3) currentState = GameState::Exiting;
                }
            }
        }

        window.clear();

        /** @brief rysuje menu glowne */
        if (currentState == GameState::Menu)
            menu.draw(window);

        else if (currentState == GameState::Przegrana) {
            menu.drawKoniec(window);
            game.m_gameOver = false;
            window.display();
            myDelay(1500);
            currentState = GameState::Menu;
        }

        /** @brief aktualizuje i wyswietla gre */
        else if (currentState == GameState::Playing)
        {
            if (game.isGameOver()) {
                currentState = GameState::Przegrana;
                continue;
            }
            game.update(dt);
            game.render(window);
        }

        /** @brief wczytuje zapis gry */
        else if (currentState == GameState::Playing2) {
            gameState loaded;
            if (loaded.loadFromFile("zapis.txt"))
            {
                std::cout << "Gra wczytana!\n";

                loaded.apply(
                    game.getPaddle(),
                    game.getBall(),
                    game.getBlocks()
                );
            }
            else
            {
                std::cout << "Blad odczytu pliku!\n";
            }
            currentState = GameState::Playing;
        }

        /** @brief zamyka aplikacje */
        else if (currentState == GameState::Exiting)
            window.close();

        /** @brief renderuje gre w trybie pauzy */
        else if (currentState == GameState::Stop) {
            stop.capture(game.getPaddle(), game.getBall(), game.getBlocks());
            game.render(window);
        }

        window.display();
    }

    return 0;
}
