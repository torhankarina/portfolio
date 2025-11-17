#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/carrot.hpp"

TEST_CASE( "it can be initialized with a single plot" ) {
    Player player;
    Farm farm(1, 1, &player);
    REQUIRE( farm.number_of_rows() == 1 );
    REQUIRE( farm.number_of_columns() == 1 );
}

TEST_CASE( "it can be initialized as a 1x2 farm" ) {
    Player player;
    Farm farm(1, 2, &player);
    REQUIRE( farm.number_of_rows() == 1 );
    REQUIRE( farm.number_of_columns() == 2 );
}

TEST_CASE( "it can be initialized as a 2x1 farm" ) {
    Player player;
    Farm farm(2, 1, &player);
    REQUIRE( farm.number_of_rows() == 2 );
    REQUIRE( farm.number_of_columns() == 1 );
}

TEST_CASE( "it returns the symbol for a single soil plot" ) {
    Player player;
    Farm farm(1, 1, &player);
    REQUIRE( farm.get_symbol(0, 0) == "@" );
}

TEST_CASE( "it returns the symbols for a 1x2 farm" ) {
    Player player;
    Farm farm(1, 2, &player);
    REQUIRE( farm.get_symbol(0, 0) == "@" );
    REQUIRE( farm.get_symbol(0, 1) == "." );
}

TEST_CASE( "it returns the symbols for a 2x1 farm" ) {
    Player player;
    Farm farm(2, 1, &player);
    REQUIRE( farm.get_symbol(0, 0) == "@" );
    REQUIRE( farm.get_symbol(1, 0) == "." );
}

TEST_CASE( "it allows us to plant a carrot" ) {
    Player player;
    Farm farm(1, 2, &player);
    Carrot carrot;
    farm.plant(0, 1, &carrot);
    REQUIRE( farm.get_symbol(0, 1) == "~" );
}

TEST_CASE("harvesting a mature plant replaces it with soil") {
    Player player;
    Farm farm(1, 1, &player);
    Carrot* carrot = new Carrot();
    farm.plant(0, 0, carrot);

    player.move_down();

    farm.end_day();
    farm.harvest(0, 0);

    REQUIRE(farm.get_symbol(0, 0) == "."); // now visible as soil
}

TEST_CASE("cannot harvest a seedling") {
    Player player;
    Farm farm(1, 1, &player);
    Carrot* carrot = new Carrot();
    farm.plant(0, 0, carrot);

    player.move_down();

    farm.harvest(0, 0);
    REQUIRE(farm.get_symbol(0, 0) == "~");
}

TEST_CASE("cannot plant on an occupied plot") {
    Player player;
    Farm farm(1, 1, &player);
    Carrot* carrot1 = new Carrot();
    farm.plant(0, 0, carrot1);

    player.move_down();

    Carrot* carrot2 = new Carrot();
    farm.plant(0, 0, carrot2);
    REQUIRE(farm.get_symbol(0, 0) == "~");
}

TEST_CASE("can plant on soil") {
    Player player;
    Farm farm(1, 1, &player);

    player.move_down();

    Carrot* carrot = new Carrot();
    farm.plant(0, 0, carrot);
    REQUIRE(farm.get_symbol(0, 0) == "~");
}