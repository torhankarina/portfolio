#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/spinach.hpp"

TEST_CASE("Spinach initial state") {
    Spinach spinach;
    REQUIRE(spinach.symbol() == "~");
    REQUIRE_FALSE(spinach.is_mature());
}

TEST_CASE("Spinach growth without watering") {
    Spinach spinach;

    spinach.end_day(); // age = 1
    REQUIRE(spinach.symbol() == "~");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // age = 2
    REQUIRE(spinach.symbol() == "p"); // seedling
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // age = 3
    REQUIRE(spinach.symbol() == "p");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // age = 4
    REQUIRE(spinach.symbol() == "p");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.end_day(); // age = 5
    REQUIRE(spinach.symbol() == "P"); // adult
    REQUIRE(spinach.is_mature());

    // extra day
    spinach.end_day(); // age = 6
    REQUIRE(spinach.symbol() == "P");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Spinach growth with watering") {
    Spinach spinach;

    spinach.water();
    spinach.end_day(); // age += 2 -> age = 2
    REQUIRE(spinach.symbol() == "p");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.water();
    spinach.end_day(); // age += 2 -> age = 4
    REQUIRE(spinach.symbol() == "p");
    REQUIRE_FALSE(spinach.is_mature());

    spinach.water();
    spinach.end_day(); // age += 2 -> age = 6
    REQUIRE(spinach.symbol() == "P");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Multiple waterings in one day have no extra effect") {
    Spinach spinach;
    spinach.water();
    spinach.water(); // second watering same day should have no effect
    spinach.end_day(); // age += 2
    REQUIRE(spinach.symbol() == "p");
    REQUIRE_FALSE(spinach.is_mature());
}

TEST_CASE("Spinach remains mature after reaching maturity") {
    Spinach spinach;
    for (int i = 0; i < 10; ++i) spinach.end_day();
    REQUIRE(spinach.symbol() == "P");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Watering an already mature Spinach does nothing extra") {
    Spinach spinach;
    for (int i = 0; i < 5; ++i) spinach.end_day(); // mature
    REQUIRE(spinach.is_mature());

    spinach.water();
    spinach.end_day();
    REQUIRE(spinach.symbol() == "P");
    REQUIRE(spinach.is_mature());
}

TEST_CASE("Watering unplanted soil does nothing") {
    Spinach spinach; // age 0
    spinach.water();
    REQUIRE(spinach.symbol() == "~");
    REQUIRE_FALSE(spinach.is_mature());
}