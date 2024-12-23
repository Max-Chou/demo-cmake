#include <gtest/gtest.h>
#include "../path.hpp"

TEST(PathTest, ConstructorAndGetter) {
    Path path("/usr/local/bin");
    EXPECT_EQ(path.get_path(), "/usr/local/bin");
}

TEST(PathTest, EmptyPath) {
    Path path("");
    EXPECT_EQ(path.get_path(), "");
} 