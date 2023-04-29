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

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minGroups(vector<vector<int>> &intervals)
    {
        multiset<pair<int, int>> data;
        for (auto &i : intervals) {
            data.insert({ i[0], i[1] });
        }
        int result = 0;
        while (!data.empty()) {
            ++result;
            pair<int, int> next = { data.begin()->second + 1, data.begin()->second + 1 };
            auto it = data.erase(data.begin());
            while ((it = data.lower_bound(next)) != data.end()) {
                next = { it->second + 1, it->second };
                data.erase(it);
            }

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
    vector<vector<int>> intervals = {{5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}};
    Solution s;
    auto actual = s.minGroups(intervals);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}
