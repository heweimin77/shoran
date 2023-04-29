#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minimizeXor(int num1, int num2)
    {
        int n1 = getbitnums(num1);
        int n2 = getbitnums(num2);
        if (n1 >= n2) {
            for (int cnt = n1 - n2; cnt > 0; --cnt) {
                num1 &= (num1 - 1);
            }
        } else {
            for (int cnt = n2 - n1, mask = 1; cnt > 0; mask <<= 1) {
                if ((num1 & mask) == 0) {
                    --cnt;
                    num1 |= mask;
                }
            }
        }
        return num1;
    }
    int getbitnums(int n)
    {
        int cnt = 0;
        while (n > 0) {
            ++cnt;
            n &= n - 1;
        }
        return cnt;
    }
};

class TestSolution :public testing::Test {
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(TestSolution, Test1)
{
    Solution s;
    auto actual = s.minimizeXor(3, 5);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}
