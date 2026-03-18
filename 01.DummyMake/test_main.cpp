#include <gtest/gtest.h>

#include "library.h"

TEST(FooTest, DemoClassTestset)
{
    DemoClass a;
    EXPECT_EQ(a.foo(), 5);
}
