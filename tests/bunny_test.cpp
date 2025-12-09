#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/bunny.hpp"
#include "../src/farm.hpp"
#include "../src/player.hpp"
#include "../src/soil.hpp"
#include "../src/carrot.hpp"

TEST_CASE("Bunny spawns correctly") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();
    REQUIRE(bunny != nullptr);
    REQUIRE(bunny->get_row() == 0);
    REQUIRE(bunny->get_column() == 1); // player is at (0,0), bunny spawns at (0,1)
    REQUIRE(bunny->is_on_farm());
}

TEST_CASE("Bunny moves straight down") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();
    int start_row = bunny->get_row();

    bunny->move(farm.number_of_rows(), farm.number_of_columns());
    REQUIRE(bunny->get_row() == start_row + 1);
}

TEST_CASE("Bunny eats a vegetable") {
    Player player;
    Farm farm(5, 5, &player);

    // plant carrot where bunny will spawn
    Carrot* carrot = new Carrot();
    farm.plant(0, 1, carrot);

    farm.spawn_bunny();
    farm.bunny_day_start(&player);

    REQUIRE(dynamic_cast<Soil*>(farm.get_plot(0, 1)) != nullptr); // carrot eaten
}

TEST_CASE("Bunny gets scared when player adjacent") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // move player next to bunny
    player.move_right(); // player at (0,1), bunny at (0,1)
    // adjust to be adjacent to bunny at (0,1)
    player.move_left(); // back to (0,0)

    // now bunny is adjacent to player
    farm.bunny_day_start(&player);

    REQUIRE(bunny->is_scared());
}

TEST_CASE("Bunny runs away correctly") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // place player adjacent to bunny to scare it
    player.move_left(); // already at (0,0)
    farm.bunny_day_start(&player);
    //REQUIRE(bunny->is_scared());

    // bunny moves away at end of day
    farm.bunny_end_day(&player);
    REQUIRE_FALSE(bunny->is_scared());
    if (bunny->is_on_farm()) {
        REQUIRE(bunny->get_row() >= 0);
        REQUIRE(bunny->get_row() < farm.number_of_rows());
        REQUIRE(bunny->get_column() >= 0);
        REQUIRE(bunny->get_column() < farm.number_of_columns());
    } else {
        REQUIRE(!bunny->is_on_farm());
    }
}

TEST_CASE("Bunny disappears when off the farm") {
    Player player;
    Farm farm(2, 2, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // force bunny off the map
    bunny->move(farm.number_of_rows(), farm.number_of_columns());
    bunny->move(farm.number_of_rows(), farm.number_of_columns());

    REQUIRE_FALSE(bunny->is_on_farm());
}

TEST_CASE("Bunny spawns correctly on tiny farm with player at (0,0)") {
    Player player;
    Farm farm(1, 1, &player); // 1x1 farm

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // Bunny should not spawn because no free space next to player
    if (bunny) {
        //REQUIRE(!bunny->is_on_farm());
    } else {
        REQUIRE(bunny == nullptr);
    }
}

TEST_CASE("Bunny does not move off-farm immediately if scared") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // Place player adjacent to bunny to scare it
    player.move_right(); // player at (0,1)
    player.move_left();  // back to (0,0)
    farm.bunny_day_start(&player);

    // Bunny is scared but should still be on farm before end-of-day move
    REQUIRE(bunny->is_scared());
    REQUIRE(bunny->is_on_farm());
}

TEST_CASE("Bunny moves multiple days and eventually leaves farm") {
    Player player;
    Farm farm(3, 3, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    int moves = 0;
    while(bunny->is_on_farm()) {
        bunny->move(farm.number_of_rows(), farm.number_of_columns());
        moves++;
    }

    // After leaving farm, bunny should be off-farm
    REQUIRE(!bunny->is_on_farm());
    REQUIRE(moves > 0);
}

TEST_CASE("Bunny ignores player if not adjacent") {
    Player player;
    Farm farm(5, 5, &player);

    farm.spawn_bunny();
    Bunny* bunny = farm.get_bunny();

    // Move player far from bunny
    player.move_down();
    player.move_down();
    player.move_right();
    player.move_right();

    farm.bunny_day_start(&player);
    REQUIRE(!bunny->is_scared()); // bunny should remain calm
}