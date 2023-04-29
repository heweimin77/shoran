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
        int unSuitability(vector<int>& operate) {
            vector<array<int, 3>> results = { {0,0,0} };
            for (auto op : operate) {
                vector<array<int, 3>> nexts;
                for (auto& r : results) {
                    int delta[2] = { op, -op };
                    for (auto d : delta) {
                        int bb = -r[1] + d;
                        int cc = r[2] + d;
                        if (bb >= 0) {
                            bb = 0;
                        }
                        else if (cc <= 0) {
                            cc = -bb;
                            bb = 0;
                        }
                        else {
                            bb = -bb;
                            if (bb > cc) {
                                swap(bb, cc);
                            }
                        }
                        int aa = max(bb, cc);
                        aa = max(aa, r[0]);
                        nexts.push_back({ aa, bb, cc });
                    }
                }
                sort(nexts.begin(), nexts.end());
                results.resize(0);
                for (auto &n : nexts) {
                    bool ok = true;
                    for (auto &r : results) {
                        if (n[1] >= r[1] && n[2] >= r[2]) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        results.push_back(n);
                    }
                }
            }

            return results[0][0];
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
        auto actual = s.unSuitability(para);
        decltype(actual) expect = 8;
        EXPECT_EQ(expect, actual);
    }
}



