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
    static constexpr int MOD = 1e9 + 7;
public:
    int numberOfWays(string s, string t, long long k) {
        int f0 = 0, f1 = 0;
        if (s == t) f0 = 1;
        else f1 = 1;

        int n = s.size();
        vector<int> match = kmp_patten(t);
        s += s;
        s.pop_back();
        int c = kmp_search(s, t, match);

        vector<vector<int>> r = { {f0}, {f1} };
        vector<vector<int>> x = { {c - 1, c}, {n - c, n - c - 1} };
        vector<vector<int>> xx = fastpower(x, k);
        r = multipy(xx, r);
        return r[0][0];
    }
    
    vector<vector<int>> fastpower(vector<vector<int>>& x, long long k) {
        vector<vector<int>> r = { {1, 0}, {0, 1} };
        for (; k; k >>= 1) {
            if (1 & k) {
                r = multipy(r, x);
            }
            x = multipy(x, x);
        }
        return r;
    }
    vector<vector<int>> multipy(vector<vector<int>>& x, vector<vector<int>>& y) {
        vector<vector<int>> result(x.size(), vector<int>(y[0].size()));
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j < result[0].size(); ++j) {
                long long r = 0;
                for (int k = 0; k < y.size(); ++k) {
                    r += (long long)x[i][k] * y[k][j];
                    r %= MOD;
                }
                result[i][j] = r;
            }
        }
        return result;
    }


    vector<int> kmp_patten(const string& pattern) {
        int n = pattern.size();
        vector<int> match(n);
        match[0] = 0;
        for (int i = 1; i < n; ++i) {
            int cnt = 0;
            for (cnt = match[i - 1]; cnt > 0 ; cnt = match[cnt]) {
                if (pattern[i] == pattern[cnt]) {
                    match[i] = cnt + 1;
                    break;
                }
                if (cnt == match[cnt]) {
                    break;
                }
            }
            if (match[i] == 0 && pattern[0] == pattern[i]) {
                match[i] = 1;
            }
        }
        return match;
    }

    int kmp_search(const string& s, const string& p, vector<int>& match) {
        int result = 0;
        int x = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == p[x]) {
                ++x;
                if (x < p.size()) {
                    continue;
                }
                ++result;
                x = match[x - 1];
                continue;
            }
            for (x = match[x]; x > 0; x = match[x]) {
                if (s[i] == p[x]) {
                    ++x;
                    break;
                }
                if (x == match[x]) {
                    x = 0;
                    break;
                }
            }
            if (x == 0 && s[i] == p[x]) {
                x = 1;
            }
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

TEST_F(TestSolution, Test1)
{
    Solution s;
    auto actual = s.numberOfWays("abcd", "cdab", 2);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    Solution s;
    auto actual = s.numberOfWays("ceoceo", "eoceoc", 4);
    decltype(actual) expect = 208;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    Solution s;
    auto actual = s.numberOfWays("ababab", "ababab", 1);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    Solution s;
    auto actual = s.numberOfWays("uhixx", "xxuhi", 3);
    decltype(actual) expect = 13;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test5)
{
    Solution s;
    auto actual = s.numberOfWays("uuuuuuuuu", "uuuuuuuuu", 10);
    decltype(actual) expect = 73741817;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.numberOfWays("hmwfh", "hhmwf", 10);
    decltype(actual) expect = 209715;
    EXPECT_EQ(expect, actual);
}

}
