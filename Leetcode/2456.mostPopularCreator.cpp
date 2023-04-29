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
    vector<vector<string>> mostPopularCreator(vector<string> &creators, vector<string> &ids, vector<int> &views)
    {
        unordered_map<string, long long> counts;
        int n = creators.size();
        long long mcount = 0;
        for (int i = 0; i < n; ++i) {
            long long ncount = counts[creators[i]] += views[i];
            mcount = max(mcount, ncount);
        }
        unordered_map<string, int> rrs;
        for (auto &cnt : counts) {
            if (mcount == cnt.second) {
                rrs[cnt.first] = -1;
            }
        }

        for (int i = 0; i < n; ++i) {
            auto it = rrs.find(creators[i]);
            if (it == rrs.end()) continue;
            if (it->second == -1) {
                it->second = i;
            } else {
                int j = it->second;
                if (views[i] > views[j] || (views[i] == views[j] && ids[i] < ids[j])) {
                    it->second = i;
                }
            }
        }

        vector<vector<string>> results;
        for (auto &r : rrs) {
            results.push_back({ r.first, ids[r.second] });
        }
        return results;
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
    vector<string> creators = { "alice","bob","alice","chris" };
    vector<string> ids = { "one","two","three","four" };
    vector<int> views = { 5,10,5,4 };
    Solution s;
    auto actual = s.mostPopularCreator(creators, ids, views);
    decltype(actual) expect = {{"alice", "one"}, {"bob", "two"}};
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
}

}
