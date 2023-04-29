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
    vector<string> maxRectangle(vector<string> &words)
    {
        map<int, vector<string>> wordblocks;
        for (auto w : words) {
            wordblocks[w.size()].push_back(w);
        }
        vector<string> results;
        for (auto it = wordblocks.rbegin(); it != wordblocks.rend(); ++it) {
            for (auto w1 : it->s) {

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
    vector<string> words = { "this", "real", "hard", "trh", "hea", "iar", "sld" };
    Solution s;
    auto actual = s.maxRectangle(words);
    decltype(actual) expect = { "this",  "real", "hard" };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
