#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>

#include "support.h"

using namespace std;

namespace {

class TreeAncestor {
    static constexpr int MASK = 0x7F;
public:
    TreeAncestor(int n, vector<int>& ps) : parent(ps) {
        vector<vector<int>> children(n);
        for (int i = 1; i < n; ++i) {
            children[parent[i]].push_back(i);
        }
        parents.resize(n);
        traverse(children, 0, 0, 0, 0);
    }

    int getKthAncestor(int node, int k) {
        while (node != 0 && k != 0) {
            auto& p = parents[node];
            if (p.second <= k) {
                k -= p.second;
                node = p.first;
            } else {
                for (; k > 0; --k) {
                    node = parent[node];
                }
            }
        }
        return k != 0 ? -1 : node;
    }

    void traverse(vector<vector<int>>& children, int now, int level, int p, int pl) {
        parents[now] = { p, level - pl };
        if ((MASK & level) == 0) {
            p = now;
            pl = level;
        }
        for (auto next : children[now]) {
            traverse(children, next, level + 1, p, pl);
        }
    }

private:
    vector<int>& parent;
    vector<pair<int,int>> parents;
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
    vector<int> parent = { -1,0,0,1,1,2,2 };
    TreeAncestor s(7, parent);
    EXPECT_EQ(1, s.getKthAncestor(3, 1));
    EXPECT_EQ(0, s.getKthAncestor(5, 2));
    EXPECT_EQ(-1, s.getKthAncestor(6, 3));
}
}

