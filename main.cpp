#include <iostream>
#include "src/player.hpp"
#include "src/farm.hpp"
#include "src/farm_printer.hpp"
#include "src/soil.hpp"
#include "src/plot.hpp"
#include "src/ansi_clear.hpp"
#include "src/carrot.hpp"
#include "src/lettuce.hpp"
#include "src/spinach.hpp"
#include "src/beet.hpp"
#include "src/brussels_sprouts.hpp"

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
    } else if(player_input == "l") {
      Lettuce* lettuce = new Lettuce();
      farm.plant(player.row(), player.column(), lettuce);
    } else if(player_input == "p") {
      Spinach* spinach = new Spinach();
      farm.plant(player.row(), player.column(), spinach);
    } else if(player_input == "b") {
      Beet* beet = new Beet();
      farm.plant(player.row(), player.column(), beet);
    } else if(player_input == "r") {
      BrusselsSprouts* brussels_sprouts = new BrusselsSprouts();
      farm.plant(player.row(), player.column(), brussels_sprouts);
    } else if (player_input == "t") {
      Plot* plot = farm.get_plot(player.row(), player.column());
      if (auto carrot = dynamic_cast<Carrot*>(plot)) carrot->water();
      else if (auto lettuce = dynamic_cast<Lettuce*>(plot)) lettuce->water();
      else if (auto spinach = dynamic_cast<Spinach*>(plot)) spinach->water();
      else if (auto beet = dynamic_cast<Beet*>(plot)) beet->water();
      else if (auto brussels = dynamic_cast<BrusselsSprouts*>(plot)) brussels->water();
    } else if(player_input == "h") {
      farm.harvest(player.row(), player.column());
    } else if (player_input == "e") {
      farm.end_day();
    }
  }
  std::cout << "\nThanks for playing!\n";
}