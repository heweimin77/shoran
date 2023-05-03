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
    using Index = pair<long long, int>;
    struct Item {
        int i;
        int left;
        int right;
        long long value;
    };
public:
    long long ringGame(vector<long long> &challenge)
    {
        long long mbase = *max_element(challenge.begin(), challenge.end());
        long long mmask = 1LL << 60;
        while (mmask > mbase) mmask >>= 1;
        int n = challenge.size();
        vector<Item> items(n);
        priority_queue<Index, vector<Index>, greater<Index>> q;
        for (int i = 0; i < n; ++i) {
            items[i] = { i, i, i, 0};
            q.push({ challenge[i], i});
        }
        long long base = 0;
        while (!q.empty()) {
            Index now = q.top();
            q.pop();
            base = now.first;
            if (base >= mbase) return mbase;
            int i = now.second;
            auto &item = items[i];
            if (item.i != i) continue;
            while (true) {
                auto value = base | item.value;
                if (item.left == item.right && item.left == i) {
                    item.value |= challenge[i];
                    --item.left;
                    if (item.left < 0) item.left += n;
                    ++item.right;
                    if (item.right >= n) item.right -= n;
                } else if (item.left == item.right && value >= challenge[item.left]) {
                    return base;
                } else if (value >= challenge[item.left]) {
                    item.value |= challenge[item.left];
                    auto &litem = items[items[item.left].i];
                    item.value |= litem.value;
                    litem.i = i;
                    if (litem.left == item.left) {
                        items[item.left].i = i;
                        --item.left;
                        if (item.left < 0) item.left += n;
                    } else {
                        item.left = litem.left;
                        items[(item.left + 1) % n].i = i;
                    }
                    if (items[item.left].i == i) return base;
                } else if (value >= challenge[item.right]) {
                    item.value |= challenge[item.right];
                    auto &ritem = items[items[item.right].i];
                    item.value |= ritem.value;
                    ritem.i = i;
                    if (ritem.right == item.right) {
                        items[item.right].i = i;
                        ++item.right;
                        if (item.right >= n) item.right -= n;
                    } else {
                        item.right = ritem.right;
                        items[(item.right + n - 1) % n].i = i;
                    }
                    if (items[item.right].i == i) return base;
                } else {
                    long long nb1 = get_base(item.value, challenge[item.left], mmask);
                    long long nb2 = get_base(item.value, challenge[item.right], mmask);
                    q.push({ min(nb1, nb2), i });
                    break;
                }
            }
        }
        return base;
    }
    long long get_base(long long b, long long n, long long mmask)
    {
        long long r = 0;
        // r >= b && (r | b ) >= n
        for (;  mmask > 0; mmask >>= 1) {
            if ((mmask & b) == 0 && (mmask & n) == 0) continue;
            if (r < b && (mmask & b)) r |= mmask;
            if ((r | b) < n && (mmask & n) && (mmask & b) == 0) r |= mmask;
            if ((r | b) >= n && r >= b) break;
        }
        return r;
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
    vector<long long> challenge = { 5,4,6,2,7 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<long long> challenge = { 1,17,1,19,1 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 18;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<long long> challenge = { 1, 180, 447 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 266;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<long long> challenge = { 1,4,37,39,5,37,2,37,39 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 32;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test5)
{
    vector<long long> challenge = { 16,12,14,9,17,17,12,4 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 16;
    EXPECT_EQ(expect, actual);
}
}
