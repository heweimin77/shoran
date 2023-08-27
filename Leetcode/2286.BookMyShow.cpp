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

class BookMyShow {
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
    BookMyShow(int n, int m) : data(n, m), mm(m), tree(n)
    {
        pos.insert({ 0, -1 });
        pos.insert({ m, 0 });
        pos.insert({ {m + 1, n} });
    }

    vector<int> gather(int k, int maxRow)
    {
        auto it = pos.lower_bound(k);
        if (it == pos.end() || it->second > maxRow) return {};
        int row = it->second;
        vector<int> result = { row, mm - it->first };
        int limit = it->first;
        data[row] -= k;
        tree.update(row + 1, k);

        it = pos.erase(it);
        --it;
        int lastv = it->first;
        for (; lastv < limit && row < data.size(); ++row) {
            if (data[row] > lastv) {
                lastv = data[row];
                pos[lastv] = row;
            }
        }
        return result;
    }

    bool scatter(int k, int maxRow)
    {
        auto it = pos.begin();
        ++it;
        int first = it->second;
        if (first > maxRow) return false;
        //if (accumulate(data.begin() + first, data.begin() + maxRow + 1, 0LL) < k) return false;
        if ((long long) mm * (maxRow + 1) - tree.get_sum(maxRow + 1) < k) return false;

        int row = first;
        for (; data[row] < k; ++row) {
            k -= data[row];
            tree.update(row + 1, data[row]);
            data[row] = 0;
        }
        while (it->second < row) it = pos.erase(it);
        int lastv = 0;
        int limit = 0;
        if (it->second == row) {
            limit = it->first;
            pos.erase(it);
        } else {
            limit = it->first - 1;
        }
        tree.update(row + 1, k);
        data[row] -= k;
        for (; lastv < limit && row < data.size(); ++row) {
            if (data[row] > lastv) {
                lastv = data[row];
                pos[lastv] = row;
            }
        }

        return true;
    }
private:
    vector<int> data;
    map<int, int> pos;
    int mm;

    BinaryIndexedTree tree;
};

class BookMyShow1Timeout93of97 {
public:
    BookMyShow1Timeout93of97(int n, int m) : data(n, m), mm(m)
    {
        pos.insert({ 0, -1 });
        pos.insert({ m, 0 });
        pos.insert({ {m + 1, n} });
    }

    vector<int> gather(int k, int maxRow)
    {
        auto it = pos.lower_bound(k);
        if (it == pos.end() || it->second > maxRow) return {};
        int row = it->second;
        vector<int> result = { row, mm - it->first };
        int limit = it->first;
        data[row] = it->first - k;

        it = pos.erase(it);
        --it;
        int lastv = it->first;
        for (; lastv < limit && row < data.size(); ++row) {
            if (data[row] > lastv) {
                lastv = data[row];
                pos[lastv] = row;
            }
        }
        return result;
    }

    bool scatter(int k, int maxRow)
    {
        auto it = pos.begin();
        ++it;
        int first = it->second;
        if (first > maxRow) return false;
        if (accumulate(data.begin() + first, data.begin() + maxRow + 1, 0LL) < k) return false;
        int row = first;
        for (; data[row] < k; ++row) {
            k -= data[row];
            data[row] = 0;
        }
        while (it->second < row) it = pos.erase(it);
        int lastv = 0;
        int limit = 0;
        if (it->second == row) {
            limit = it->first;
            pos.erase(it);
        } else {
            limit = it->first - 1;
        }
        data[row] -= k;
        for (; lastv < limit && row < data.size(); ++row) {
            if (data[row] > lastv) {
                lastv = data[row];
                pos[lastv] = row;
            }
        }

        return true;
    }
private:
    vector<int> data;
    map<int, int> pos;
    int mm;
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
    BookMyShow show(2, 5);
    EXPECT_EQ_CONTAINER(vector<int>({0, 0}), show.gather(4, 0));
    EXPECT_EQ_CONTAINER(vector<int>({}), show.gather(4, 0));
    EXPECT_EQ(true, show.scatter(5, 1));
    EXPECT_EQ(false, show.scatter(5, 1));
}
TEST_F(TestSolution, Test2)
{
    BookMyShow show(5, 10);
    EXPECT_EQ(true, show.scatter(9, 1));
    EXPECT_EQ(true, show.scatter(1,3));
    EXPECT_EQ_CONTAINER(vector<int>({ 1, 0 }), show.gather(3, 4));
    EXPECT_EQ_CONTAINER(vector<int>({1, 3}), show.gather(1, 1));
    EXPECT_EQ_CONTAINER(vector<int>({2, 0}), show.gather(10, 4));
}
TEST_F(TestSolution, TestMain)
{
    BookMyShow show(1, 1);
    EXPECT_EQ_CONTAINER(vector<int>({ 0, 0 }), show.gather(1, 0));
}

}

