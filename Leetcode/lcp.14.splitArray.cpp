#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int splitArray(vector<int> &nums)
    {
        int maxnum = *max_element(nums.begin(), nums.end());
        vector<int> min_factor(maxnum + 1);
        vector<int> primes;
        for (int i = 2; i <= maxnum; ++i) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (i * p > maxnum) break;
                min_factor[i * p] = p;
                if (p == min_factor[i]) break;
            }
        }

        int result = 0;
        unordered_map<int, int> dps;
        vector<int> factors;
        for (auto n :  nums) {
            int nresult = result + 1;
            factors.clear();
            factors.push_back(min_factor[n]);
            for (int x = n; x > 1; x /= min_factor[x]) {
                if (min_factor[x] != factors.back()) {
                    factors.push_back(min_factor[x]);
                }
            }

            for (auto p : factors) {
                auto it = dps.find(p);
                if (it == dps.end()) {
                    dps[p] = result + 1;
                } else {
                    nresult = min(nresult, it->second);
                    it->second = min(it->second, result + 1);
                }
            }
            result = nresult;
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
    //vector<int> nums = { 968311,967753,966677,968573,966527,966653,967319,967663,967931,968021,967961,968423,966727,967937,967699,966883,968017,968311,967781,966617,967937 };
    //vector<int> nums = { 2,967753,966677,968573,966527,966653,967319,967663,967931,968021,967961,968423,966727,3,967699,966883,968017,2,5,7,3 };
    vector<int> nums = { 968311,967753,966677,968573,966527,966653,967319,967663,967931,968021,967961,968423,966727,967937,967699,966883,968017,968311,967781,966617,967937 };
    Solution s;
    auto actual = s.splitArray(nums);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}

}
