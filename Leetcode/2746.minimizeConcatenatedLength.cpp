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
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class Solution {
#define MAKE_STATE(x, y)  ((x) << 8 | (y) )
#define GET_X(state)   ((state) >> 8)
#define GET_Y(state)   ((state) &0xFF)

public:
    int minimizeConcatenatedLength(vector<string>& words) {
        unordered_map<int, int> results;
        int h = words[0].front() - 'a', t = words[0].back() - 'a';
        results[MAKE_STATE(h, t)] = words[0].size();
        for (int i = 1; i < words.size(); ++i) {
            string& w = words[i];
            h = w.front() - 'a', t = w.back() - 'a';
            unordered_map<int, int> nexts;
            for (auto& r : results) {
                int hh = GET_X(r.first);
                int tt = GET_Y(r.first);
                int ns = MAKE_STATE(h, tt);
                int nv = r.second + w.size() - (t == hh ? 1 : 0);
                auto it = nexts.find(ns);
                if (it == nexts.end()) {
                    nexts.insert({ ns, nv });
                } else {
                    it->second = min(it->second, nv);
                }
                ns = MAKE_STATE(hh, t);
                nv = r.second + w.size() - (tt == h ? 1 : 0);
                it = nexts.find(ns);
                if (it == nexts.end()) {
                    nexts.insert({ ns, nv });
                } else {
                    it->second = min(it->second, nv);
                }
            }
            results = std::move(nexts);
        }
        int result = INT_MAX;
        for (auto& r : results) {
            result = min(result, r.second);
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

TEST_F(TestSolution, Test1)
{
    vector<string> words = { "aa","ab","bc" };
    Solution s;
    auto actual = s.minimizeConcatenatedLength(words);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<string> words = { "aab","ba"};
    Solution s;
    auto actual = s.minimizeConcatenatedLength(words);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
}
