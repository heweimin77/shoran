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
    vector<int> recoverArray(int n, vector<int>& sums) {
        sort(sums.begin(), sums.end());
        unordered_map<int, int> xxx{ {1, 0}, {2, 1}, {4, 2}, {8, 3}, {16, 4}, {32, 5}, {64, 6}, {128, 7},
                                     {256,8}, {512,9}, {1024,10}, {2048,11}, {4096,12},{8192,13},{16384,14},
                                     {32768,15} };
        int xmin = sums[0];

        int cnt = 0;
        for (auto x : sums) {
            if (x != xmin) break;
            ++cnt;
        }
        vector<int> results(xxx[cnt], 0);
        if (cnt > 1) {
            int i = 0;
            for (int j = 0; j < sums.size(); j += cnt) {
                sums[i++] = sums[j];
            }
            sums.resize(i);
        }

        auto limit = sums.end();
        while (limit - sums.begin() > 1) {
            int r = sums[1] - sums[0];
            int j = 0;
            bool zero = false;
            auto jt = sums.begin();
            for (auto it = sums.begin(); it != limit; ++it) {
                if (*it == INT_MAX) continue;
                if (*it == 0) zero = true;
                while (*jt < *it + r) ++jt;
                *jt++ = INT_MAX;
            }
            limit = remove(sums.begin(), limit, INT_MAX);
            if (!zero) {
                for (auto it = sums.begin(); it != limit; ++it) *it += r;
                r = -r;
            }
            results.push_back(r);
        }


        return results;
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
    vector<int> sums = { -3,-2,-1,0,0,1,2,3 };
    Solution s;
    auto actual = s.recoverArray(3, sums);
    decltype(actual) expect = {1, 2, -3};
    EXPECT_EQ_CONTAINER(expect, actual);
}
}
