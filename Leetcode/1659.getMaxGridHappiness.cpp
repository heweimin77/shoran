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
#define MAKE_STATE(ic, ec, s) (((ic) << 16) | ((ec) << 8) |(s))
#define GET_IC(state) ((state) >> 16)
#define GET_EC(state) (((state) >> 8) & 0xFF)
#define GET_S(state)  ((state) & 0xFF)
    struct Info {
        vector<int> x;
        int icount;
        int ecount;
        int value;
        Info(vector<int> &xx)
        {
            icount = ecount = value = 0;
            x = std::move(xx);
            for (auto v : x) {
                if (v == 1) {
                    ++icount;
                    value += 120;
                } else if (v == 2) {
                    ++ecount;
                    value += 40;
                }
            }
            for (int i = 1; i < x.size(); ++i) {
                auto s1 = x[i - 1], s2 = x[i];
                if (s1 == 0 || s2 == 0) continue;
                value += s1 == 1 ? -30 : 20;
                value += s2 == 1 ? -30 : 20;
            }
        }
    };
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount)
    {
        vector<Info> infos;
        for (int i = 0; true; ++i) {
            vector<int> x;
            for (auto xx = i; xx > 0; xx /= 3) {
                x.push_back(xx % 3);
            }
            if (x.size() > n) break;
            x.resize(n);
            infos.push_back(Info(x));
        }

        unordered_map<int, int> results;
        results[MAKE_STATE(introvertsCount, extrovertsCount, 0)] = 0;
        for (int i = 0; i < m; ++i) {
            unordered_map<int, int> nexts;
            for (auto &r : results) {
                int s = GET_S(r.first);
                int ic = GET_IC(r.first);
                int ec = GET_EC(r.first);
                for (int ns = 0; ns < infos.size(); ++ns) {
                    auto &info = infos[ns];
                    if (info.icount > ic || info.ecount > ec) continue;
                    int nic = ic - info.icount;
                    int nec = ec - info.ecount;
                    int value = r.second + info.value;
                    for (int i = 0; i < n; ++i) {
                        auto s1 = info.x[i], s2 = infos[s].x[i];
                        if (s1 == 0 || s2 == 0) continue;
                        value += s1 == 1 ? -30 : 20;
                        value += s2 == 1 ? -30 : 20;
                    }
                    int nstate = MAKE_STATE(nic, nec, ns);
                    nexts[nstate] = max(nexts[nstate], value);
                }
            }
            results = std::move(nexts);
        }

        int result = 0;
        for (auto &r : results) {
            result = max(result, r.second);
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
    Solution s;
    auto actual = s.getMaxGridHappiness(2, 3, 1, 2);
    decltype(actual) expect = 240;
    EXPECT_EQ(expect, actual);
}
}
