#pragma once
#include "plot.hpp"

class Bunny {
private:
    int row;
    int column;
    bool scared = false;
    bool on_farm = true;

public:
    Bunny(int start_row, int start_column);
    int get_row();
    int get_column();
    void scare(); // sets scared = true
    bool is_scared();
    bool is_on_farm();
    void move(int farm_rows, int farm_columns); // normal movement
    void run_away(int player_row, int player_column, int farm_rows, int farm_columns); // 4 squares away
    std::string symbol();
};