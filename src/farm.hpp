#pragma once
#include <string>
#include <vector>
#include "plot.hpp"
#include "player.hpp"
#include "bunny.hpp"

class Farm {
private:
    int rows;
    int columns;
    Player *player;
    Bunny* bunny = nullptr; // only 1 bunny at a time
    std::vector<std::vector<Plot *>> plots;
    int current_day = 1;
public:
    Farm(int rows, int columns, Player *player);
    int number_of_rows();
    int number_of_columns();
    std::string get_symbol(int row, int column);
    void plant(int row, int column, Plot *plot);
    int day() const;
    void end_day();
    void harvest(int row, int column);
    Plot* get_plot(int row, int column) {
        return plots.at(row).at(column);
    }
    Bunny* get_bunny() { return bunny; }
    void spawn_bunny(); // spawn at top-left corner
    void bunny_day_start(Player* player); // eat crops / check adjacency
    void bunny_end_day(Player* player);   // move bunny
};