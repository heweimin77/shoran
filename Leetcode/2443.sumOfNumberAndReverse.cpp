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
    bool sumOfNumberAndReverse(int num)
    {
        int base = 10;
        while (base <= num) base *= 10;
        base /= 10;
        if (isOK(num, base, true)) return true;
        if (num / base == 1 && isOK(num, base / 10, true)) return true;
        return false;

    }
    bool isOK(int num, int base, bool first)
    {
        if (num < 0) return false;
        if (base == 0) return num == 0;
        if (base == 1) return (num & 1) == 0;
        int x1 = num % 10;
        int x2 = num / base;
        int xx = -1;
        if (x1 == x2) {
            xx = x1;
        } else if (x1 + 1 == x2) {
            xx = x1;
        } else if (x1 + 10 == x2) {
            xx = x1 + 10;
        } else if (x1 + 10 + 1 == x2) {
            xx = x1 + 10;
        }
        if (xx == -1 || xx > 18 || (first && xx == 0)) return false;
        return isOK((num - xx * (1 + base)) / 10 , base / 100, false);
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
    auto actual = s.sumOfNumberAndReverse(99998);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}

}
