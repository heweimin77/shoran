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
public:
    int maximumTastiness(vector<int> &price, int k)
    {
        if (k == 2) return *max_element(price.begin(), price.end()) - *min_element(price.begin(), price.end());
        sort(price.begin(), price.end());
        int low = 0, high = price.back() - price.front();
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            if (isOk(price, mid, k)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }
    bool isOk(vector<int> &price, int m, int k)
    {
        auto it = price.begin();
        for (int i = 1; i < k; ++i) {
            it = lower_bound(it, price.end(), *it + m);
            if (it == price.end()) {
                return false;
            }
        }
        return true;
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
    vector<int> price = { 13,5,1,8,21,2 };
    Solution s;
    auto actual = s.maximumTastiness(price, 3);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}

}

