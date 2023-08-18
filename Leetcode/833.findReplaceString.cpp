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
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int n = indices.size();
        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&](const int lhs, const int rhs) {
            return indices[lhs] < indices[rhs];
            });

        string result;
        int last = 0;
        for (auto index : indexes) {
            if (equal(sources[index].begin(), sources[index].end(), s.begin() + indices[index])) {
                result += string(s.begin() + last, s.begin() + indices[index]);
                result += targets[index];
                last = indices[index] + sources[index].size();
            }
        }
        result += string(s.begin() + last, s.end());
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

TEST_F(TestSolution, Test1)
{
    vector<int> indices = {0, 2};
    vector<string> sources = { "a","cd" };
    vector<string> targets = { "eee","ffff" };
    Solution s;
    auto actual = s.findReplaceString("abcd", indices, sources, targets);
    decltype(actual) expect = "eeebffff";
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> indices = { 3, 5, 1 };
    vector<string> sources = { "kg","ggq","mo" };
    vector<string> targets = { "s","so","bfr" };
    Solution s;
    auto actual = s.findReplaceString("vmokgggqzp", indices, sources, targets);
    decltype(actual) expect = "vbfrssozp";
    EXPECT_EQ(expect, actual);
}
}

