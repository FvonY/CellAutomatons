#include "stdafx.h"

#include "Conway.h"
#include "Automaton.h"

void resetState(int* state, int cells)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int y = 0; y < cells; y++)
    {
        for (int x = 0; x < cells; x++)
        {
            *(state + x + cells * y) = dis(gen);
        }
    }
}

int main()
{   
    sf::RenderWindow window(sf::VideoMode(800, 800), "#LebenIstLava");
    window.setFramerateLimit(15);

    sf::Clock clock;

    sf::VertexArray varray;
    varray.setPrimitiveType(sf::PrimitiveType::Quads);

    int cell_size = 20;
    int cell_padding = 1;

    constexpr auto CELL_COUNT = 40;

    const unsigned int cells_x = CELL_COUNT;
    const unsigned int cells_y = CELL_COUNT;

    Automaton automat(160, 5, 0, sf::Color::Black, sf::Color::Red);
    automat.resetCurrentState();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            automat.resetCurrentState();
        }

        clock.restart();

        window.clear(sf::Color(64, 64, 64, 255));

        automat.update();
        automat.draw(window, sf::RenderStates::Default);

        window.display();

        //int time = clock.getElapsedTime().asMicroseconds;
        //std::cout << "Calc: " << time << "\n";
    }

    return 0;
}