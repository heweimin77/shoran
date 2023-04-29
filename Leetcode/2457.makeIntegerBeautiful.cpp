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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target)
    {
        vector<int> data;
        for (long long nn = n; nn > 0; nn /= 10) {
            data.push_back(nn % 10);
        }
        reverse(data.begin(), data.end());
        int x = 0;
        for (int i = 0; i < data.size(); ++i) {
            x += data[i];
            if (x == target) {
                int rest = 0;
                for (int j = i + 1; j < data.size(); ++j) {
                    rest += data[j];
                }
                if (rest > 0) {
                    data[i] = 10;
                    fill(data.begin() + i + 1, data.end(), 0);
                }
                break;
            } else if (x > target) {
                data[i] = 10;
                fill(data.begin() + i + 1, data.end(), 0);
                break;
            }
        }

        long long nn = 0;
        for (auto d : data) {
            nn *= 10;
            nn += d;
        }
        return nn - n;
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
    vector<int> nums = {  };
    Solution s;
    auto actual = s.makeIntegerBeautiful(5756554100, 26);
    decltype(actual) expect = 445900;
    EXPECT_EQ(expect, actual);
    
}

}
