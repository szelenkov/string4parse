#include "../include/string4parse.h"
#include "gtest/gtest.h"


class String4ParseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code that will be called before each test
    }
};

TEST_F(String4ParseTest, DefaultConstructor) {
    string4parse::string4parse s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.length(), 0);
}

TEST_F(String4ParseTest, ConstructFromCString) {
    const char* test_str = "Hello, World!";
    string4parse::string4parse s(test_str);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.length(), strlen(test_str));
}

TEST_F(String4ParseTest, ConstructFromStdString) {
    std::string test_str = "Hello, World!";
    string4parse::string4parse s(test_str);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.length(), test_str.length());
}

TEST_F(String4ParseTest, CopyConstructor) {
    string4parse::string4parse original("Hello");
    string4parse::string4parse copy(original);
    EXPECT_EQ(copy.length(), original.length());
    EXPECT_FALSE(copy.empty());
}

TEST_F(String4ParseTest, AssignmentOperator) {
    string4parse::string4parse s1("Hello");
    string4parse::string4parse s2;
    s2 = s1;
    EXPECT_EQ(s2.length(), s1.length());
    EXPECT_FALSE(s2.empty());
}

TEST_F(String4ParseTest, EmptyString) {
    string4parse::string4parse s("");
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.length(), 0);
}

TEST_F(String4ParseTest, Iterator) {
    string4parse::string4parse s("abc");
    auto it = s.begin();
    EXPECT_NE(it, s.end());
    
    // Test iterator advancement
    std::advance(it, 1);
    EXPECT_NE(it, s.end());
    
    std::advance(it, 2);
    EXPECT_EQ(it, s.end());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}