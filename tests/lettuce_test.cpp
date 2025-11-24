#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/lettuce.hpp"

TEST_CASE("Lettuce initial state") {
    Lettuce lettuce;
    REQUIRE(lettuce.symbol() == "~");
    REQUIRE_FALSE(lettuce.is_mature());
}

TEST_CASE("Lettuce growth without watering") {
    Lettuce lettuce;

    lettuce.end_day(); // age = 1
    REQUIRE(lettuce.symbol() == "~");
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.end_day(); // age = 2
    REQUIRE(lettuce.symbol() == "l");
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.end_day(); // age = 3
    REQUIRE(lettuce.symbol() == "l");
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.end_day(); // age = 4
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());

    // extra days
    lettuce.end_day(); // age = 5
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Lettuce growth with watering") {
    Lettuce lettuce;

    lettuce.water();
    lettuce.end_day(); // age += 2 -> age = 2
    REQUIRE(lettuce.symbol() == "l");
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.water();
    lettuce.end_day(); // age += 2 -> age = 4
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Multiple waterings in one day have no extra effect") {
    Lettuce lettuce;
    lettuce.water();
    lettuce.water(); // second watering same day should have no effect
    lettuce.end_day(); // age += 2
    REQUIRE(lettuce.symbol() == "l");
    REQUIRE_FALSE(lettuce.is_mature());
}

TEST_CASE("Watered plant matures faster than unwatered") {
    Lettuce lettuce;
    // without watering, age = 1 after 1 day
    lettuce.end_day();
    REQUIRE(lettuce.symbol() == "~");

    lettuce.water();
    lettuce.end_day(); // age += 2 -> age = 3
    REQUIRE(lettuce.symbol() == "l");
    REQUIRE_FALSE(lettuce.is_mature());

    lettuce.water();
    lettuce.end_day(); // age += 2 -> age = 5
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Lettuce remains mature after reaching maturity") {
    Lettuce lettuce;
    for (int i = 0; i < 10; ++i) {
        lettuce.end_day();
    }
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Watering an already mature plant does nothing extra") {
    Lettuce lettuce;
    for (int i = 0; i < 4; ++i) lettuce.end_day(); // mature
    REQUIRE(lettuce.is_mature());

    lettuce.water();
    lettuce.end_day();
    REQUIRE(lettuce.symbol() == "L");
    REQUIRE(lettuce.is_mature());
}

TEST_CASE("Watering an unplanted soil does nothing") {
    Lettuce lettuce; // simulate age 0
    lettuce.water(); // should not affect age = 0 tilled soil
    REQUIRE(lettuce.symbol() == "~");
    REQUIRE_FALSE(lettuce.is_mature());
}