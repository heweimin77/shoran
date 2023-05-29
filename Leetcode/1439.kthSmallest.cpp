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

#include "support.h"

using namespace std;

namespace {

class Solution {
    using Info = pair<int, string>;
public:
    int kthSmallest(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        priority_queue<Info, vector<Info>, greater<Info>> q;
        int v = 0;
        string s(m, '0');
        for (int i = 0; i < mat.size(); ++i) {
            v += mat[i][0];
        }
        cout << s << endl;
        unordered_set<string> visited;
        visited.insert(s);
        q.push({ v, s });
        int result = 0;
        for (int j = 0; j < k; ++j) {
            auto &now = q.top();
            result = now.first;
            string s = now.second;
            for (int i = 0; i < m; ++i) {
                if (s[i] + 1 - '0' < n) {
                    ++s[i];
                    if (visited.count(s)) {
                        --s[i];
                        continue;
                    }
                    visited.insert(s);
                    q.push({ result + mat[i][s[i] - '0'] - mat[i][s[i] - 1 - '0'], s });
                    --s[i];
                }
            }
            q.pop();
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

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> mat = { {2, 7, 8, 10}, {1, 8, 8, 9}, {5, 6, 10, 10}, {4, 5, 5, 8}, {1, 3, 4, 8} };
    Solution s;
    auto actual = s.kthSmallest(mat, 15);
    decltype(actual) expect = 17;
    EXPECT_EQ(expect, actual);
}

}
