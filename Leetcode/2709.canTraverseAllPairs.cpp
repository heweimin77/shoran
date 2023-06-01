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
    bool canTraverseAllPairs(vector<int>& nums) {
        if (nums.size() == 1) return true;
        unordered_map<int, int> indexes;
        vector<unordered_set<int>> groups;
        for (auto n : nums) {
            if (n == 1) return false;
            vector<int> ps = getPrimes(n);
            int index = groups.size();
            for (auto p : ps) {
                auto it = indexes.find(p);
                if (it != indexes.end()) {
                    index = it->second;
                    break;
                }
            }
            if (index == groups.size()) {
                groups.push_back(unordered_set<int>());
                auto &x = groups.back();
                for (auto p : ps) {
                    x.insert(p);
                    indexes[p] = index;
                }
            } else {
                auto& x = groups[index];
                for (auto p : ps) {
                    if (x.count(p)) continue;
                    if (indexes.find(p) == indexes.end()) {
                        x.insert(p);
                        indexes[p] = index;
                    } else {
                        int pindex = indexes[p];
                        for (auto y : groups[pindex]) {
                            x.insert(y);
                            indexes[y] = index;
                        }
                        groups[pindex].clear();
                    }
                }
            }
        }
        
        int cnt = 0;
        for (auto g : groups) {
            if (g.size() > 0) {
                if (++cnt == 2) {
                    return false;
                }
            }
        }
        return true;
    }
    vector<int> getPrimes(int n) {
        vector<int> results;
        int limit = sqrt(n);
        for (int i = 2; i <= limit; ++i) {
            if (n % i == 0) {
                results.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
                limit = sqrt(n);
            }
        }
        if (n > 1) {
            results.push_back(n);
        }
        return results;
    }
};

class Solution2Timeout918 {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> indexes;
        indexes.push_back(0);
        vector<int> nexts;
        for (int i = 1; i < nums.size(); ++i) nexts.push_back(i);
        for (int i = 0; i < indexes.size(); ++i) {
            vector<int> xxx;
            int now = nums[indexes[i]];
            for (int j : nexts) {
                if (gcd(now, nums[j]) > 1) {
                    indexes.push_back(j);
                } else {
                    xxx.push_back(j);
                }
            }
            nexts = std::move(xxx);
        }

        return indexes.size() == n;
    }
    int gcd(int a, int b) {
        if (a > b) swap(a, b);
        while (a > 0) {
            int c = b % a;
            b = a;
            a = c;
        }
        return b;
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
    vector<int> nums = { 2,3,6 };
    Solution s;
    auto actual = s.canTraverseAllPairs(nums);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
}
