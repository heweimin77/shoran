#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int countSpecialNumbers(int n)
    {
        if (n < 10) return n;
        int f[11] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 };
        int count = 0;
        int data[10];
        while (n > 0) {
            data[count++] = n % 10;
            n /= 10;
        }
        int result = 0;
        for (int i = 1; i < count; ++i) {
            result += 9 * f[9] / f[9 - i + 1];
        }
        
        bool visited[10] = { false };
        for (int i = count - 1; i >= 0; --i) {
            for (int x = i == count - 1 ? 1 : 0; x < data[i]; ++x) {
                if (visited[x]) continue;
                result += f[10 - count + i] / f[10 - count];
            }
            if (visited[data[i]]) break;
            visited[data[i]] = true;
            if (i == 0) ++result;
        }

        return result;
    }
};

class TestSolution :public testing::Test
{
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.countSpecialNumbers(20);
    decltype(actual) expect = 19;
    EXPECT_EQ(expect, actual);
}

}

