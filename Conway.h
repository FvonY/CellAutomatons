#pragma once
class Conway
{
private:
    unsigned int m_size;
public:
    Conway(unsigned int size);
    virtual ~Conway();

    int update(const int* state, int loc_x, int loc_y);

    int countLivingNeighbours(const int* state, int loc_x, int loc_y);
};
