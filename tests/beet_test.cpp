#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/beet.hpp"

TEST_CASE("Beet initial state") {
    Beet beet;
    REQUIRE(beet.symbol() == "~");
    REQUIRE_FALSE(beet.is_mature());
}

TEST_CASE("Beet growth without watering") {
    Beet beet;

    beet.end_day(); // age = 1
    REQUIRE(beet.symbol() == "~");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 2
    REQUIRE(beet.symbol() == "b"); // seedling
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 3
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 4
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 5
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 6
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.end_day(); // age = 7
    REQUIRE(beet.symbol() == "B"); // adult
    REQUIRE(beet.is_mature());

    beet.end_day(); // age = 8
    REQUIRE(beet.symbol() == "B");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Beet growth with watering") {
    Beet beet;

    beet.water();
    beet.end_day(); // age += 2 -> age = 2
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.water();
    beet.end_day(); // age += 2 -> age = 4
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.water();
    beet.end_day(); // age += 2 -> age = 6
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());

    beet.water();
    beet.end_day(); // age += 2 -> age = 8
    REQUIRE(beet.symbol() == "B");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Multiple waterings in one day have no extra effect") {
    Beet beet;
    beet.water();
    beet.water(); // second watering same day should have no effect
    beet.end_day(); // age += 2
    REQUIRE(beet.symbol() == "b");
    REQUIRE_FALSE(beet.is_mature());
}

TEST_CASE("Beet remains mature after reaching maturity") {
    Beet beet;
    for (int i = 0; i < 10; ++i) beet.end_day();
    REQUIRE(beet.symbol() == "B");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Watering an already mature Beet does nothing extra") {
    Beet beet;
    for (int i = 0; i < 7; ++i) beet.end_day(); // mature at age 7
    REQUIRE(beet.is_mature());

    beet.water();
    beet.end_day();
    REQUIRE(beet.symbol() == "B");
    REQUIRE(beet.is_mature());
}

TEST_CASE("Watering unplanted soil does nothing") {
    Beet beet; // age 0
    beet.water();
    REQUIRE(beet.symbol() == "~");
    REQUIRE_FALSE(beet.is_mature());
}