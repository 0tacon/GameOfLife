#include <cstdint>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

    void Play();

private:
    std::vector<std::vector<bool> > Board;
    uint8_t dim;
    bool evolution;
};

GameOfLife::GameOfLife(uint8_t side_length)
{
    dim = side_length;

    evolution = true;

    uint16_t random_num;

    std::srand(std::time(0));

    std::vector<bool> vect(dim);

    //std::fill(vect.begin(), vect.end(), true);

    for (uint8_t i = 0; i < dim; i++)
    {
        for (uint8_t j = 0; j < dim; j++)
        {
            random_num = std::rand();

            if (random_num%2 == 0)
                vect[j] = true;
            else
                vect[j] = false;
        }

        Board.push_back(vect);
    }
}

GameOfLife::GameOfLife(uint8_t side_length, std::vector<std::pair<uint8_t, uint8_t> > initial_state)
{
    dim = side_length;

    evolution = true;

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
                printf("%c", ' ');
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

    if (Board != NextGen)
        evolution = true;
    else
        evolution = false;

    Board = NextGen;
}

bool GameOfLife::IterateCell (bool cell, uint8_t row, uint8_t col)
{
    uint8_t neighbours = 0;

    std::vector<uint8_t> cols, rows;

    if (col > 0 && col < dim -1)
    {
        cols.push_back(col - 1);
        cols.push_back(col);
        cols.push_back(col + 1);
    }
    else if (col == 0)
    {
        cols.push_back(col);
        cols.push_back(col + 1);
        cols.push_back(dim - 1);
    }
    else if (col == dim - 1)
    {
        cols.push_back(col);
        cols.push_back(col - 1);
        cols.push_back(0);
    }

    if (row > 0 && row < dim -1)
    {
        rows.push_back(row - 1);
        rows.push_back(row);
        rows.push_back(row + 1);
    }
    else if (row == 0)
    {
        rows.push_back(row);
        rows.push_back(row + 1);
        rows.push_back(dim - 1);
    }
    else if (row == dim - 1)
    {
        rows.push_back(row);
        rows.push_back(row - 1);
        rows.push_back(0);
    }

    for (std::vector<uint8_t>::iterator a = rows.begin(); a != rows.end(); a++)
        for (std::vector<uint8_t>::iterator b = cols.begin(); b != cols.end(); b++)
            if ((*a != row || *b != col) && Board[*a][*b])
                neighbours++;

    if (neighbours == 3 || (cell && neighbours == 2))
        return true;

    return false;
}

void GameOfLife::Play()
{
    std::system("clear");

    this->PrintGame();

    while (evolution)
    {
        this->Iterate();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::system("clear");

        this->PrintGame();
    }
}
