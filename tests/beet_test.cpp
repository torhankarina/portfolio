#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/beet.hpp"

TEST_CASE( "it returns a ~ as its when beet is a tilled soil" ) {
    Beet beet;
    REQUIRE( beet.symbol() == "~" );
}