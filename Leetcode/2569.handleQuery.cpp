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

// 线段树
class SegmentTree {
    static constexpr int MOD = 1e9 + 7;
#if 1
#define GETMOD(x)  ((x) % MOD)
#define MAKEMOD(x)  (x %= MOD)
#else
#define GETMOD(x) x
#define MAKEMOD(x)
#endif 

    struct Info {
        int value = 0;
        int todo = 0;
    };
public:
    SegmentTree(int nn)
    {
        for (n = 1; n < nn; n <<= 1);
        data = (Info *)malloc(sizeof(Info) * n * 2);
        memset(data, 0, sizeof(Info) * n * 2);
    }
    ~SegmentTree()
    {
        free(data);
    }

    void update(int i, int v)
    {
        update(i, i, v);
    }
    void update(int left, int right, int v)
    {
        update(left, right, v, 0, 0, n - 1);
    }
    // ll <= left <= right <= rr
    void update(int left, int right, int v, int index, int ll, int rr)
    {
        Info *info = &data[index];
        if (ll == left && right == rr) {
            info->todo += v;
            MAKEMOD(info->todo);
            return;
        }
        info->value += v * (right - left + 1);
        MAKEMOD(info->value);
        int mid = (ll + rr) >> 1;
        if (right <= mid) {
            update(left, right, v, (index << 1) + 1, ll, mid);
        } else if (left > mid) {
            update(left, right, v, (index << 1) + 2, mid + 1, rr);
        } else {
            update(left, mid, v, (index << 1) + 1, ll, mid);
            update(mid + 1, right, v, (index << 1) + 2, mid + 1, rr);
        }

    }
    int get(int left, int right)
    {
        return GETMOD(get(left, right, 0, 0, n - 1));
    }
    // ll <= left <= right <= rr
    long long get(int left, int right, int index, int ll, int rr)
    {
        Info *info = &data[index];
        if (ll == rr) {
            return info->todo + info->value;
        }
        int lindex = (index << 1) + 1;
        int rindex = (index << 1) + 2;
        // Process todo
        if (info->todo) {
            data[lindex].todo += info->todo;
            data[rindex].todo += info->todo;
            info->value += GETMOD((long long)info->todo * (rr - ll + 1));
            MAKEMOD(info->value);
            info->todo = 0;
        }

        if (ll == left && right == rr) {
            return info->value;
        }
        long long  result = 0;
        int mid = (ll + rr) >> 1;
        if (right <= mid) {
            result += get(left, right, lindex, ll, mid);
        } else if (left > mid) {
            result += get(left, right, rindex, mid + 1, rr);
        } else {
            result += get(left, mid, lindex, ll, mid);
            result += get(mid + 1, right, rindex, mid + 1, rr);
        }
        return result;
    }

private:
    Info *data;
    int n;
};

class Solution {
public:
    vector<long long> handleQuery(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries)
    {
        long long result = accumulate(nums2.begin(), nums2.end(), 0LL);
        vector<long long> results;
        long long cnt1 = accumulate(nums1.begin(), nums1.end(), 0LL);
        for (auto &q : queries) {
            if (q[0] == 1) {
                for (int i = q[1]; i <= q[2]; ++i) {
                    nums1[i] = 1 - nums1[1];
                    cnt1 += nums1[i] == 1 ? 1 : -1;
                }
            } else if (q[0] == 2) {
                result += cnt1 * q[1];
            } else {
                results.push_back(result);
            }
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
    vector<int> nums1 = { 1,0,1 };
    vector<int> nums2 = { 0,0,0 };
    vector<vector<int>> queries = { {1, 1, 1}, {2, 1, 0}, {3, 0, 0} };
    Solution s;
    auto actual = s.handleQuery(nums1, nums2, queries);
    decltype(actual) expect = {3};
    EXPECT_EQ_CONTAINER(expect, actual);
}
}
