#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/brussels_sprouts.hpp"

TEST_CASE("Brussels Sprouts initial state") {
    BrusselsSprouts bs;
    REQUIRE(bs.symbol() == "~");
    REQUIRE_FALSE(bs.is_mature());
}

TEST_CASE("Brussels Sprouts growth without watering") {
    BrusselsSprouts bs;

    // Age 0-4: tilled soil
    for(int i=0;i<5;++i) {
        REQUIRE(bs.symbol() == "~");
        REQUIRE_FALSE(bs.is_mature());
        bs.end_day();
    }

    // Age 5-14: seedling
    for(int i=5;i<15;++i) {
        REQUIRE(bs.symbol() == "r");
        REQUIRE_FALSE(bs.is_mature());
        bs.end_day();
    }

    // Age >=15: adult
    bs.end_day(); // age=15
    REQUIRE(bs.symbol() == "R");
    REQUIRE(bs.is_mature());
}

TEST_CASE("Brussels Sprouts growth with watering") {
    BrusselsSprouts bs;

    // Water at age 0
    bs.water();
    bs.end_day();
    REQUIRE(bs.symbol() == "~"); // still tilled soil
    REQUIRE_FALSE(bs.is_mature());

    // Fast-forward with watering until adult
    int days = 0;
    while(!bs.is_mature() && days < 20) {
        bs.water();
        bs.end_day();
        days++;
    }

    REQUIRE(bs.symbol() == "R");
    REQUIRE(bs.is_mature());
}

TEST_CASE("Multiple waterings in same day have no extra effect") {
    BrusselsSprouts bs;

    // Move to seedling stage
    for(int i=0;i<5;++i) bs.end_day(); // age=5, seedling

    bs.water();
    bs.water(); // second watering same day
    bs.end_day();
    REQUIRE(bs.symbol() == "r"); // age=7 after +2, still seedling
    REQUIRE_FALSE(bs.is_mature());
}

TEST_CASE("Watering mature plant does nothing extra") {
    BrusselsSprouts bs;
    for(int i=0;i<15;++i) bs.end_day(); // age=15, adult

    bs.water();
    bs.end_day();
    REQUIRE(bs.symbol() == "R");
    REQUIRE(bs.is_mature());
}