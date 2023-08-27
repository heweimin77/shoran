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
    static constexpr int MOD = 1e9 + 7;
public:
    int totalStrength(vector<int> &strength)
    {
        int n = strength.size();
        vector<int> lsums(n), lssums(n);
        long long s = 0;
        long long ss = 0;
        for (long long i = 0; i < n; ++i) {
            s += strength[i];
            ss += strength[i] * (i + 1);
            s %= MOD;
            ss %= MOD;
            lsums[i] = s;
            lssums[i] = ss;
        }
        vector<int> rsums(n), rssums(n);
        s = ss = 0;
        for (long long i = n - 1; i >= 0; --i) {
            s += strength[i];
            ss += strength[i] * (n - i);
            s %= MOD;
            ss %= MOD;
            rsums[i] = s;
            rssums[i] = ss;
        }

        vector<int> lindexes(n);
        stack<pair<int, int>> lvalueindexes;
        lvalueindexes.push({ -1, -1 });
        for (int i = 0; i < n; ++i) {
            while (lvalueindexes.top().first > strength[i]) {
                lvalueindexes.pop();
            }
            lindexes[i] = lvalueindexes.top().second;
            if (lvalueindexes.top().first == strength[i]) {
                lvalueindexes.top().second = i;
            } else {
                lvalueindexes.push({ strength[i], i });
            }
        }
        vector<int> rindexes(n);
        stack<pair<int, int>> rvalueindexes;
        rvalueindexes.push({ -1, n });
        for (int i = n - 1; i >= 0; --i) {
            while (rvalueindexes.top().first >= strength[i]) {
                rvalueindexes.pop();
            }
            rindexes[i] = rvalueindexes.top().second;
            if (rvalueindexes.top().first == strength[i]) {
                rvalueindexes.top().second = i;
            } else {
                rvalueindexes.push({ strength[i], i });
            }
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            int left = lindexes[i], right = rindexes[i];
            int lcnt = i - left, rcnt = right - i;
            long long r = lssums[i], rr = lsums[i];
            if (left >= 0) {
                r += MOD - lssums[left];
                rr += MOD - lsums[left];
                rr *= (left + 1);
                rr %= MOD;
                r += MOD - rr;
                r %= MOD;
            }
            r *= strength[i];
            r %= MOD;
            r *= rcnt;
            result += r;


            r = rssums[i], rr = rsums[i];
            if (right < n) {
                r += MOD - rssums[right];
                rr += MOD - rsums[right];
                rr *= (n - right);
                rr %= MOD;
                r += MOD - rr;
                r %= MOD;
            }
            r *= strength[i];
            r %= MOD;
            r *= lcnt;
            result += r;

            r = (long long)strength[i] * strength[i];
            r %= MOD;
            r *= lcnt;
            r %= MOD;
            r *= rcnt;
            r %= MOD;

            result += MOD - r;
            result %= MOD;
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
    vector<int> strength = { 1,3,1,2 };
    Solution s;
    auto actual = s.totalStrength(strength);
    decltype(actual) expect = 44;
    EXPECT_EQ(expect, actual);
}

}

