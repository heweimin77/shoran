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
    public:
        int numDupDigitsAtMostN(int n) {
            if (n <= 10) return 0;
            int cnt = 0;
            char data[12];
            int nn = n;
            while (nn > 0) {
                data[cnt++] = nn % 10;
                nn /= 10;
            }
            int sum[10] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };
            int rsum[10] = { 0, 9, 90, 738, 5274, 32490, 168570, 712890, 2345850, 5611770};

            int r = rsum[cnt - 1];
            char* p = &data[cnt - 1];
            if (*p > 1) {
                r += (*p - 1) * sum[9] / sum[10 - cnt];
            }
            unsigned flag = 1 << *p;
            int nrest = 8;
            --cnt, --cnt;
            for (--p; p >= &data[0]; --p, --cnt, --nrest) {
                int x = 0;
                for (int i = 0; i < *p; ++i) {
                    if (flag & (1 << i)) continue;
                    ++x;
                }
                if (x > 0) {
                    r += x * sum[nrest] / sum[nrest - cnt];
                }
                
                if (flag & (1 << *p)) break;
                flag |= (1 << *p);
            }
            if (p < &data[0]) ++r;
            return n - r;

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
        vector<int> para = { 5,3,7 };
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        auto actual = s.numDupDigitsAtMostN(543);
        decltype(actual) expect = 129;
        EXPECT_EQ(expect, actual);
    }
}



