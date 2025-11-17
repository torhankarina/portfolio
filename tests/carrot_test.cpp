#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/carrot.hpp"

TEST_CASE( "it returns a c as its when it is a seedling" ) {
    Carrot carrot;
    REQUIRE( carrot.symbol() == "~" );
}

TEST_CASE( "it returns a C when the carrot is grown" ) {
    Carrot carrot;
    carrot.end_day();
    REQUIRE( carrot.symbol() == "C" );
}