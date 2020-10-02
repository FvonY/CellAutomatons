#include "stdafx.h"
#include "Automaton.h"

// Constructor + Destructor

Automaton::Automaton(unsigned int number_of_cells, int cell_size, int cell_padding, sf::Color color_dead, sf::Color color_alive) :
    m_numberOfCells(number_of_cells),
    m_cellSize(cell_size),
    m_cellPadding(cell_padding),
    m_colorDead(color_dead),
    m_colorAlive(color_alive)
{
    initStates();

    m_varray.setPrimitiveType(sf::PrimitiveType::Quads);
    m_varray.resize(m_numberOfCells * m_numberOfCells);

    m_cell = new Cell(m_cellSize, m_cellPadding, m_colorDead);
}

Automaton::~Automaton()
{
    delete m_currentState;
    delete m_nextState;

    delete m_cell;
}

// Initiators

void Automaton::initStates()
{
    m_currentState = new std::vector<std::vector<int>>;
    m_currentState->resize(m_numberOfCells);
    for (auto& it : *m_currentState)
        it.resize(m_numberOfCells, -1);


    m_nextState = new std::vector<std::vector<int>>;
    m_nextState->resize(m_numberOfCells);
    for (auto& it : *m_nextState)
        it.resize(m_numberOfCells, -1);
}

void Automaton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_varray);
}

void Automaton::resetCurrentState()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    // Reseed currentState with [0,1]

    for (auto& outer : *m_currentState)
        for (auto& inner : outer)
            inner = dis(gen);
}

void Automaton::printStates()
{
    for (unsigned int y = 0; y < m_numberOfCells; ++y)
    {
        for (unsigned int x = 0; x < m_numberOfCells; ++x)
        {
            std::cout << (*m_currentState)[x][y];
        }
        std::cout << "\n";
    }
}

void Automaton::swapStates()
{
    std::vector<std::vector<int>>* tempptr = m_currentState;
    m_currentState = m_nextState;
    m_nextState = tempptr;
}

void Automaton::update()
{
    // Magic goes here.

    m_varray.clear();

    applyRules();
    swapStates();
}

int Automaton::countLivingNeighbours(unsigned int loc_x, unsigned int loc_y)
{
    int counter = 0;

    int x_lower = loc_x - 1 < 0 ? 0 : loc_x - 1;
    int x_upper = loc_x + 1 > m_numberOfCells - 1 ? m_numberOfCells - 1 : loc_x + 1;
    int y_lower = loc_y - 1 < 0 ? 0 : loc_y - 1;
    int y_upper = loc_y + 1 > m_numberOfCells - 1 ? m_numberOfCells - 1 : loc_y + 1;

    //std::cout << x_lower << " " << x_upper << " " << y_lower << " " << y_upper << std::endl;

    for (unsigned int m = y_lower; m <= y_upper; ++m)
    {
        for (unsigned int n = x_lower; n <= x_upper; ++n)
        {
            int nb = (*m_currentState)[n][m];
            if (nb == 1)
            {
                counter++;
            }
        }
    }

    return counter;
}

void Automaton::applyRules()
{
    for (unsigned int y = 0; y < m_numberOfCells; ++y)
    {
        for (unsigned int x = 0; x < m_numberOfCells; ++x)
        {
            int cur = (*m_currentState)[x][y];

            int neighbours = countLivingNeighbours(x, y);
            if (cur == 1)
                neighbours--;

            int new_cur = 0;

            if (cur == 0 && neighbours == 3)
                new_cur = 1;

            if (cur == 1)
            {
                if (neighbours == 1)
                {
                    new_cur = 0;
                }
                else if (neighbours == 2 || neighbours == 3)
                {
                    new_cur = 1;
                }
                else if (neighbours > 3)
                {
                    new_cur = 0;
                }
            }

            // Update VertexArray
            m_cell->setPosition(m_cellSize * x, m_cellSize * y);

            if (cur == 1)
                m_cell->setColor(m_colorAlive);
            else
                m_cell->setColor(m_colorDead);

            m_cell->appendMe(m_varray);
            // Update for next iteration.
            (*m_nextState)[x][y] = new_cur;
        }
    }
}
