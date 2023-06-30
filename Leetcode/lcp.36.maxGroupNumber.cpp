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

class Solution{
public:
    int maxGroupNumber(vector<int>&tiles) {
        map<int, int> counts;
        for (auto t : tiles) {
            ++counts[t];
        }

        int rs1[5][5][5];
        int rs2[5][5][5];
        memset(rs1, -1, sizeof(rs1));
        memset(rs2, -1, sizeof(rs2));
        int(*results)[5][5] = rs1;
        int(*nows)[5][5] = rs2;
        results[0][0][0] = 0;

        int p = INT_MIN;
        for (auto& cnt : counts) {
            memset(nows, -1, sizeof(rs1));
            if (cnt.first > p + 1) {
                int r = results[0][0][0];
                for (int i = 0; i < 5 && i <= cnt.second; ++i) {
                    nows[i][0][0] = (cnt.second - i) / 3 + r;
                }
            } else {
                for (int i = 0; i < 5 && i <= cnt.second; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        if (results[j][0][0] < 0) break;
                        for (int k = 0; k < 5; ++k) {
                            if (results[j][k][0] < 0) break;
                            int r = results[j][k][0] + (cnt.second - i) / 3;
                            for (int x = 1; x < 5 && (i + x) <= cnt.second; ++x) {
                                if (j + x >= 5 || k + x >= 5 || results[j + x][k + x][0] < 0) break;
                                r = max(r, x + results[j + x][k + x][0] + (cnt.second - i - x) / 3);
                            }
                            nows[i][j][k] = r;

                        }
                    }
                }
            }
            swap(results, nows);
            p = cnt.first;
        }
        return results[0][0][0];
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
    vector<int> tiles = { 2,2,2,3,4 };
    Solution s;
    auto actual = s.maxGroupNumber(tiles);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> tiles = { 1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,4,4,5,5,6 };
    Solution s;
    auto actual = s.maxGroupNumber(tiles);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}
