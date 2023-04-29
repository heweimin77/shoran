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

// https://leetcode.cn/problems/s5kipK/

namespace {

    class Solution {
    public:
        long long minimumCost(vector<int>& cost, vector<vector<int>>& roads) {
            int n = cost.size();
            vector<vector<int>> adjs(n);
            for (auto& r : roads) {
                adjs[r[0]].push_back(r[1]);
                adjs[r[1]].push_back(r[0]);
            }

            vector<int> state(n); // >= 0 : center，子leaf个数; -1: leaf, -2: middle of leaf and center
            vector<pair<int,int>> leafs; // leaf and parent in center
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                if (adjs[i].size() == 1) { // leaf
                    state[i] = -1;
                    leafs.push_back({ i, INT_MAX });
                    sum += cost[i];
                }
            }
            if (leafs.size() == 0) {
                return *min_element(cost.begin(), cost.end());
            }
            for (auto &leaf : leafs) {
                auto n = adjs[leaf.first][0];
                auto last = leaf.first;
                while (adjs[n].size() == 2) {
                    state[n] = -2;
                    if (last == adjs[n][0]) {
                        last = n;
                        n = adjs[n][1];
                    } else {
                        last = n;
                        n = adjs[n][1];
                    }
                }
                if (adjs[n].size() == 1) {
                    return min(cost[leaf.first], cost[n]); // 直线，2个leaf结点
                }
                ++state[n];
                leaf.second = n;
            }
            // 计算center个数，最小值与次小值
            int cnum = 0;
            int cmin = INT_MAX, cmin2 = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (state[i] >= 0) {
                    ++cnum;
                    auto cnow = cost[i];
                    if (cnow >= cmin2) {
                        //do nothing
                    } else if (cnow >= cmin) {
                        cmin2 = cnow;
                    } else {
                        cmin2 = cmin;
                        cmin = cnow;
                    }
                }
            }

            long long result = sum;
            for (auto leaf : leafs) {
                long long r = sum - cost[leaf.first];
                if (leafs.size() == state[leaf.second]) {
                    if (cost[leaf.second] == cmin) {
                        r += cmin2;
                    } else {
                        r += cmin;
                    }
                }
                result = min(result, r);
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
        vector<int> cost = { 1,2,3,4,5,6 };
        vector<vector<int>> roads = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {1, 2}, {2, 4}, {2, 5}};
        Solution s;
        auto actual = s.minimumCost(cost, roads);
        decltype(actual) expect = 6;
        EXPECT_EQ(expect, actual);
    }
}
