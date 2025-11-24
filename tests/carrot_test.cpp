#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/carrot.hpp"

TEST_CASE("Carrot initial state") {
    Carrot carrot;
    REQUIRE(carrot.symbol() == "~"); // tilled soil
    REQUIRE(!carrot.is_mature());
}

TEST_CASE("Carrot grows without watering") {
    Carrot carrot;
    carrot.end_day(); // age 1
    REQUIRE(carrot.symbol() == "c"); // seedling
    REQUIRE(!carrot.is_mature());

    carrot.end_day(); // age 2
    REQUIRE(carrot.symbol() == "C"); // adult
    REQUIRE(carrot.is_mature());
}

TEST_CASE("Carrot grows with watering") {
    Carrot carrot;
    carrot.water();
    carrot.end_day(); // watered, age += 2
    REQUIRE(carrot.symbol() == "C");
    REQUIRE(carrot.is_mature());
}

TEST_CASE("Carrot watered multiple times in one day") {
    Carrot carrot;
    carrot.water();
    carrot.water(); // second watering same day should do nothing extra
    carrot.end_day();
    REQUIRE(carrot.symbol() == "C");
    REQUIRE(carrot.is_mature());
}

TEST_CASE("Carrot does not regress in age") {
    Carrot carrot;
    carrot.end_day(); // age 1
    carrot.end_day(); // age 2
    carrot.end_day(); // age 3
    REQUIRE(carrot.symbol() == "C");
    REQUIRE(carrot.is_mature());
}

TEST_CASE("Carrot watering right before maturity") {
    Carrot carrot;
    carrot.end_day(); // age 1, seedling
    carrot.water();
    carrot.end_day(); // age should go from 1 -> 3
    REQUIRE(carrot.symbol() == "C");
    REQUIRE(carrot.is_mature());
}

TEST_CASE("Watering mature carrot does nothing bad") {
    Carrot carrot;
    carrot.end_day(); // age 1
    carrot.end_day(); // age 2, mature
    carrot.water();
    carrot.end_day(); // age 3
    REQUIRE(carrot.symbol() == "C");
    REQUIRE(carrot.is_mature());
}