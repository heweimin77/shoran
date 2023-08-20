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
    class Uniset {
    public:
        Uniset(int n) : indexes(n, -1)
        {
        }

        int getIndex(int i) const { return indexes[i]; }
        void merge(int i, int j)
        {
            if (isSameGroup(i, j)) return;
            int ii = getIndex(i), ji = getIndex(j);
            if (ii < 0 && ji < 0) {
                indexes[i] = indexes[j] = groups.size();
                groups.push_back(unordered_set<int>{i, j});
            } else if (ii < 0) {
                indexes[i] = ji;
                groups[ji].insert(i);
            } else if (ji < 0) {
                indexes[j] = ii;
                groups[ii].insert(j);
            } else {
                if (groups[ii].size() < groups[ji].size()) swap(ii, ji);
                auto &t = groups[ii];
                for (auto x : groups[ji]) {
                    indexes[x] = ii;
                    t.insert(x);
                }
                groups[ji].clear();
            }
        }
        bool isSameGroup(int i, int j)
        {
            int ii = getIndex(i), ji = getIndex(j);
            return ii >= 0 && ii == ji;
        }

    private:
        vector<int> indexes;
        vector<unordered_set<int>> groups;
    };

public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&](const int lhs, const int rhs ) {
            return vals[lhs] < vals[rhs];
            });

        int count = 0;
        Uniset uset(n);
        int last = 0;
        int lastv = vals[indexes[0]];
        for (int i = 1; true; ++i) {
            if (i == n || vals[indexes[i]] != lastv) {
                for (int j = last; j < i; ++j) {
                    int now = indexes[j];
                    for (auto next : adjs[now]) {
                        if (vals[next] <= vals[now]) {
                            uset.merge(next, now);
                        }
                    }
                }
                unordered_map<int, int> gcounts;
                for (int j = last; j < i; ++j) {
                    int now = indexes[j];
                    if (uset.getIndex(now) < 0) ++count;
                    else ++gcounts[uset.getIndex(now)];
                }
                for (auto& g : gcounts) {
                    count += g.second + g.second * (g.second - 1) / 2;
                }

                if (i == n) break;
                last = i;
                lastv = vals[indexes[i]];
            }
        }

        return count;
    }
};

class Solution2Timeout123of134 {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        int count = 0;
        function<unordered_map<int, int>(int, int) > travese = [&](int now, int parent) {
            unordered_map<int, int> results;
            ++count;
            results[vals[now]] = 1;
            for (auto next : adjs[now]) {
                if (next == parent) continue;
                unordered_map<int, int> rs = travese(next, now);
                for (auto& r : rs) {
                    if (r.first < vals[now]) continue;
                    auto it = results.find(r.first);
                    if (it != results.end()) {
                        count += r.second * it->second;
                        it->second += r.second;
                    } else {
                        results.insert(r);
                    }
                }
            }

            return results;
        };

        travese(0, -1);

        return count;
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
    vector<int> vals = { 1,3,2,1,3 };
    vector<vector<int>> edges = { {0,1}, {0,2}, {2,3}, {2,4} };
    Solution s;
    auto actual = s.numberOfGoodPaths(vals, edges);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}

