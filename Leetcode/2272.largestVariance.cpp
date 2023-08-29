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
    static constexpr int MAXCNT = 26;
public:
    int largestVariance(string s) {
        bool visited[MAXCNT] = { 0 };
        bool lastvisited[MAXCNT] = { 0 };
        int counts[MAXCNT] = { 0 };
        int chcounts[MAXCNT] = { 0 };
        int lastv[MAXCNT];
        for (auto ch : s) visited[ch - 'a'] = true;
        int result = 0;

        function<void(char)> traverse = [&](char ch) {
            fill(lastv, lastv + MAXCNT, -1);
            memset(counts, 0, sizeof(counts));
            memset(chcounts, 0, sizeof(counts));

            for (auto c : s) {
                if (c != ch) {
                    ++counts[c - 'a'];
                } else {
                    for (int i = 0; i < MAXCNT; ++i) {
                        if (ch == 'a' + i) continue;
                        if (lastv[i] == -1 && counts[i] == 0) {
                            ++chcounts[i];
                            continue;
                        }

                        int r = 0;
                        if (lastv[i] != -1) {
                            r = max(r, lastv[i] + 1 - counts[i]);
                        } else {
                            r = max(r, chcounts[i] + 1 - counts[i]);
                        }
                        if (counts[i] > 0) {
                            r = max(r, chcounts[i] + 1 - counts[i]);
                            result = max(result, chcounts[i] - 1);
                        }
                        result = max(result, r);
                        lastv[i] = r;
                        if (counts[i] == 0) ++chcounts[i];
                        else chcounts[i] = 1;
                        counts[i] = 0;
                    }
                }
            }

            memset(lastvisited, 0, sizeof(lastvisited));
            for (auto it = s.rbegin(); it != s.rend(); ++it) {
                if (*it == ch) break;
                lastvisited[*it - 'a'] = true;
            }
            for (int i = 0; i < MAXCNT; ++i) {
                if (lastvisited[i]) {
                    result = max(result, chcounts[i] - 1);
                }
            }
        };

        for (int i = 0; i < MAXCNT; ++i) {
            if (visited[i]) {
                traverse('a' + i);
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

TEST_F(TestSolution, Test1)
{
    Solution s;
    auto actual = s.largestVariance("aababbb");
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    Solution s;
    auto actual = s.largestVariance("bba");
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.largestVariance("baaabbbaaaaaab");
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}
