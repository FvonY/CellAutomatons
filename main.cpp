#include "stdafx.h"

#include "Conway.h"
#include "Cell.h"

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

    sf::Color cell_color;
    cell_color = sf::Color::Black;

    /*
    int current_state[cells_x][cells_y] = 
    { 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

        {0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0},
        {0,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0},
        {0,0,1,1,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    */

    int current_state[cells_x][cells_y];
    int next_state[cells_x][cells_y];
    int* current_state_p = current_state[0];

    /*
    // Array nullen
    for (unsigned int y = 0; y < cells_y; y++)
    {
        for (unsigned int x = 0; x < cells_x; x++)
        {
            current_state[x][y] = 0;
            //std::cout << "Init: " << current_state[x][y] << std::endl;
        }
    }
    
    */

    // Reprint
    /*
    for (unsigned int y = 0; y < cells_y; y++)
    {
        for (unsigned int x = 0; x < cells_x; x++)
        {
            std::cout << "Reprint: " << current_state_p[x+y*cells_x] << std::endl;
        }
    }
    */
    
    /*
    // Blinker
    current_state[6][7] = 1;
    current_state[7][7] = 1;
    current_state[8][7] = 1;
    */

    /*
    // Init with current_state with random numbers [0,1]

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (unsigned int y = 0; y < cells_y; y++)
    {
        for (unsigned int x = 0; x < cells_x; x++)
        {
            current_state[x][y] = dis(gen);
            //std::cout << "Init: " << current_state[x][y] << "\n";
        }
    }
    */
    
    resetState(current_state[0],CELL_COUNT);

    //std::cout << a << std::endl;
    //std::cout << *a << std::endl;

    

    Cell cell(cell_size, cell_padding, cell_color);
    Conway conway(cells_x);

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
            resetState(current_state[0], CELL_COUNT);
        }

        clock.restart();

        window.clear(sf::Color(64, 64, 64, 255));
        varray.clear();

        for (unsigned int y = 0; y < cells_y; ++y)
        {
            for (unsigned int x = 0; x < cells_x; ++x)
            {
                // Draw current_state
                cell.setPosition(cell_size * x, cell_size * y);

                if (current_state[x][y] == 1)
                    cell.setColor(sf::Color(220, 80, 10, 255));
                else
                    cell.setColor(sf::Color::Black);

                // Add cell to VertexArray
                cell.appendMe(varray);

                // Update next_state
                next_state[x][y] = conway.update(current_state_p, x, y);
            }
        }
        
        //std::cout << "Varray ist: " << varray.getVertexCount() << std::endl;

        window.draw(varray);
        window.display();

        float time = clock.getElapsedTime().asMicroseconds();

        std::cout << "Calc time: " << time << "\n";

        for (unsigned int y = 0; y < cells_y; ++y)
        {
            for (unsigned int x = 0; x < cells_x; ++x)
            {
                // Overwrite current_state with next_state
                //std::cout << "X:" << x << ", Y:" << y << " " << next_state[x][y] << std::endl;
                current_state[x][y] = next_state[y][x];
            }
        }
        //std::cin.get();
    }

    return 0;
}