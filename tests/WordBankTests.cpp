#include <gtest/gtest.h>
#include "word_bank.h"

TEST(HelloTest, BasicAssertions) {
    WB wb;
    InitWordBank("test-file.txt", &wb);
    DestroyWordBank(&wb);
    EXPECT_EQ(7 * 6, 43);
}