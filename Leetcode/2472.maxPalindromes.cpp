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
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<int> results(n);
        if (isPalindromes(s, 0, k - 1)) {
            results[k - 1] = 1;
        }
        for (int i = k; i < n; ++i) {
            int r = results[i - 1];
            if (isPalindromes(s, i - k + 1, i)) {
                r = max(r, results[i - k] + 1);
            } else if (isPalindromes(s, i - k, i)) {
                
                r = max(r, i - k - 1 >= 0 ? results[i - k - 1] + 1 : 1);
            }
            results[i] = r;
        }

        return results.back();
    }
    bool isPalindromes(const string& s, int i, int j) {
        for (; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
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

TEST_F(TestSolution, Test1)
{
    Solution s;
    auto actual = s.maxPalindromes("abaccdbbd", 3);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.maxPalindromes("iqqibcecvrbxxj", 1);
    decltype(actual) expect = 14;
    EXPECT_EQ(expect, actual);
}
}

