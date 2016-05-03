#include <gtest/gtest.h>
#include "../src/cornell-box/black-body.hh"
#include "../src/cornell-box/rng.hh"
#include "../src/cornell-box/colour.hh"

template <typename T>
testing::AssertionResult IsInRange(T value, T low, T high) 
{   
    if (value < low)
        return testing::AssertionFailure() << value << " < lower bound " << low;
    else if (value > high)
        return testing::AssertionFailure() << value << " > upper bound " << high;
    else
        return testing::AssertionSuccess() << value << " is in range ["  << low << ", " << high << "]";
}

using namespace cornell;

TEST(Cornell, BlackBody)
{
    BlackBody<double> f(Rng::generator(), 5000.0);
    for (unsigned i = 0; i < 100; ++i)
    {
        EXPECT_TRUE(IsInRange(f(), 0.39, 0.83));
    }
}

TEST(Cornell, CIE_XYZ)
{

}

