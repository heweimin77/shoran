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
    class BinaryIndexedTree {
    public:
        BinaryIndexedTree(int n) : data(n + 1)
        {
        }
        ~BinaryIndexedTree()
        {
        }

        void update(int i, int v)
        {
            for (int n = data.size() - 1; i <= n; i += lowbit(i)) {
                data[i] += v;
            }
        }
        long long get_range(int left, int right)
        {
            return get_sum(right) - get_sum(left - 1);
        }
        long long get_sum(int i)
        {
            long long r = 0;
            for (; i > 0; i -= lowbit(i)) {
                r += data[i];
            }
            return r;
        }
    private:
        inline int lowbit(int i)
        {
            return i & -i;
        }
    private:
        vector<long long> data;
    };
public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        vector<int> indexes(n);
        for (int i = 0; i < n; ++i) indexes[nums2[i]] = i;
        for (auto &d : nums1) d = indexes[d];

        BinaryIndexedTree counts1(n), counts2(n);
        long long result = 0;
        for (auto d : nums1) {
            ++d;
            result += counts2.get_sum(d);
            counts2.update(d, counts1.get_sum(d));
            counts1.update(d, 1);
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
    vector<int> nums1 = { 2,0,1,3 };
    vector<int> nums2 = { 0,1,2,3 };
    Solution s;
    auto actual = s.goodTriplets(nums1, nums2);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}

