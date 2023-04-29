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

using namespace std;

namespace {

    class Solution {
    public:
        int squareFreeSubsets(vector<int>& nums) {
            unordered_map<int, long long> counts;

            int flag[30] = { 0, 1, 2, -1, 4, 3, 8, -1, -1, 5,
                            16, -1, 32, 9, 6, -1, 64, -1, 128, -1,
                            10, 17, 256, -1, -1, 33, -1, -1, 512, 7 };
            int cnts[30] = { 0 };
            for (auto n : nums) {
                ++cnts[n - 1];
            }
            long long result = 1;
            long long base = 2;
            int mask = 1;
            int cnt0 = cnts[0];
            for (int mask = 1; mask <= cnt0; mask <<= 1) {
                if (mask & cnt0) {
                    result *= base;
                    result %= 1000000007;
                }
                base *= base;
                base %= 1000000007;
            }
            counts[0] = result--;
            for (int i = 1; i < 30; ++i) {
                if (cnts[i] == 0) continue;
                int f = flag[i];
                if (f < 0) continue;
                unordered_map<int, long long> nexts = counts;
                for (auto& cnt : counts) {
                    if (cnt.first & f) continue;
                    result += cnt.second * cnts[i];
                    result %= 1000000007;
                    nexts[cnt.first | f] += cnt.second * cnts[i];
                    nexts[cnt.first | f] %= 1000000007;
                }
                counts = std::move(nexts);
            }
            return (int)result;
        }
    };

    class Solution2 {
    public:
        int squareFreeSubsets(vector<int>& nums) {
            unordered_map<int, int> counts;
            counts[0] = 1;
            int result = 0;
            int flag[30] = { 0, 1, 2, -1, 4, 3, 8, -1, -1, 5,
                            16, -1, 32, 9, 6, -1, 64, -1, 128, -1,
                            10, 17, 256, -1, -1, 33, -1, -1, 512, 7 };
            for (auto n : nums) {
                int f = flag[n - 1];
                if (f < 0) continue;
                unordered_map<int, int> nexts = counts;
                for (auto& cnt : counts) {
                    if (cnt.first & f) continue;
                    result += cnt.second;
                    nexts[cnt.first | f] += cnt.second;
                }
                counts = std::move(nexts);
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
        vector<int> para = { 1,1,1,1 };
        Solution s;
        auto actual = s.squareFreeSubsets(para);
        decltype(actual) expect = 15;
        EXPECT_EQ(expect, actual);
    }
}

