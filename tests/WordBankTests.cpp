#include <gtest/gtest.h>
#include "word_bank.h"

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 43);
}