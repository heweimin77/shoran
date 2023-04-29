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
        vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
            vector<bool> results;
            vector<bool> flags(nums.size());
            for (int i = 0; i < l.size(); ++i) {
                int ll = l[i], rr = r[i] + 1;
                int mind = *std::min_element(nums.begin() + ll, nums.begin() + rr);
                int maxd = *std::max_element(nums.begin() + ll, nums.begin() + rr);
                if (mind == maxd) {
                    results.push_back(true);
                    continue;
                }
                if ((maxd - mind) % (rr - ll - 1) != 0) {
                    results.push_back(false);
                    continue;
                }
                int d = (maxd - mind) / (rr - ll - 1);
                fill(flags.begin(), flags.begin() + rr - ll, false);
                bool r = true;
                for (int i = ll; i < rr; ++i) {
                    if ((nums[i] - mind) % d != 0) {
                        r = false;
                        break;
                    }
                    int index = (nums[i] - mind) / d;
                    if (flags[index]) {
                        r = false;
                        break;
                    }
                    flags[index] = true;
                }
                results.push_back(r);
            }
            return results;
        }
    };

    class Solution1 {
    public:
        vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
            vector<bool> results;
            for (int i = 0; i < l.size(); ++i) {
                vector<int> ns(nums.begin() + l[i], nums.begin() + r[i] + 1);
                sort(ns.begin(), ns.end());
                int d = ns[1] - ns[0];
                bool r = true;
                for (int j = 2; j < ns.size(); ++j) {
                    if (ns[j] - ns[j - 1] != d) {
                        r = false;
                        break;
                    }
                }
                results.push_back(r);
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
        vector<int> para = { 4,6,5,9,3,7 };
        vector<int> ipara = { 0,0,2 };
        vector<int> ipara2 = { 2,3,5 };
        Solution s;
        auto actual = s.checkArithmeticSubarrays(para, ipara, ipara2);
        decltype(actual) expect = { true,false,true };
        EXPECT_EQ_CONTAINER(expect, actual);
    }
}



