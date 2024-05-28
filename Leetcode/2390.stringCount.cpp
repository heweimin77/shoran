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
#include <functional>

#include "support.h"

using namespace std;

namespace {

unordered_set;

class Counts {
    static constexpr int MOD = 1e9 + 7;
    static int flags[12];
    static int indexes[12][12];
public:
    static void Init() {
        for (int li = 0; li < 12; ++li) {
            for (int ri = 0; ri < 12; ++ri) {
                int f = flags[li] + flags[ri];
                int f1 = f & 0x3; if (f1 > 1) f1 = 1;
                int f2 = f & 0xC; if (f2 > 0x4) f2 = 0x4;
                int f3 = f & 0xF0; if (f3 > 0x20) f3 = 0x20;
                f = f1 | f2 | f3;
                for (int xi = max(li, ri); xi < 12; ++xi) {
                    if (f == flags[xi]) {
                        indexes[li][ri] = xi;
                        break;
                    }
                }
            }
        }
    }
    static Counts createCount0() {
        Counts cnts0;
        memset(cnts0.counts, 0, sizeof(cnts0.counts));
        cnts0.counts[0] = 1;
        return cnts0;
    }
    static Counts createCount1() {
        Counts cnts1;
        memset(cnts1.counts, 0, sizeof(cnts1.counts));
        cnts1.counts[0] = 23;
        cnts1.counts[1] = cnts1.counts[2] = cnts1.counts[3] = 1;
        return cnts1;
    }
    static Counts merge(const Counts &lhs, const Counts& rhs) {
        Counts result;
        memset(result.counts, 0, sizeof(result.counts));
        
        for (int li = 0; li < 12; ++li) {
            for (int ri = 0; ri < 12; ++ri) {
                long long x = lhs.counts[li] * rhs.counts[ri] % MOD;
                if (x == 0) continue;
                int xi = indexes[li][ri];
                result.counts[xi] += x;
            }
        }

        for (int i = 0; i < 12; ++i) {
            result.counts[i] %= MOD;
        }

        return result;
    }
    int getResult() const { return counts[11]; }

private:


private:
    long long counts[12];
};

int Counts::flags[12] = {0x0,  0x1, 0x4, 0x10,   0x5, 0x11, 0x14, 0x20,  0x15, 0x21, 0x24,  0x25};
int Counts::indexes[12][12];

class AutoRun {
public:
    AutoRun() {
        Counts::Init();
    }
} _autorun;

class Solution {
public:
    int stringCount(int n) {
        Counts result = Counts::createCount0();
        Counts base = Counts::createCount1();
        int flag = 1;
        for (; flag <= n; flag <<= 1) {
            if (flag & n) {
                result = Counts::merge(result, base);
            }
            base = Counts::merge(base, base);
        }
        return result.getResult();
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
    vector<vector<int>> edges = { {0,1,3}, {1,2,1}, {1,3,4}, {2,3,1} };
    Solution s;
    auto actual = s.stringCount(10);
    decltype(actual) expect = 83943898;
    EXPECT_EQ(expect, actual);
}

}
