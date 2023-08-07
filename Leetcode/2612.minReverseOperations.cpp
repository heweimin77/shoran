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
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> results(n, -1);
        results[p] = 0;
        if (k == 1) return results;

        vector<bool> ban(n);
        for (auto b : banned) ban[b] = true;

        map<int, int> visiteds[2];
        visiteds[0][n] = visiteds[1][n] = n + 1;
        visiteds[0][p] = visiteds[1][p] = p + 1;

        int changed = (k - 1) & 1;
        queue<int> q;
        q.push(p);
        while (!q.empty()) {
            auto now = q.front();
            int eveodd = (now & 1) ^ changed;
            map<int, int>& visited = visiteds[eveodd];
            int nv = results[now] + 1;
            //cout << "now: " << now << ", " << nv - 1 << endl;
            q.pop();
            // move right
            int xmin = max(now + 1, k - 1 - now);
            int xmax = min(now + k, n + n - k - now);
            getNexts(q, xmin, xmax, results, ban, visited, nv, eveodd);

            // move left
            xmin = max(now - k + 1, k - 1 - now);
            xmax = min(now, n + n - k - now);
            getNexts(q, xmin, xmax, results, ban, visited, nv, eveodd);
        }
        return results;
    }
    void getNexts(queue<int>& q, int xmin, int xmax, vector<int>& results, vector<bool>& ban, map<int, int>& visited, int value, int eveodd) {
        if (xmin >= xmax) return;
        int key = xmin;
        auto it = visited.upper_bound(xmin);
        if (it != visited.begin()) {
            --it;
            if (xmax <= it->second) {
                return;
            } else if (xmin <= it->second) {
                key = it->first;
                xmin = it->second;
            } else {
                // do nothing
            }
            ++it;
        }
        for (; it != visited.end(); ) {
            if (xmax < it->first) {
                process(xmin, xmax, q, results, ban, value, eveodd);
                break;
            } else if (xmax <= it->second) {
                process(xmin, it->first, q, results, ban, value, eveodd);
                xmax = it->second;
                visited.erase(it);
                break;
            } else {
                process(xmin, it->first, q, results, ban, value, eveodd);
                xmin = it->second;
                it = visited.erase(it);
            }
        }
        visited[key] = xmax;
    }
    void process(int xmin, int xmax, queue<int>& q, vector<int>& results, vector<bool>& ban, int v, int eveodd)
    {
        for (int i = xmin; i < xmax; ++i) {
            if ((i & 1) != eveodd) continue;
            if (!ban[i]) {
                results[i] = v;
                q.push(i);
                //cout << "nexts: " << i << ", " << v << endl;
            }
        }
    }
};

class Solution2Timeout701 {
public:
    vector<int> minReverseOperations(int n, int p, vector<int> &banned, int k)
    {
        vector<int> results(n, -1);
        results[p] = 0;
        if (k == 1) return results;

        map<int, int> visited;
        visited[n] = n + 1;
        addVisited(visited, p);
        for (auto b : banned) addVisited(visited, b);
        if (k & 1) {
            for (int i = ((p + 1) & 1); i < n; i += 2) {
                addVisited(visited, i);
            }
        }

        int changed = (k - 1) & 1;
        queue<int> q;
        q.push(p);
        while (!q.empty()) {
            auto now = q.front();
            int nv = results[now] + 1;
            q.pop();
            // move right
            int xmin = max(now + 1, k - 1 - now);
            int xmax = min(now + k, n + n - k - now);
            getNexts(q, xmin, xmax, results, visited, nv, (now & 1) ^ changed);

            // move left
            xmin = max(now - k + 1, k - 1 - now);
            xmax = min(now, n + n - k - now);
            getNexts(q, xmin, xmax, results, visited, nv, (now & 1) ^ changed);
        }
        return results;
    }
    void getNexts(queue<int> &q, int xmin, int xmax, vector<int> &results, map<int, int> &visited, int value, int evenodd)
    {
        if (xmin >= xmax) return;
        vector<pair<int, int>> ranges;
        auto it = visited.upper_bound(xmin);
        if (it != visited.begin()) {
            --it;
            if (xmax <= it->second) {
                return;
            } else if (xmin <= it->second) {
                xmin = it->second;
            } else {
                // do nothing
            }
            ++it;
        }
        for (; it != visited.end(); ++it) {
            if (xmax < it->first) {
                ranges.push_back({ xmin, xmax });
                break;
            } else if (xmax <= it->second) {
                ranges.push_back({ xmin, it->first });
                break;
            } else {
                ranges.push_back({ xmin, it->first });
                xmin = it->second;
            }
        }
        for (auto &r : ranges) {
            int s = r.first;
            if ((s & 1) != evenodd) ++s;
            for (; s < r.second; s += 2) {
                results[s] = value;
                addVisited(visited, s);
                q.push(s);
            }
        }
    }
    void addVisited(map<int, int> &visited, int now)
    {
        auto it = visited.upper_bound(now);
        if (it == visited.begin()) {
            if (it->first == now + 1) {
                int v = it->second;
                visited.erase(it);
                visited.insert({ now, v });
            } else {
                visited.insert({ now, now + 1 });
            }
            return;
        }
        --it;
        if (now < it->second) return;
        if (it->second == now) {
            ++it->second;
        } else {
            visited.insert({ now, now + 1 });
            it = visited.find(now);
        }
        auto jt = it;
        ++jt;
        if (it->second == jt->first) {
            it->second = jt->second;
            visited.erase(jt);
        }
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
    vector<int> banned = { 1,2 };
    Solution s;
    auto actual = s.minReverseOperations(4, 0, banned, 4);
    decltype(actual) expect = { 0,-1,-1,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<int> banned = {};
    Solution s;
    auto actual = s.minReverseOperations(5, 0, banned, 2);
    decltype(actual) expect = { 0,1,2,3,4 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<int> banned = {};
    Solution s;
    auto actual = s.minReverseOperations(3, 0, banned, 3);
    decltype(actual) expect = { 0,-1,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test5)
{
    vector<int> banned = {};
    Solution s;
    auto actual = s.minReverseOperations(4, 0, banned, 4);
    decltype(actual) expect = { 0,-1,-1,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test6)
{
    vector<int> banned = {};
    Solution s;
    auto actual = s.minReverseOperations(5, 0, banned, 4);
    decltype(actual) expect = { 0,3,2,1,4 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> banned = {1};
    Solution s;
    auto actual = s.minReverseOperations(5, 3, banned, 4);
    decltype(actual) expect = { 1,-1,1,0,-1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}
