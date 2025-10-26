#include <iostream>
#include "src/player.hpp"
#include "src/farm.hpp"
#include "src/farm_printer.hpp"
#include "src/carrot.hpp"
#include "src/soil.hpp"
#include "src/plot.hpp"
#include "src/ansi_clear.hpp"

int main() {
  Player player;
  Farm farm(7, 8, &player);
  FarmPrinter printer(&farm);
  bool game_in_progress = true;
  std::string player_input;

  while(game_in_progress) {
    ansi_clear();
    std::cout << printer.legend();
    std::cout << printer.pp() << std::endl;
    //std::cin >> player_input;
    std::getline(std::cin, player_input);

    if(player_input == "q") {
      game_in_progress = false;
    } else if(player_input == "d") {
      if(player.column() < farm.number_of_columns() - 1) player.move_right();
    } else if(player_input == "s") {
      if(player.row() < farm.number_of_rows() - 1) player.move_down();
    } else if(player_input == "a") {
      if(player.column() > 0) player.move_left();
    } else if(player_input == "w") {
      if(player.row() > 0) player.move_up();
    } else if(player_input == "c") {
      Carrot *carrot = new Carrot();
      farm.plant(player.row(), player.column(), carrot);
    } else if(player_input == "h") {
      farm.harvest(player.row(), player.column());
    } else if (player_input == "e") {
      farm.end_day();
    }
  }
  std::cout << "\nThanks for playing!\n";
}