#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int getNandResult(int k, vector<int>& arr, vector<vector<int>>& operations) {
        int n = arr.size();
        array<set<int>, 32> zeros;
        for (int i = 0; i < arr.size(); ++i) {
            int v = arr[i];
            for (int j = 0, mask = 1; j < k; ++j, mask <<= 1) {
                if ((v & mask) == 0) {
                    zeros[j].insert(i);
                }
            }
        }
        int result = 0;
        for (auto& op : operations) {
            if (op[0] == 0) {
                int x = op[1];
                int y = op[2];
                int v = arr[x];
                for (int j = 0, mask = 1; j < k; ++j, mask <<= 1) {
                    if ((v & mask) == (y & mask)) continue;
                    if (y & mask) {
                        zeros[j].erase(x);
                    } else {
                        zeros[j].insert(x);
                    }
                }
                arr[x] = y;
            } else {
                int r = 0;
                int x = op[1];
                int y = op[2];
                int nx = (n & x) & 1; //单bit乘使用& 
                for (int j = 0, mask = 1; j < k; ++j, mask <<= 1) {
                    auto& zero = zeros[j];
                    if (zero.empty()) {
                        r ^= nx ? (~y & mask) : (y & mask);
                    } else {
                        int x = *zero.rbegin();
                        r ^= (n - x) & 1 ? mask : 0;
                    }
                }
                result ^= r;
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

TEST_F(TestSolution, TestMain)
{
    vector<int> arr = {1,2};
    vector<vector<int>> operations = {{1, 2, 3}, {0, 0, 3}, {1, 2, 2}};
    Solution s;
    auto actual = s.getNandResult(3, arr, operations);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

