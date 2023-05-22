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
    int numTilePossibilities(string tiles) {
        unordered_map<int, int> counts;
        for (auto ch : tiles) {
            ++counts[ch];
        }
        vector<int> cnts;
        for (auto& r : counts) {
            cnts.push_back(r.second);
        }
        sort(cnts.begin(), cnts.end(), greater<int>());
        return getCount(cnts);
    }

    int getCount(vector<int>& cnts) {
        int r = 1;
        for (int i = 0; i < cnts.size(); ++i) {
            vector<int> next = cnts;
            --next[i];
            sort(next.begin(), next.end(), greater<int>());
            if (next.back() == 0) next.pop_back();
            r += getCount(next);
        }
        return r;
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
    auto actual = s.numTilePossibilities("AAB");
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}
}

