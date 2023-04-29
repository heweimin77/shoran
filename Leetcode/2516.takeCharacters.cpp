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

#include "support.h"

using namespace std;


namespace {

class Solution {
public:
    int takeCharacters(string s, int k)
    {   
        int n = s.size();
        int counts[3] = { 0 };
        int i = 0;
        for (; i < n; ++i) {
            ++counts[s[i] - 'a'];
            if (counts[0] >= k && counts[1] >= k && counts[2] >= k) {
                break;
            }
        }
        if (i == n) return -1;
        int result = i + 1;

        int j = n - 1;
        for (; i >= 0; --i) {
            --counts[s[i] - 'a'];
            for (; !(counts[0] >= k && counts[1] >= k && counts[2] >= k); --j) {
                ++counts[s[j] - 'a'];
            }
            result = min(result, i + n - j - 1);
        }

        return result;
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
    auto actual = s.takeCharacters("aabaaaacaabc", 2);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}

}

