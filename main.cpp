#include "stdafx.h"

#include "Automaton.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode(800, 800), "#LebenIstLava");
    window.setFramerateLimit(15);

    sf::Clock clock;

    Automaton automat(80, 10, 1, sf::Color(10, 10, 10, 255), sf::Color(255, 80, 40, 255));
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

        window.clear(sf::Color(48, 48, 48, 255));

        automat.update();
        automat.draw(window, sf::RenderStates::Default);

        window.display();

        /*
        sf::Time time = clock.getElapsedTime();
        std::cout << "Calctime: " << time.asMicroseconds() << "\n";
        */
    }

    return 0;
}