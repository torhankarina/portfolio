#include <string>
#include <vector>
#include "farm.hpp"
#include "soil.hpp"
#include "bunny.hpp"

Farm::Farm(int rows, int columns, Player *player) : rows(rows), columns(columns), player(player) {
  for(int i = 0; i < rows; i++) {
    std::vector<Plot *> row;
    for(int j = 0; j < columns; j++) {
      Soil *soil = new Soil();
      row.push_back(soil);
    }
    plots.push_back(row);
  }
}

int Farm::number_of_rows() {
  return rows;
}

int Farm::number_of_columns() {
  return columns;
}

std::string Farm::get_symbol(int row, int column) {
  if(player->row() == row && player->column() == column) return "@";
  if (bunny && bunny->is_on_farm() && bunny->get_row() == row && bunny->get_column() == column)
    return bunny->symbol();
  return plots.at(row).at(column)->symbol();
}

void Farm::plant(int row, int column, Plot *plot) {
  if (plots.at(row).at(column)->is_mature() || dynamic_cast<Soil*>(plots.at(row).at(column)) == nullptr) {
    return;
  }
  Plot *current_plot = plots.at(row).at(column);
  plots.at(row).at(column) = plot;
  delete current_plot;
}

int Farm::day() const {
  return current_day;
}

void Farm::end_day() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      plots.at(i).at(j)->end_day();
    }
  }
  current_day += 1;
}

void Farm::harvest(int row, int column) {
  Plot* plot = plots.at(row).at(column);
  if(plot->is_mature()) {
    delete plot;
    plots.at(row).at(column) = new Soil();
  }
}

void Farm::spawn_bunny() {
  if (!bunny || !bunny->is_on_farm()) {
    delete bunny;               // clean up old bunny if it exists
    int start_row = 0;          // top row
    int start_col = 1;          // next to player at (0,0)
    bunny = new Bunny(start_row, start_col);
  }
}

// check if bunny is on vegetable and eat it; check if player is nearby
void Farm::bunny_day_start(Player* player) {
  if (!bunny || !bunny->is_on_farm()) return;

  int r = bunny->get_row();
  int c = bunny->get_column();

  // eat vegetable if present
  Plot* plot = plots.at(r).at(c);
  if (!dynamic_cast<Soil*>(plot)) {
    delete plot;
    plots.at(r).at(c) = new Soil();
  }

  // check adjacency to player
  int pr = player->row();
  int pc = player->column();
  if ((abs(pr - r) == 1 && pc == c) || (abs(pc - c) == 1 && pr == r)) {
    bunny->scare();
  }
}

// move bunny at end of day
void Farm::bunny_end_day(Player* player) {
  if (!bunny || !bunny->is_on_farm()) return;

  if (bunny->is_scared()) {
    bunny->run_away(player->row(), player->column(), rows, columns);
  } else {
    bunny->move(rows, columns);
  }
}