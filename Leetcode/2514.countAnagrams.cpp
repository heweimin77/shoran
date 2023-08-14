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
    int countAnagrams(string s)
    {
        data.resize(2);
        data[0] = data[1] = 1;
        s += ' ';
        long long result = 1;
        array<int, 26> counts = { 0 };
        for (auto ch : s) {
            if (ch == ' ') {
                result *= getCount(counts);
                result %= MOD;
                counts.fill(0);
            } else {
                ++counts[ch - 'a'];
            }
        }

        return result;
    }
    long long getCount(array<int, 26> &counts)
    {
        int sum = accumulate(counts.begin(), counts.end(), 0);
        long long r = getData(sum);
        long long p = 1;
        for (auto n : counts) {
            if (n == 0) continue;
            p *= getData(n);
            p %= MOD;
        }
        r *= invert(p, MOD);
        return r % MOD;
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

    // https://oi-wiki.org/math/number-theory/inverse/ 逆元
    // a * x = 1 (mod p) 则x 是a的逆元
    // a * x = a^(p - 1) (mod p) 费马小定理
    // x     = a^(p - 2) (mod p) 
    // 要求；ｐ是质数，a,p互质
    long long invert(long long a, long long p)
    {
        return fast_power(a, p - 2, p);
    }

    int getData(int n) {
        if (n < data.size()) return data[n];
        long long x = data.size();
        data.resize(n + 1);
        for (; x <= n; ++x) {
            data[x] = (data[x - 1] * x) % MOD;
        }
        return data[n];
    }

private:
    vector<int> data;
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
    auto actual = s.countAnagrams("too hot");
    decltype(actual) expect =18;
    EXPECT_EQ(expect, actual);
}
}

