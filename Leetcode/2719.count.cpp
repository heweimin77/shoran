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
    //static constexpr long long MOD = 1e18 + 7;
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        int n = num2.size();
        results.resize(n);
        results[0].resize(10, 1);
        for (int i = 1; i < n; ++i) {
            auto &pre = results[i - 1];
            auto& now = results[i];
            long long s = 0;
            for (int j = 0; j < 10; ++j) {
                s += pre[j];
                now.push_back(s);
            }
            for (int j = 10; j < pre.size(); ++j) {
                s += pre[j];
                s -= pre[j - 10];
                now.push_back(s);
            }
            for (int j = pre.size(); j < pre.size() + 9; ++j) {
                s -= pre[j - 10];
                now.push_back(s);
            }
        }
        for (int i = 0; i < n; ++i) {
            long long s = 0;
            for (auto& x : results[i]) {
                s += x;
                s %= MOD;
                x = s;
            }
        }

        long long count1 = getcount(num1, min_sum, max_sum);
        long long count2 = getcount(num2, min_sum, max_sum);

        int sum = 0;
        for (auto ch : num1) {
            sum += ch - '0';
        }
        long long result = count2 - count1;
        if (sum >= min_sum && sum <= max_sum) {
            ++result;
        }
        return result % MOD;
    }
    long long getcount(const string& num, int min_sum, int max_sum) {
        long long count1 = getcount(num, min_sum - 1);
        long long count2 = getcount(num, max_sum);
        return MOD + count2 - count1;
    }
    int getcount(const string& num, int sum) {
        if (sum > 9 * num.size()) sum = 9 * num.size();
        long long result = 0;
        for (int i = 0, x = num.size()-2; i < num.size() - 1; ++i, --x) {
            for (int j = 0; j < num[i] - '0'; ++j) {
                if (sum < j) break;
                if (sum - j >= results[x].size()) {
                    result += results[x].back();
                } else {
                    result += results[x][sum - j];
                }
                
            }
            sum -= num[i] - '0';
            if (sum < 0) break;
        }
        if (sum >= 0) {
            result += min(sum, num.back() - '0') + 1;
        }
        return result;
    }
private:
    vector<vector<int>> results;
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
    auto actual = s.count("1", "12", 1, 8);
    decltype(actual) expect = 11;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, Test2)
{
    Solution s;
    auto actual = s.count("6312", "9416", 29, 30);
    decltype(actual) expect = 114;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.count("1", "2000000014", 1, 400);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
}

}
