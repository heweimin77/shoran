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
    static constexpr int MAX_POSITION = 100;
    static constexpr int MAX_TIME = 5;
    static constexpr int MAX_STATE = 1 << MAX_TIME;
    using States = array<int, MAX_STATE>;
public:
    int defendSpaceCity(vector<int> &time, vector<int> &position)
    {
        unsigned state[MAX_POSITION + 1] = { 0 };
        for (int i = 0; i < time.size(); ++i) {
            state[position[i]] |= 1 << (time[i] - 1);
        }
        
        States costs2 = get_costs(2);
        States costs3 = get_costs(3);
        States nows = costs3;
        for (int i = 0; i <= MAX_POSITION; ++i) {
            auto s = state[i];
            States nexts;
            for (unsigned nextstate = 0; nextstate < MAX_STATE; ++nextstate) {
                int r = INT_MAX;
                for (int nowstate = 0; nowstate < MAX_STATE; ++nowstate) {
                    if (nextstate & nowstate) continue;
                    unsigned flag = nextstate | nowstate;
                    flag = ~flag & s;
                    r = min(r, nows[nowstate] + costs3[nextstate] + costs2[flag]);
                }
                nexts[nextstate] = r;
            }
            nows = std::move(nexts);
            //cout << s << endl;
            //for (int nowstate = 0; nowstate < MAX_STATE; ++nowstate) {
            //    cout << nows[nowstate] << " ";
            //}
            //cout << endl;
        }
        return nows[0];
    }
    array<int, 1 << MAX_TIME> get_costs(int cost)
    {
        array<int, MAX_STATE> costs;
        for (unsigned state = 0; state < MAX_STATE; ++state) {
            int r = (state & 1) ? cost : 0;
            for (unsigned mask = 2; mask < MAX_STATE; mask <<= 1) {
                if ((mask & state) == 0) continue;
                r += ((mask >> 1) & state) ? 1 : cost;
            }
            costs[state] = r;
        }
        return costs;
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
    vector<int> time = { 1,2,1 };
    vector<int> position = { 3,0,0 };
    Solution s;
    auto actual = s.defendSpaceCity(time, position);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}

}
