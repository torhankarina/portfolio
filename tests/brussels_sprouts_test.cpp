#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/brussels_sprouts.hpp"

TEST_CASE( "it returns a ~ as its when brussels sprouts is a tilled soil" ) {
    BrusselsSprouts brussels_sprouts;
    REQUIRE( brussels_sprouts.symbol() == "~" );
}