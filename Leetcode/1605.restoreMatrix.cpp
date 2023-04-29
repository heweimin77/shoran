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

using namespace std;

namespace {

    class Solution {
    public:
        vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
            int n = rowSum.size(), m = colSum.size();
            int i = 0, j = 0;
            vector<vector<int>> results(n, vector<int>(m));
            while (i < n && j < m) {
                if (rowSum[i] < colSum[j]) {
                    colSum[j] -= rowSum[i];
                    results[i][j] = rowSum[i];
                    ++i;
                }
                else if (rowSum[i] > colSum[j]) {
                    rowSum[i] -= colSum[j];
                    results[i][j] = colSum[j];
                    ++j;
                }
                else {
                    results[i][j] = colSum[j];
                    ++i, ++j;
                }
            }

            return results;
        }
    };

    class Solution3 {
    public:
        vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
            int n = rowSum.size(), m = colSum.size();
            int j = 0;
            vector<vector<int>> results(n, vector<int>(m, 0));
            for (int i = 0; i < n; ++i) {
                int rsum = rowSum[i];
                for (; colSum[j] < rsum; ++j) {
                    rsum -= colSum[j];
                    results[i][j] = colSum[j];
                }
                results[i][j] = rsum;
                colSum[j] -= rsum;
            }

            return results;
        }
    };

    class Solution2 {
    public:
        vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
            int n = rowSum.size(), m = colSum.size();
            int fj = 0;
            vector<vector<int>> results(n, vector<int>(m, 0));
            for (int i = 0; i < n; ++i) {
                int rsum = rowSum[i];
                for (int j = fj; j < m; ++j) {
                    if (rsum <= colSum[j]) {
                        results[i][j] = rsum;
                        colSum[j] -= rsum;
                        fj = j;
                        break;
                    }
                    else {
                        rsum -= colSum[j];
                        results[i][j] = colSum[j];
                        colSum[j] = 0;
                    }
                }
            }

            return results;
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
        vector<int> para = { 3, 8 };
        vector<int> para2 = { 4, 7 };
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        auto actual = s.restoreMatrix(para, para2);
        decltype(actual) expect = { {3, 0}, {1, 7} };
        EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
    }
}