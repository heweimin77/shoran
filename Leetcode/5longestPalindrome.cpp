#include <string>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

namespace {

class Solution {
public:
    string longestPalindrome(string s) {
        string result = s.substr(0, 1);
        vector<vector<int>> flag(s.size(), vector<int>(s.size()));
        flag[0][0] = true;
        for (size_t i = 1; i < s.size(); ++i) {
            flag[i][i] = true;
            flag[i - 1][i] = (s[i] == s[i - 1]);
            if (flag[i - 1][i] && result.size() < 2) {
                result = s.substr(i - 1, 2);
            }
        }
        for (size_t d = 2; d < s.size(); ++d) {
            for (size_t i = 0; i + d < s.size(); ++i) {
                auto j = i + d;
                flag[i][j] = flag[i + 1][j - 1] && (s[i] == s[j]);
                if (flag[i][j] && result.size() < j - i + 1) {
                    result = s.substr(i, j - i + 1);
                }
            }
        }
        return result;
    }
};

class Solution2 {
public:
    string longestPalindrome(string s) {
        string result = s.substr(0, 1);
        vector<size_t> indexes;
        for (size_t i = 0; i < s.size(); ++i) {
            vector<size_t> nexts;
            for (auto idx : indexes) {
                if (s[idx - 1] == s[i]) {
                    if (i - idx + 2 > result.size()) {
                        result = s.substr(idx - 1, i - idx + 2);
                    }
                    if (idx >= 2) {
                        nexts.push_back(idx - 1);
                    }
                }
            }
            if (i > 0 && s[i - 1] == s[i]) {
                if (result.size() < 2) {
                    result = s.substr(i - 1, 2);
                }
                if (i >= 2) {
                    nexts.push_back(i - 1);
                }
            }
            if (i >= 1) {
                nexts.push_back(i);
            }
            indexes = std::move(nexts);
        }

        return result;
    }
};

class TestSolution5 :public testing::Test
{
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};


TEST_F(TestSolution5, Test1)
{
    vector<int> para = {1,3 };
    vector<int> para2 = {2};
    //int expect = 4;

    Solution s;
    auto actual = s.longestPalindrome("babad");
    EXPECT_EQ("bab", actual);
}
TEST_F(TestSolution5, Test2)
{
    vector<int> para = { 1,3 };
    vector<int> para2 = { 2 };
    //int expect = 4;

    Solution s;
    auto actual = s.longestPalindrome("cbbd");
    EXPECT_EQ("bb", actual);
}


}


