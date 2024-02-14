#include <gtest/gtest.h>
#include "helper.hpp"

TEST(toLower, lowercase)
{
    EXPECT_EQ(toLower("pO"), "po");
}