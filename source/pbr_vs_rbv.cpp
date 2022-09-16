#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <iostream>
#include <vector>

#include <Eigen/Eigen>

/*
# Go Ahead, Return by That Value!

TL;DR: Both pass by reference and return by value are equally fast. Return by value results in 
better syntax. Using it should not be a problem.

Is it better to pass by reference, or return by value? C++ programmers are very concerned with
performance and would argue that returning by value causes a copy which will slow down your 
program. Let's test this. I write two functions, one which populates a vector passed by 
reference and another that returns a populated vector by value. Which one is faster? We
will find out by benchmarking using Catch2 banchmarks. 
*/

/*
This functions populates a vector passed by reference.
*/
void fill_random_pbr(int n, std::vector<Eigen::Matrix3d>& vector)
{
    for(auto i = 0; i < n; i++)
    {
        vector.push_back(Eigen::Matrix3d::Random());
    }
}

/*
This functions populates a vector and returns it by value.
*/
std::vector<Eigen::Matrix3d> fill_random_rbv(int n)
{
    auto vector = std::vector<Eigen::Matrix3d>();

    for(auto i = 0; i < n; i++)
    {
        vector.push_back(Eigen::Matrix3d::Random());
    }

    return vector;
}

/**
 * @brief BENCHMARK TEST
 * 
 * We wrap both functions within a benchmark block. Running this code will profile the 
 * performance of both functions.
 */
TEST_CASE("pass by reference vs return by value", "[pbr_vs_rbv]")
{
    // number of elements to populate
    auto n = 1E6;

    // pass by reference banchmark
    BENCHMARK("pbr")
    {
        auto vector = std::vector<Eigen::Matrix3d>();
        fill_random_pbr(n, vector);
        auto size = vector.size();
    };

    // return by value
    BENCHMARK("rbv")
    {
        auto vector = fill_random_rbv(n);   // copy made here?
        auto size = vector.size();
    };
}

/**
 * @brief RESULTS

Randomness seeded to: 4223207383

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pbr_vs_rbv is a Catch2 v3.0.1 host application.
Run with -? for options

-------------------------------------------------------------------------------
pass by reference vs return by value
-------------------------------------------------------------------------------
/Users/vinod/GitHub/vinodkhare/cpp-playground/source/pbr_vs_rbv.cpp:49
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
pbr                                            100             1     7.69369 s 
                                        77.5449 ms     77.382 ms     77.858 ms 
                                        1.11737 ms    625.526 us    1.87783 ms 
                                                                               
rbv                                            100             1     7.88499 s 
                                         77.387 ms    77.1888 ms     77.838 ms 
                                        1.44612 ms     788.45 us    2.87325 ms 
                                                                               

===============================================================================
test cases: 1 | 1 passed
assertions: - none -

SURPRISE! Both are equally fast. So go ahead, return away by that value!

*/