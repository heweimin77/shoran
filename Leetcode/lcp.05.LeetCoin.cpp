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
    static constexpr int MOD = 1e9 + 7;
    // 序号从1开始，不是从0开始
    // 单点修改，获取区域
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

    // 区域修改，获取单点。。。使用差分
    class BinaryIndexedTree2 {
    public:
        BinaryIndexedTree2(int n) : diff(n + 1)
        {
        }
        ~BinaryIndexedTree2()
        {
        }

        void update(int left, int right, int v)
        {
            diff.update(left, v);
            diff.update(right + 1, -v);
        }

        int get_value(int i)
        {
            return diff.get_sum(i);
        }
    private:
        BinaryIndexedTree diff;
    };

    // 区域修改，获取区域。。。使用差分, sum(i) = (i + 1) * sum(diff) - sum (i * diff)
    class BinaryIndexedTree3 {
    public:
        BinaryIndexedTree3(int n) : diff(n + 1), idiff(n + 1)
        {
        }
        ~BinaryIndexedTree3()
        {
        }

        void update(int left, int right, int v)
        {
            diff.update(left, v);
            idiff.update(left, left * v);

            ++right;
            diff.update(right, -v);
            idiff.update(right, -right * v);
        }

        long long get_sum(int i)
        {
            long long r = (i + 1) * diff.get_sum(i);
            r -= idiff.get_sum(i);
            return r % MOD;
        }
        long long get_range(int left, int right)
        {
            return get_sum(right) - get_sum(left - 1);
        }

    private:
        inline int lowbit(int i)
        {
            return i & -i;
        }
    private:
        BinaryIndexedTree diff;
        BinaryIndexedTree idiff;
    };

public:
    vector<int> bonus(int n, vector<vector<int>> &leadership, vector<vector<int>> &operations)
    {
        ++n;
        vector<vector<int>> children(n);
        for (auto &lead : leadership) {
            children[lead[0]].push_back(lead[1]);
        }
        vector<pair<int, int>> range(n);
        int index = 1;
        dfs(children, 1, range, index);

        BinaryIndexedTree3 segtree(n);
        vector<int> results;
        for (auto &op : operations) {
            if (op[0] == 1) {
                segtree.update(range[op[1]].first, range[op[1]].first, op[2]);
            } else if (op[0] == 2) {
                segtree.update(range[op[1]].first, range[op[1]].second - 1, op[2]);
            } else {
                results.push_back(segtree.get_range(range[op[1]].first, range[op[1]].second - 1));
            }
        }
        return results;
    }
    void dfs(const vector<vector<int>> &children, int now, vector<pair<int, int>> &range, int &index)
    {
        range[now].first = index++;
        for (auto child : children[now]) {
            dfs(children, child, range, index);
        }
        range[now].second = index;
    }
};


class Solution2Timeout {
    static constexpr int MOD = 1e9 + 7;
public:
    vector<int> bonus(int n, vector<vector<int>> &leadership, vector<vector<int>> &operations)
    {
        vector<int> parents(n + 1);
        vector<vector<int>> children(n + 1);
        for (auto &lead : leadership) {
            parents[lead[1]] = lead[0];
            children[lead[0]].push_back(lead[1]);
        }
        vector <int> b1(n + 1);
        vector <int> b2(n + 1);
        vector<int> results;
        for (auto &op : operations) {
            if (op[0] == 1) {
                b1[op[1]] += op[2];
            } else if (op[0] == 2) {
                b2[op[1]] += op[2];
            } else {
                int n = op[1];
                long long count = 0;
                long long  r = getResults(children, b1, b2, n, count);
                int b = 0;
                for (auto p = parents[n]; p != 0; p = parents[p]) {
                    b += b2[p];
                }
                r += b * count;
                results.push_back(r % MOD);
            }
        }

        return results;
    }
    long long  getResults(vector<vector<int>> &children, vector <int> &b1, vector <int> &b2, int n, long long &count)
    {
        long long r = 0;
        long long cnt = 1;
        for (auto child : children[n]) {
            long long c = 0;
            r += getResults(children, b1, b2, child, c);
            cnt += c;
        }
        r += b1[n];
        r += b2[n] * cnt;
        count = cnt;
        return r % MOD;
    }
};

class Solution3SegmentTree {
    static constexpr int MOD = 1e9 + 7;
#if 1
#define GETMOD(x)  ((x) % MOD)
#define MAKEMOD(x)  (x %= MOD)
#else
#define GETMOD(x) x
#define MAKEMOD(x)
#endif 

    class SegmentTree {
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
        //vector<Info> data;
        int n;
    };

public:
    vector<int> bonus(int n, vector<vector<int>> &leadership, vector<vector<int>> &operations)
    {
        ++n;
        vector<vector<int>> children(n);
        for (auto &lead : leadership) {
            children[lead[0]].push_back(lead[1]);
        }
        vector<pair<int, int>> range(n);
        int index = 0;
        dfs(children, 1, range, index);

        SegmentTree segtree(n);
        vector<int> results;
        for (auto &op : operations) {
            if (op[0] == 1) {
                segtree.update(range[op[1]].first, range[op[1]].first, op[2]);
            } else if (op[0] == 2) {
                segtree.update(range[op[1]].first, range[op[1]].second - 1, op[2]);
            } else {
                results.push_back(segtree.get(range[op[1]].first, range[op[1]].second - 1));
            }
        }
        return results;
    }
    void dfs(const vector<vector<int>> &children, int now, vector<pair<int, int>> &range, int &index)
    {
        range[now].first = index++;
        for (auto child : children[now]) {
            dfs(children, child, range, index);
        }
        range[now].second = index;
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
    vector<vector<int>> leadership = {{1, 2}, {1, 6}, {2, 3}, {2, 5}, {1, 4}};
    vector<vector<int>> operations = {{1, 1, 500}, {2, 2, 50}, {3, 1}, {2, 6, 15}, {3, 1}};
    Solution s;
    auto actual = s.bonus(6, leadership, operations);
    decltype(actual) expect = { 650, 665 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
