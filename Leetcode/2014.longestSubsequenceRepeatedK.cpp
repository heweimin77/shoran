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
    string longestSubsequenceRepeatedK(string s, int k) {
        int counts[26] = { 0 };
        for (auto ch : s) {
            ++counts[ch - 'a'];
        }
       
        vector<pair<char, int>> charcounts;
        int totalcnt = 0;
        for (int i = 25; i >= 0; --i) {
            int cnt = counts[i] / k;
            if (cnt > 0) {
                charcounts.push_back({ 'a' + i, cnt });
                totalcnt += cnt;
            }
        }
        vector<vector<string>> results(totalcnt, vector<string>());

        function<void(int, const string&)> traverse = [&](int now, const string &s) {
            if (now == totalcnt) return;
            for (auto& item : charcounts) {
                if (item.second > 0) {
                    --item.second;
                    results[now].push_back(s + item.first);
                    traverse(now + 1, s + item.first);
                    ++item.second;
                }
            }
        };
        traverse(0, "");

        function<bool(const string&)> ok = [&](const string& r) {
            int count = k;
            int j = 0;
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] == r[j]) {
                    if (++j == r.size()) {
                        if (--count == 0) break;
                        j = 0;
                    }
                }
            }

            return count == 0;
        };
        
        for (auto it = results.rbegin(); it != results.rend(); ++it) {
            for (auto& r : *it) {
                if (ok(r)) {
                    return r;
                }
            }
        }

        return "";
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
    vector<int> sums = { -3,-2,-1,0,0,1,2,3 };
    Solution s;
    auto actual = s.longestSubsequenceRepeatedK("letsleetcode", 2);
    decltype(actual) expect = "let";
    EXPECT_EQ(expect, actual);
}
}
