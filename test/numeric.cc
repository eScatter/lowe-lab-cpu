#include <gtest/gtest.h>
#include "../src/numeric/romberg.hh"
#include "../src/numeric/brent.hh"
#include <cmath>

using namespace eScatter;
using namespace numeric;

constexpr double epsilon = 1e-6;

inline double planck_function(double x)
{
    constexpr double A = 15. / (M_PI * M_PI * M_PI * M_PI);
    return A / (pow(x, 5) * (exp(1. / x) - 1));
}

inline double normal(double x) 
{ 
    return 1. / sqrt(2 * M_PI) * exp(-x * x / 2); 
}

TEST(Romberg, Sine) {
    ASSERT_NEAR(2.0, integrate_romberg<double>(sin, 0, M_PI, epsilon, 10), epsilon);
    ASSERT_NEAR(0.0, integrate_romberg<double>(cos, 0, 2*M_PI, epsilon, 10), epsilon);
}

TEST(Romberg, Normal) {
    ASSERT_NEAR(0.5, integrate_romberg<double>(normal, 0, 10, epsilon, 10), epsilon);
}

TEST(Romberg, Planck) {
    ASSERT_NEAR(1.0, integrate_romberg<double>(planck_function, epsilon, 50, epsilon, 15), epsilon);
}

TEST(Brent, Sqrt2) {
    ASSERT_NEAR(sqrt(2), find_root_brent<double>(
        [] (double x) { return x*x; },
        [] (double x) { return x/2.; },
        0., 2., 2., epsilon), epsilon);

    ASSERT_NEAR(0.0, find_root_brent<double>(
        [] (double x) { return integrate_romberg<double>(normal, -10, x, epsilon, 10); },
        normal,
        -10, 10, 0.5, epsilon), epsilon);
}

