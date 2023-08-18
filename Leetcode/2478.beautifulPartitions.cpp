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
    int beautifulPartitions(string s, int k, int minLength) {
        int n = s.size();
        bool isPrimes[10] = { false, false, true, true, false, true, false, true, false, false };
        if (!isPrimes[s[0] - '0'] || (isPrimes[s[n - 1] - '0'])) return 0;

        vector<int> indexes;
        indexes.push_back(0);
        for (int i = 1; i < s.size(); ++i) {
            if (isPrimes[s[i] - '0'] && !isPrimes[s[i - 1] - '0']) indexes.push_back(i);
        }
        indexes.push_back(n);

        vector<vector<int>> results(indexes.size(), vector<int>(k + 1));
        int i = 0;
        for (; i < indexes.size(); ++i) {
            if (indexes[i] >= minLength) break;
        }
        for (; i < indexes.size(); ++i) results[i][1] = 1;
        
        for (int x = 2; x <= k; ++x) {
            int r = 0;
            int j = 0;
            for (int i = 1; i < indexes.size(); ++i) {
                while (indexes[i] - indexes[j] >= minLength) {
                    r += results[j++][x - 1];
                    if (r >= MOD) r -= MOD;
                }
                results[i][x] = r;
            }
        }

        return results.back().back();
    }
};

class Solution2Timeout68 {
    static constexpr int MOD = 1e9 + 7;
public:
    int beautifulPartitions(string s, int k, int minLength) {
        int n = s.size();
        bool isPrimes[10] = { false, false, true, true, false, true, false, true, false, false };
        if (!isPrimes[s[0] - '0'] || (isPrimes[s[n - 1] - '0'])) return 0;

        vector<int> indexes;
        indexes.push_back(0);
        for (int i = 1; i < s.size(); ++i) {
            if (isPrimes[s[i] - '0'] && !isPrimes[s[i - 1] - '0']) indexes.push_back(i);
        }
        indexes.push_back(n);

        vector<vector<int>> results(indexes.size(), vector<int>(k + 1));
        results[0][0] = 1;
        for (int i = 1; i < indexes.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (indexes[i] - indexes[j] < minLength) break;
                for (int x = 1; x <= k; ++x) {
                    results[i][x] += results[j][x - 1];
                    if (results[i][x] >= MOD) results[i][x] -= MOD;
                }
            }
        }
        return results.back().back();
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
    auto actual = s.beautifulPartitions("23542185131", 3, 2);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

