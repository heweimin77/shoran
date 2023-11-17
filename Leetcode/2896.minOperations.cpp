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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        vector<int> indexes;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                indexes.push_back(i);
            }
        }
        int n = indexes.size();
        if (n == 0) return 0;
        if (n & 1) return -1;

        vector<int> results(n);
        results[0] = 0;
        results[1] = min(x, indexes[1] - indexes[0]);
        for (int i = 2; i < n; ++i) {
            if (i & 1) {
                results[i] = min(results[i - 1] + x, results[i - 2] + indexes[i] - indexes[i - 1]);
            } else {
                results[i] = min(results[i - 1], results[i - 2] + indexes[i] - indexes[i - 1]);
            }
        }

        return results[n - 1];
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
    auto actual = s.minOperations("1100011000", "0101001010", 2);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}

}
