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
    vector<string> twoEditWords(vector<string> &queries, vector<string> &dictionary)
    {
        int n = queries[0].size();
        vector<string> results;
        for (auto &q : queries) {
            bool match = false;
            for (auto &s : dictionary) {
                int mismatch = 0;
                for (int i = 0; i < n && mismatch <= 2; ++i) {
                    if (q[i] != s[i]) ++mismatch;
                }
                if (mismatch <= 2) {
                    match = true;
                    break;
                }
            }

            if (match) {
                results.push_back(q);
            }
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
    vector<string> queries = { "word","note","ants","wood" };
    vector<string> dictionary = { "wood","joke","moat" };
    Solution s;
    auto actual = s.twoEditWords(queries, dictionary);
    decltype(actual) expect = { "word","note","wood" };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
