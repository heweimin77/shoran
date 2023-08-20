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
    long long kSum(vector<int> &nums, int k)
    {
        long long sum = 0;
        for (auto &n : nums) {
            if (n >= 0) sum += n;
            else n = -n;
        }
        sort(nums.begin(), nums.end());
        if (k-- == 1) return sum;
        priority_queue<pair<long long, int>> q;
        q.push({ sum - nums[0], 1 });
        while (--k) {
            auto [now, i] = q.top();
            q.pop();
            if (i < nums.size()) {
                q.push({ now - nums[i], i + 1 });
                q.push({ now - nums[i] + nums[i - 1], i + 1 });
            }
        }
        return q.top().first;
    }
};


class Solution2Timeout98of111 {
    using Item = pair<long long, pair<int, int>>;
public:
    long long kSum(vector<int> &nums, int k)
    {
        long long data[2001];
        function<void(int, int, long long[])> getCount = [&](int i, int j, long long data[])->void {
            if (j - i == 1) {
                data[0] = 2;
                data[1] = 0;
                data[2] = nums[i];
                if (nums[i] > 0) swap(data[1], data[2]);
                return;
            }
            int mid = (i + j) / 2;

            long long ldata[2001];
            long long rdata[2001];

            getCount(i, mid, ldata);
            getCount(mid, j, rdata);
            long long *results = &data[1];
            long long count = 0;
            long long lcount = ldata[0];
            long long rcount = rdata[0];
            long long *lr = &ldata[1];
            long long *rr = &rdata[1];

            priority_queue<Item> q;
            for (int k = 0; k < lcount; ++k)
                q.push({ lr[k] + rr[0], {k, 0} });
            while (!q.empty() && count < k) {
                auto [v, pos] = q.top();
                q.pop();
                results[count++] = v;
                if (count == k) break;
                int x = pos.first, y = pos.second + 1;
                if (y >= rcount) continue;
                q.push({ lr[x] + rr[y], {x, y} });
            }
            data[0] = count;
        };

        getCount(0, nums.size(), data);
        return data[k];
    }
};

class Solution2Timeout93of111 {
#define MAKEPOS(x, y)  (((x) << 16) | (y))
    using Infos = vector<long long>;
    using Item = pair<long long, pair<int, int>>;
public:
    long long kSum(vector<int> &nums, int k)
    {
        function<Infos(int, int)> getCount = [&](int i, int j)->Infos {
            if (j - i == 1) {
                if (nums[i] < 0) return Infos{ 0, nums[i] };
                return Infos{ nums[i], 0 };
            }
            int mid = (i + j) / 2;
            auto lr = getCount(i, mid);
            auto rr = getCount(mid, j);
            Infos results;
            priority_queue<Item> q;
            unordered_set<int> visited;
            visited.insert(0);
            q.push({ lr[0] + rr[0], {0, 0} });
            while (!q.empty() && results.size() < k) {
                auto [v, pos] = q.top();

                q.pop();
                results.push_back(v);
                if (results.size() == k) break;

                int nextposes[2][2] = { {pos.first + 1, pos.second}, {pos.first, pos.second + 1} };
                for (auto [x, y] : nextposes) {
                    if (x >= lr.size()) continue;
                    if (y >= rr.size()) continue;
                    if (visited.count(MAKEPOS(x, y)) > 0) continue;
                    visited.insert(MAKEPOS(x, y));
                    q.push({ lr[x] + rr[y], {x, y} });
                }
            }
            return results;
        };

        Infos counts = getCount(0, nums.size());
        return counts.back();
    }
};
class Solution2Timeout92of111 {
#define MAKEPOS(x, y)  (((x) << 16) | (y))
    using Infos = vector<pair<long long, long long>>;
    using Item = pair<long long, pair<int, int>>;
public:
    long long kSum(vector<int> &nums, int k)
    {
        function<Infos(int, int)> getCount = [&](int i, int j)->Infos {
            if (j - i == 1) {
                if (nums[i] < 0) return Infos{ {0, 1}, {nums[i], 1} };
                return Infos{ {nums[i], 1}, { 0, 1 } };
            }
            int mid = (i + j) / 2;
            auto lr = getCount(i, mid);
            auto rr = getCount(mid, j);
            Infos results;
            priority_queue<Item> q;
            unordered_set<int> visited;
            visited.insert(0);
            q.push({ lr[0].first + rr[0].first, {0, 0} });
            int count = 0;
            while (!q.empty()) {
                auto [v, pos] = q.top();
                q.pop();
                auto ncnt = lr[pos.first].second * rr[pos.second].second;
                if (count + ncnt >= k) {
                    results.push_back({ v, k - count });
                    break;
                }
                count += ncnt;
                results.push_back({ v, ncnt });
                int nextposes[2][2] = { {pos.first + 1, pos.second}, {pos.first, pos.second + 1} };
                for (auto [x, y] : nextposes) {
                    if (x >= lr.size()) continue;
                    if (y >= rr.size()) continue;
                    if (visited.count(MAKEPOS(x, y)) > 0) continue;
                    visited.insert(MAKEPOS(x, y));
                    q.push({ lr[x].first + rr[y].first, {x, y} });
                }
            }

            return results;
        };

        Infos counts = getCount(0, nums.size());
        return counts.back().first;
    }
};

class Solution2Timeout68of111 {
public:
    long long kSum(vector<int> &nums, int k)
    {
        map<long long, int> counts = { {0, 1} };
        int tcount = 1;
        for (auto n : nums) {
            unordered_map<long long, int> newcounts;
            for (auto it = counts.rbegin(); it != counts.rend(); ++it) {
                long long nv = n + it->first;
                newcounts[nv] = it->second;
            }
            for (auto &r : newcounts) {
                counts[r.first] += r.second;
            }
            tcount += tcount;
            if (tcount > k) {
                int delcount = tcount - k;
                tcount = k;
                while (delcount > 0) {
                    if (counts.begin()->second > delcount) {
                        counts.begin()->second -= delcount;
                        break;
                    } else {
                        delcount -= counts.begin()->second;
                        counts.erase(counts.begin());
                    }
                }
            }
        }

        return counts.begin()->first;
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
    vector<int> nums = { 2,4,-2 };
    Solution s;
    auto actual = s.kSum(nums, 5);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 1,-2,3,4,-10,12 };
    Solution s;
    auto actual = s.kSum(nums, 16);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
}

