#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <utility>

#ifndef _GAMEOFLIFE_
#include "include/classes/GameOfLife.h"
#endif

int main ()
{
    std::vector<std::pair<uint8_t, uint8_t> > initial_state;

    /* GLIDER */
    /*initial_state.push_back(std::make_pair(0, 2));
    initial_state.push_back(std::make_pair(1, 2));
    initial_state.push_back(std::make_pair(2, 2));
    initial_state.push_back(std::make_pair(2, 1));
    initial_state.push_back(std::make_pair(1, 0));*/

    /* PULSAR */
    std::vector<uint8_t> x = {1,6,8,13}, y = {3,4,5,9,10,11};
    for (uint8_t i = 0; i < x.size(); i++)
        for (uint8_t j = 0; j < y.size(); j++)
        {
            initial_state.push_back(std::make_pair(y[j],x[i]));
            initial_state.push_back(std::make_pair(x[i],y[j]));

        }

    GameOfLife game(15, initial_state);

    std::system("clear");

    game.PrintGame();

    for (uint8_t i = 0; i < 30; i++)
    {
        game.Iterate();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::system("clear");

        game.PrintGame();
    }

    return 0;
}
