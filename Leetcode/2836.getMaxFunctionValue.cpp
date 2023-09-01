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
#include <stack>
#include "support.h"

using namespace std;

namespace {

class Solution {
    using ll = long long;
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        int n = receiver.size();
        vector<vector<int>> parents(n);
        for (int i = 0; i < n; ++i) parents[receiver[i]].push_back(i);

        vector<bool> visited(n);
        vector<ll> results(n, -1);
        for (int i = 0; i < n; ++i) {
            if (results[i] >= 0) continue;
            int j = i;
            for (; !visited[j]; j = receiver[j]) {
                visited[j] = true;
            }
            vector<int> loop{ j };
            for (int k = receiver[j]; k != j; k = receiver[k]) {
                loop.push_back(k);
            }
            int ln = loop.size();
            vector<ll> sums;
            ll s = 0;
            for (auto lp : loop) {
                s += lp;
                sums.push_back(s);
            }

            function<ll(int, ll)> getresult = [&](int j, ll kk) {
                ll r = (kk / ln) * sums.back();
                kk %= ln;
                if (kk == 0) return r;
                if (j == 0) return r + sums[kk - 1];
                if (ln - j >= kk) return r + sums[j + kk - 1] - sums[j - 1];
                return r + sums[ln - 1] - sums[j - 1] + sums[kk - ln + j - 1];
            };

            deque<int> data;
            function<void(int, int, ll)> dfs = [&](int j, int now, ll ss) {
                int x = -1;
                if (data.size() > k + 1) {
                    x = data.front();
                    data.pop_front();
                    ss -= x;
                }
                results[now] = ss + getresult(j, k + 1 - data.size());

                for (auto p : parents[now]) {
                    if (results[p] >= 0) continue;
                    data.push_back(p);
                    dfs(j, p, ss + p);
                    data.pop_back();
                }
                if (x >= 0) {
                    data.push_front(x);
                    ss += x;
                }
            };

            for (int j = 0; j < ln; ++j) {
                results[loop[j]] = getresult(j, k + 1);
            }
            for (int j = 0; j < ln; ++j) {
                dfs(j, loop[j], 0);
            }
        }

        return *max_element(results.begin(), results.end());
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
    vector<int> receiver = { 2,0,1 };
    Solution s;
    auto actual = s.getMaxFunctionValue(receiver, 4);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}

}
