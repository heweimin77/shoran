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
    vector<int> productQueries(int n, vector<vector<int>> &queries)
    {
        vector<int> powers;
        for (int base = 1, p = 0; base <= n; base <<= 1, ++p) {
            if (base & n) powers.push_back(p);
        }
        int ps = 0;
        for (auto &p : powers) {
            ps += p;
            p = ps;
        }
        vector<int> results;
        results.reserve(queries.size());
        for (auto &q : queries) {
            int x = powers[q[1]];
            if (q[0] > 0) x -= powers[q[0] - 1];
            results.push_back(fast_power(2, x, 1e9+7));
        }
        return results;
    }
    long long fast_power(long long base, long long n, long long module)
    {
        long long result = 1;
        int mask = 1;
        for (int mask = 1; mask <= n; mask <<= 1) {
            if (mask & n) {
                result *= base;
                result %= module;
            }
            base *= base;
            base %= module;
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
    vector<vector<int>> queries = {{0, 1}, {2, 2}, {0, 3}};
    Solution s;
    auto actual = s.productQueries(15, queries);
    decltype(actual) expect = {2, 4, 64};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
