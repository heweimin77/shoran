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
    using Record = pair<string, string>;
public:
    string evolutionaryRecord(vector<int>& parents) {
        int n = parents.size();
        vector<vector<int>> children(n);
        int root = 0;
        for (int i = 0; i < n; ++i) {
            if (parents[i] == -1) {
                root = i;
                continue;
            }
            children[parents[i]].push_back(i);
        }
        return getRecord(children, root).second;
    }
    Record getRecord(vector<vector<int>> &children, int i) {
        if (children[i].empty()) return { "", "" };

        priority_queue<Record, vector<Record>, std::greater<Record>> q;
        for (auto& child : children[i]) {
            Record r = getRecord(children, child);
            q.push({ "0" + r.first + "1", "0" + r.second });
        }
        string s;
        while (q.size() > 1) {
            s += q.top().first;
            q.pop();
        }
        return { s + q.top().first, s + q.top().second };
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
    vector<int> parents = { -1,0,0,2 };
    Solution s;
    auto actual = s.evolutionaryRecord(parents);
    decltype(actual) expect = "00110";
    EXPECT_EQ(expect, actual);
}
}

