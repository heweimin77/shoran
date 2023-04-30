#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

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
    long long countOperationsToEmptyArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> indexes(n);
        for (int i = 0; i < n; ++i) indexes[i] = i;
        sort(indexes.begin(), indexes.end(), [&nums](int lhs, int rhs) {
            return nums[lhs] < nums[rhs];
        });

        BinaryIndexedTree btree(n + 1);
        long long result = 0;
        int last = -1;
        for (int i = 0; i < n; ++i) {
            int now = indexes[i];
            if (now >= last) {
                result += now - last;
                result -= btree.get_sum(now + 1) - btree.get_sum(last + 1);
            } else {
                result += now + n - last;
                result -= btree.get_sum(n) - btree.get_sum(last + 1) + btree.get_sum(now + 1);
            }
            btree.update(now + 1, 1);
            last = now;
        }

        return result;
    }
};

class TestSolution :public testing::Test {
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
    vector<int> nums = {3,4,-1};
    Solution s;
    auto actual = s.countOperationsToEmptyArray(nums);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}

}
