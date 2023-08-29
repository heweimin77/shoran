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
    string crackSafe(int n, int k) {
        unordered_set<int> visited;
        string result;
        int mask = (1 << (n - 1) * 4) - 1;

        function<void(int)> dfs = [&](int now) {
            for (int i = 0; i < k; ++i) {
                int eid = (now << 4) + i;
                if (visited.count(eid) == 0) {
                    visited.insert(eid);
                    dfs(eid & mask);
                    result += '0' + i;
                }
            }
        };
        
        dfs(0);
        result += string(n - 1, '0');
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

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.crackSafe(1, 2);
    decltype(actual) expect = "10";
    EXPECT_EQ(expect, actual);
}


}
