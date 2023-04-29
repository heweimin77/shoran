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
    string robotWithString(string s)
    {
        int counts[27] = { 0 };
        for (auto c : s) {
            ++counts[c - 'a'];
        }
        counts[26] = 1; // deadline
        int mindex = 0;
        while (counts[mindex] == 0) ++mindex;
        stack<char> ss;
        string result;
        for (auto it = s.begin(); it != s.end(); ++it) {
            while (!ss.empty() && (ss.top() - 'a' <= mindex)) {
                result += ss.top();
                ss.pop();
            }
            ss.push(*it);
            --counts[*it - 'a'];
            while (counts[mindex] == 0) ++mindex;
        }
        while (!ss.empty()) {
            result += ss.top();
            ss.pop();
        }
        return result;
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
    vector<vector<int>> queries = {{0, 1}, {2, 2}, {0, 3}};
    Solution s;
    auto actual = s.robotWithString("zza");
    decltype(actual) expect = "azz";
    EXPECT_EQ(expect, actual);
}

}
