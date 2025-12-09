#include "bunny.hpp"
#include <string>
#include <cmath>

Bunny::Bunny(int start_row, int start_column) : row(start_row), column(start_column) {}

int Bunny::get_row() { return row; }
int Bunny::get_column() { return column; }
void Bunny::scare() { scared = true; }
bool Bunny::is_scared() { return scared; }
bool Bunny::is_on_farm() { return on_farm; }
std::string Bunny::symbol() { return "&"; }

// normal movement: straight line downwards (increase row by 1)
void Bunny::move(int farm_rows, int farm_columns) {
    if (!on_farm) return;
    row += 1;
    if (row >= farm_rows) on_farm = false;
}

// run away movement: 4 squares directly away from player
void Bunny::run_away(int player_row, int player_column, int farm_rows, int farm_columns) {
    if (!on_farm) return;
    int dr = row - player_row;
    int dc = column - player_column;

    // move vertically
    if (abs(dr) > abs(dc)) {
        row += (dr >= 0) ? 4 : -4;
    } else { // move horizontally
        column += (dc >= 0) ? 4 : -4;
    }

    scared = false;

    // check bounds
    if (row < 0 || row >= farm_rows || column < 0 || column >= farm_columns) on_farm = false;
}