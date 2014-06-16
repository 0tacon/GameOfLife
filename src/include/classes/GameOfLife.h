#include <cstdint>
#include <vector>
#include <utility>
#include <algorithm>

#define _GAMEOFLIFE_

class GameOfLife
{
public:
    GameOfLife(uint8_t dim);
    GameOfLife(uint8_t dim, std::vector<std::pair<uint8_t, uint8_t> > initial_state);
    ~GameOfLife();

    void PrintGame();

    void Iterate();

    bool IterateCell(bool cell, uint8_t row, uint8_t col);

private:
    std::vector<std::vector<bool> > Board;
    uint8_t dim;
};

GameOfLife::GameOfLife(uint8_t side_length)
{
    dim = side_length;

    std::vector<bool> vect(dim);

    std::fill(vect.begin(), vect.end(), true);

    for (uint8_t i = 0; i < dim; i++)
        Board.push_back(vect);
}

GameOfLife::GameOfLife(uint8_t side_length, std::vector<std::pair<uint8_t, uint8_t> > initial_state)
{
    dim = side_length;

    std::vector<bool> vect(dim);

    std::fill(vect.begin(), vect.end(), false);

    for (uint8_t i = 0; i < dim; i++)
        Board.push_back(vect);

    for (std::vector<std::pair<uint8_t, uint8_t> >::iterator val = initial_state.begin(); val != initial_state.end(); val++)
        if (val->first < dim && val->second < dim)
            Board[val->first][val->second] = true;
}

GameOfLife::~GameOfLife() {}

void GameOfLife::PrintGame()
{
    printf("\n");

    for (std::vector<std::vector<bool> >::iterator a = Board.begin(); a != Board.end(); a++)
    {
        for (std::vector<bool>::iterator b = a->begin(); b != a->end(); b++)
        {
            if (*b)
                printf("%c", '#');
            else
                printf("%c", '-');
        }

        printf("\n");
    }

    printf("\n");
}

void GameOfLife::Iterate()
{
    std::vector<std::vector<bool> > NextGen = Board;

    for (uint8_t a = 0; a < dim; a++)
    {
        for (uint8_t b = 0; b < dim; b++)
        {
            NextGen[a][b] = IterateCell(Board[a][b], a, b);
        }
    }

    Board = NextGen;
}

bool GameOfLife::IterateCell (bool cell, uint8_t row, uint8_t col)
{
    uint8_t neighbours = 0;

    if (col > 0 && col < dim -1)
    {
        for (uint8_t i = col - 1; i < col + 2; i++)
        {
            if (row > 0)
                if (Board[row-1][i])
                    neighbours++;

            if (row < dim - 1)
                if (Board[row+1][i])
                    neighbours++;

            if (Board[row][i] && i != col)
                neighbours++;
        }
    }
    else if (col == 0)
    {
        for (uint8_t i = col; i < col + 2; i++)
        {
            if (row > 0)
                if (Board[row-1][i])
                    neighbours++;

            if (row < dim - 1)
                if (Board[row+1][i])
                    neighbours++;

            if (Board[row][i] && i != col)
                neighbours++;
        }
    }
    else if (col == dim - 1)
    {
        for (uint8_t i = col - 1; i < col + 1; i++)
        {
            if (row > 0)
                if (Board[row-1][i])
                    neighbours++;

            if (row < dim - 1)
                if (Board[row+1][i])
                    neighbours++;

            if (Board[row][i] && i != col)
                neighbours++;
        }
    }

    if (neighbours == 3 || (cell && neighbours == 2))
        return true;

    return false;
}
