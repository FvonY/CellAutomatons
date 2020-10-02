#pragma once

#include "Cell.h"

class Automaton : public sf::Drawable
{
private:
    std::vector<std::vector<int>>* m_currentState = nullptr;
    std::vector<std::vector<int>>* m_nextState = nullptr;

    sf::VertexArray m_varray;

    Cell* m_cell;

    int m_cellSize;
    int m_cellPadding;
    sf::Color m_colorDead;
    sf::Color m_colorAlive;

    unsigned int m_numberOfCells;
public:
    // Constructor + Destructor
    Automaton(unsigned int number_of_cells, int cell_size, int cell_padding, sf::Color color_dead, sf::Color color_alive);
    virtual ~Automaton();

    // Initiators
    void initStates();

    // Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Functions
    void resetCurrentState();
    void printStates();
    void swapStates();

    void update();

    int countLivingNeighbours(unsigned int loc_x, unsigned int loc_y);
    void applyRules();
};
