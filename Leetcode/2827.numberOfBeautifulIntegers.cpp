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
    int numberOfBeautifulIntegers(int low, int high, int k) {
        makeprepare(k);
        if (low < 10) return getNum(high, k);
        return getNum(high, k) - getNum(low - 1, k);
    }
    int getNum(int d, int k) {
        string s = to_string(d);
        int n = s.size();
        int r = 0;
        if (n <= 1) return 0;

        function<void(int, int )> traverse1 = [&](int base, int ocnt)->void {
            int start = (base % k == 0) ? base : base + k - base % k;
            int limit = min(base * 10, d + 1);
            for (; start < limit; start += k) {
                if (odds[start] == ocnt) ++r;
            }
        };

        function<void(int, int, array<vector<vector<int>>, 5>&)> traverse2 = [&](int base, int ocnt, array<vector<vector<int>>, 5> &groups)->void {
            int left = d / base;
            int leftvalue = d / base * base;
            int limit = min(base, left);

            for (int i = base / 10; i < limit; ++i) {
                int x = (base * base * k - i * base) % k;
                r += groups[ocnt - odds[i]][x].size();
            }

            if (left >= base) return;

            int start = leftvalue % k == 0 ? leftvalue : leftvalue + k - leftvalue % k;
            for (; start < d; start += k) {
                if (odds[left] + odds[start - leftvalue] == ocnt) ++r;
            }
        };


        // 计算2位数
        traverse1(10, 1);
        if (n <= 3) return r;
        
        // 计算4位数
        traverse1(1000, 2);
        if (n <= 5) return r;

        // 计算6位数
        traverse2(1000, 3, groups3);
        if (n <= 7) return r;

        // 计算8位数
        traverse2(10000, 4, groups4);
        return r;
    }

    void makeprepare(int k) {
        for (auto& g : groups4) g.resize(k);
        for (auto& g : groups3) g.resize(k);
        odds.resize(10000);
        for (int i = 0; i < 10000; ++i) {
            int ocnt = 0;
            int d = i;
            while (d > 0) {
                if (d & 1) ++ocnt;
                d /= 10;
            }
            odds[i] = ocnt;
            groups4[ocnt][i % k].push_back(i);
            if (i < 1000) {
                groups3[ocnt][i % k].push_back(i);
            }
        }
    }
    

private:
    vector<int> odds;
    array<vector<vector<int>>, 5> groups3;
    array<vector<vector<int>>, 5> groups4;
};

class Solution1Time574of596 {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        makeFlags();
        if (low < 10) return getNum(high, k);
        return getNum(high, k) - getNum(low - 1, k);
    }
    int getNum(int d, int k) {
        int r = 0;
        int data[2][5] = { {0, 2, 4, 6, 8}, {1, 3, 5, 7, 9} };
        function<void(int, int, int, int)> xxxx = [&](int f, int n, int i, int v) {
            if (v > d) return;
            if (i == n) {
                if (v % k == 0) ++r;
                return;
            }
            for (auto x : data[(f & (1 << i)) ? 1 : 0]) {
                if (i == 0 && x == 0) continue;
                xxxx(f, n, i + 1, v * 10 + x);
            }
        };

        function<bool(vector<int>&, int n)> traverse = [&](vector<int>& flags, int n)->bool {
            for (auto f : flags) {
                xxxx(f, n, 0, 0);
            }
            return pow(10, n) <= d;
        };
        if (!traverse(flags2, 2)) return r;
        if (!traverse(flags4, 4)) return r;
        if (!traverse(flags6, 6)) return r;
        if (!traverse(flags8, 8)) return r;
        return r;
    }
    void makeFlags() {
        function<void(int, vector<int>&)> make = [](int n, vector<int>& flags) {
            int x = 1 << n;
            int count = n / 2;
            for (int i = 1; i < x; ++i) {
                int r = 0;
                int d = i;
                while (d > 0) {
                    ++r;
                    d &= (d - 1);
                }
                if (r == count) {
                    flags.push_back(i);
                }
            }
        };
        make(2, flags2);
        make(4, flags4);
        make(6, flags6);
        make(8, flags8);
    }


private:
    vector<int> flags2;
    vector<int> flags4;
    vector<int> flags6;
    vector<int> flags8;
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
    Solution s;
    auto actual = s.numberOfBeautifulIntegers(10, 20, 3);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.numberOfBeautifulIntegers(8, 8342341, 8);
    decltype(actual) expect = 34530;
    EXPECT_EQ(expect, actual);
}

}
