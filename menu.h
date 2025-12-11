#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define MAX_LICZBA_POZIOMOW 4

/**
 * @brief klasa reprezentujaca menu glowne gry
 */
class Menu
{
private:
    /**
     * @brief czcionka uzywana do tekstow menu
     */
    sf::Font font;

    /**
     * @brief kontener przechowujacy elementy tekstowe menu
     */
    std::vector<sf::Text> menu;

    /**
     * @brief indeks aktualnie wybranego elementu menu
     */
    int selectedItem = 0;

public:
    /**
     * @brief konstruktor tworzacy strukture menu
     * @param width szerokosc okna
     * @param height wysokosc okna
     */
    Menu(float width, float height);

    /**
     * @brief destruktor klasy menu
     */
    ~Menu() {};

    /**
     * @brief przesuwa zaznaczenie w gore
     */
    void przesunG();

    /**
     * @brief przesuwa zaznaczenie w dol
     */
    void przesunD();

    /**
     * @brief zwraca indeks aktualnie wybranego elementu
     * @return numer elementu
     */
    int getSelectedItem() { return selectedItem; }

    /**
     * @brief rysuje elementy menu w oknie
     * @param window referencja do okna renderujacego
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief rysuje napis po zakonczeniu gry
     * @param window referencja do okna renderujacego
     */
    void drawKoniec(sf::RenderWindow& window);
};

/**
 * @brief wykonuje opoznienie na podstawie czasu w milisekundach
 * @param opoznienie wartosc opoznienia
 */
void myDelay(int opoznienie);


Menu::Menu(float width, float height)
{
    if (!font.openFromFile("arial (1).ttf"))
        return;

    sf::Text t(font);

    t.setFont(font);
    t.setFillColor(sf::Color::Cyan);
    t.setString("Nowa gra");
    t.setPosition({ width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1 });
    menu.push_back(t);

    t.setFillColor(sf::Color::White);
    t.setString("Ostatnie wyniki");
    t.setPosition({ width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2 });
    menu.push_back(t);

    t.setString("Wczytaj gre");
    t.setPosition({ width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3 });
    menu.push_back(t);

    t.setString("Wyjscie");
    t.setPosition({ width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 4 });
    menu.push_back(t);

    t.setFillColor(sf::Color::Red);
    t.setCharacterSize(80);
    t.setString("PRZEGRALES");
    t.setPosition({ width / 12, height / (MAX_LICZBA_POZIOMOW + 1) * 2 });
    menu.push_back(t);
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        window.draw(menu[i]);
}

void Menu::drawKoniec(sf::RenderWindow& window)
{
    window.draw(menu[4]);
}

void Menu::przesunG()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);

        selectedItem--;
        if (selectedItem < 0)
            selectedItem = MAX_LICZBA_POZIOMOW - 1;

        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);

        selectedItem++;
        if (selectedItem >= MAX_LICZBA_POZIOMOW)
            selectedItem = 0;

        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void myDelay(int opoznienie)
{
    sf::Clock zegar;
    while (true)
    {
        if (zegar.getElapsedTime().asMilliseconds() > opoznienie)
        {
            zegar.restart();
            break;
        }
    }
}

