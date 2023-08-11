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

#include "support.h"

using namespace std;

namespace {

class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        vector<int> results(target + 1);
        results[0] = 1;
        for (auto& t : types) {
            for (int i = target; i >= t[1] && i > target - t[1]; --i) {
                int p = i - t[1];
                long long s = 0;
                for (int j = 0; j < t[0] && p >= 0; ++j) {
                    s += results[p];
                    p -= t[1];
                }
                results[i] = (s + results[i]) % MOD;

                for (int x = i - t[1]; x > 0; x -= t[1]) {
                    s -= results[x];
                    if (p >= 0) {
                        s += results[p];
                        p -= t[1];
                    }
                    results[x] = (s + results[x]) % MOD;
                }
            }
            //cout << t[0] << ":";
            //for (auto r : results) {
            //    cout << " " << r;
            //}
            //cout << endl;
        }

        return results[target];
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
    vector<vector<int>> types = { {6,1}, {3,2}, {2,3} };
    Solution s;
    auto actual = s.waysToReachTarget(6, types);
    decltype(actual) expect = 7;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> types = { {6,1}, {3,2}, {2,3} };
    Solution s;
    auto actual = s.waysToReachTarget(18, types);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}
