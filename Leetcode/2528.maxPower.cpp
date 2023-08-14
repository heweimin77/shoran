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
    long long maxPower(vector<int> &stations, int r, int k)
    {
        int n = stations.size();
        vector<long long> counts(n);
        long long cnt = accumulate(stations.begin(), stations.begin() + r + 1, 0LL);
        counts[0] = cnt;
        for (int i = 1; i < n; ++i) {
            if (i + r < n) cnt += stations[i + r];
            if (i - r - 1 >= 0) cnt -= stations[i - r - 1];
            counts[i] = cnt;
        }
        long long low = 0, high = counts[0] + k + 1;
        while (low + 1 < high) {
            auto mid = (low + high) / 2;
            if (ok(counts, r, k, mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }
    bool ok(const vector<long long> &counts, int r, int k, long long t)
    {
        r += r + 1;
        int n = counts.size();
        vector<int> delta(n);
        int x = 0;
        for (int i = 0; i < counts.size(); ++i) {
            x -= delta[i];
            if (counts[i] + x >= t) {
                continue;
            }
            auto d = t - counts[i] - x;
            if (d > k) return false;
            k -= d;
            if (i + r < n) delta[i + r] = d;
            x += d;
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
    vector<int> stations = { 1,2,4,5,0 };
    Solution s;
    auto actual = s.maxPower(stations, 1, 2);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<int> stations = { 4,4,4,4 };
    Solution s;
    auto actual = s.maxPower(stations, 0, 3);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> stations = { 2,10,12,3 };
    Solution s;
    auto actual = s.maxPower(stations, 0, 14);
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}
}
