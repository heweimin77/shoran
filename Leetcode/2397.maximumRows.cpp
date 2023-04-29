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
    int maximumRows(vector<vector<int>> &matrix, int numSelect)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<unsigned> flags(m);
        for (int i = 0; i < m; ++i) {
            unsigned flag = 0;
            for (int j = 0; j < n; ++j) {
                flag |= matrix[i][j] << j;
            }
            flags[i] = flag;
        }

        int result = 0;
        for (unsigned f = 1; f < (1 << n); ++f) {
            int cnt = 0;
            for (unsigned ff = f; ff > 0; ff &= (ff - 1)) ++cnt;
            if (cnt != numSelect) continue;
            int r = 0;
            unsigned ff = ~f;
            for (auto flag : flags) {
                if ((ff & flag) == 0) ++r;
            }
            result = max(result, r);
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
    vector<vector<int>> matrix = {{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 0, 1}};
    Solution s;
    auto actual = s.maximumRows(matrix, 2);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}
