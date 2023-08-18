#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<string> splitMessage(string message, int limit) {
        constexpr int base = 5;
        int nums[] = { 9, 90, 900, 9000 };
        int count = 0;
        int messagecount = 0;
        int mbase = base;
        int v = 0;
        for (auto n : nums) {
            messagecount -= count;

            if (messagecount + n * (limit - mbase) >= message.size()) {
                v = count + (message.size() - messagecount + limit - mbase - 1) / (limit - mbase);
                break;
            }
            messagecount += n * (limit - mbase);
            count += n;
            mbase += 2;
            if (mbase >= limit) {
                return {};
            }
        }
        string surfix1 = "<";
        string surfix2 = "/" + to_string(v) + ">";
        vector<string> results;
        auto it = message.begin();
        int mcnt = 0;
        int now = 1;
        int payload = limit - surfix1.size() - surfix2.size() - 1;
        for (auto n : nums) {
            mcnt += n;
            for (; now <= mcnt; ++now) {
                if (message.end() - it > payload) {
                    results.push_back(string(it, it + payload) + surfix1 + to_string(now) + surfix2);
                    it += payload;
                } else {
                    results.push_back(string(it, message.end()) + surfix1 + to_string(now) + surfix2);
                    return results;
                }
            }
            --payload;
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

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.splitMessage("this is really a very awesome message", 9);
    decltype(actual) expect = { "thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>" };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}

