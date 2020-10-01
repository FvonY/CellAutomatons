#include "stdafx.h"
#include "Conway.h"

Conway::Conway(unsigned int size)    :
    m_size(size)
{
}

Conway::~Conway()
{
}

int Conway::update(const int* state, int loc_x, int loc_y)
{
    //return the new state of this cell

    int neighbours = countLivingNeighbours(state, loc_x, loc_y);
    int cur = *(state + loc_x + loc_y * m_size);
    int new_cur = 0;

    if (cur == 0 && neighbours == 3)
        new_cur = 1;

    if (cur == 1)
    {
        if (neighbours == 1)
        {
            new_cur = 0;
        }
        else if(neighbours == 2 || neighbours == 3)
        {
            new_cur = 1;
        }
        else if (neighbours > 3)
        {
            new_cur = 0;
        }
    }

    return new_cur;
}

int Conway::countLivingNeighbours(const int* state, int loc_x, int loc_y)
{
    int counter = 0;

    int x_lower = loc_x - 1 < 0 ? 0 : loc_x - 1;
    int x_upper = loc_x + 1 > m_size ? m_size : loc_x + 1;
    int y_lower = loc_y - 1 < 0 ? 0 : loc_y - 1;
    int y_upper = loc_y + 1 > m_size ? m_size : loc_y + 1;

    //std::cout << x_lower << " " << x_upper << " " << y_lower << " " << y_upper << std::endl;

    for (unsigned int m = y_lower; m <= y_upper; ++m)
    {
        for (unsigned int n = x_lower; n <= x_upper; ++n)
        {
            int cur = *(state + m * m_size + n);
            if (cur == 1)
            {
                counter++;
            }
        }
    }

    return counter- *(state + loc_y * m_size + loc_x);
}
