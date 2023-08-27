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
#include <functional>
#include <stack>
#include "support.h"

using namespace std;

namespace {

class Solution {
    using ll = long long;

    struct Info {
        Info(ll d) {
            left = right = d;
            v = 0;
            select = true;
        }
        ll left;
        ll right;
        ll v;
        bool select;
    };
public:
    long long ringGame(vector<long long> &challenge)
    {
        long long mask = 0;
        for (auto c : challenge) mask |= c;
        long long highbit = (1LL << 62);
        while ((highbit & mask) == 0) highbit >>= 1;
        list<Info> data;
        for (auto c : challenge) data.emplace_back(c);
        ll result = highbit;
        ll bit = highbit;
        while (data.size() > 1) {
            ll totalr = 0;
            for (auto it = data.begin(); it != data.end(); ++it) {
                if (!it->select) continue;
                it->v |= result;
                while (data.size() > 1) {
                    if (it->v >= it->right) {
                        it->v |= it->right;
                        auto jt = it;
                        if (++jt == data.end()) {
                            jt = data.begin();
                        }
                        if (it->v >= jt->left) {
                            it->v |= jt->left;
                            it->v |= jt->v;
                            it->right = jt->right;
                            data.erase(jt);
                            continue;
                        }
                    } 
                    if (it->v >= it->left) {
                        it->v |= it->left;
                        auto jt = data.end();
                        if (it != data.begin()) {
                            jt = it;
                        }
                        --jt;
                        if (it->v >= jt->right) {
                            it->v |= jt->right;
                            it->v |= jt->v;
                            it->left = jt->left;
                            data.erase(jt);
                            continue;
                        }
                    }
                    break;
                }
                totalr |= it->v;
            }
            if (data.size() == 1) return result;
            for (bit >>= 1; (bit & mask) == 0; bit >>= 1);
            if (bit & totalr) {
                for (auto it = data.begin(); it != data.end(); ++it) {
                    if ((bit & it->v) == 0) it->select = false;
                }
            } else {
                result |= bit;
            }
        }
        return result;
    }
};

// 不是单调的， 
class Solution1Error {
public:
    long long ringGame(vector<long long> &challenge)
    {
        long long low = 0, high = *max_element(challenge.begin(), challenge.end());
        function<bool(int)> ok = [&](int v) {
            deque<int> x;
            int last = challenge.size() - 1;
            for (int i = 0; i <= last; ++i) {
                if (v < challenge[i]) {
                    x.push_back(challenge[i]);
                    continue;
                }
                int vv = v | challenge[i];
                while (true) {
                    if (i + 1 <= last && challenge[i + 1] <= vv) {
                        vv |= challenge[++i];
                        continue;
                    }
                    if (i + 1 > last && !x.empty() && x.front() <= vv) {
                        vv |= x.front();
                        x.pop_front();
                        continue;
                    }
                    if (!x.empty() && x.back() <= vv) {
                        vv |= x.back();
                        x.pop_back();
                        continue;
                    }
                    if (x.empty() && last > i && challenge[last] <= vv) {
                        vv |= challenge[last--];
                        continue;
                    }
                    x.push_back(vv);
                    break;
                }
            }
            return x.size() == 1;
        };

        while (low + 1 < high) {
            auto mid = (low + high) / 2;
            if (ok(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high;
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
TEST_F(TestSolution, TestMain)
{
    vector<long long> challenge = { 45,4,45,3 };
    Solution s;
    auto actual = s.ringGame(challenge);
    decltype(actual) expect = 41;
    EXPECT_EQ(expect, actual);
}

}
