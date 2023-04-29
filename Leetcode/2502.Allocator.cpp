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

class Allocator {
public:
    Allocator(int n)
    {
        frees.insert({ n, n });
    }

    int allocate(int size, int mID)
    {
        for (auto it = frees.begin(); it != frees.end(); ++it) {
            if (it->second < size) continue;
            auto &bs = used[mID];
            bs.push_back({ it->first - it->second, size });
            it->second -= size;
            if (it->second == 0) {
                frees.erase(it);
            }
            return bs.back().first;
        }
        return -1;
    }

    int free(int mID)
    {
        auto it = used.find(mID);
        if (it == used.end()) {
            return 0;
        }
        int nb = 0;
        for (auto &b : it->second) {
            nb += b.second;
            auto jt = frees.upper_bound(b.first);
            if (jt != frees.end() && (b.first + b.second == jt->first - jt->second)) {
                jt->second += b.second;
            } else {
                jt = frees.insert({ b.first + b.second, b.second }).first;
            }
            if (jt != frees.begin()) {
                auto now = jt--;
                if (jt->first == now->first - now->second) {
                    now->second += jt->second;
                    frees.erase(jt);
                }
            }
        }
        used.erase(it);
        return nb;

    }

private:
    map<int, int> frees;
    unordered_map<int, vector<pair<int, int>>> used;
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

// [[10], [1, 1], [1, 2], [1, 3], [2], [3, 4], [1, 1], [1, 1], [1], [10, 2], [7]]
//  null, 0, 1, 2, 1, 3, 1, 6, 3, -1, 0
TEST_F(TestSolution, Test1)
{
    vector<int> nums = { };
    Allocator s(10);
    EXPECT_EQ(0, s.allocate(1, 1));
    EXPECT_EQ(1, s.allocate(1, 2));
    EXPECT_EQ(2, s.allocate(1, 3));
    EXPECT_EQ(1, s.free(2));
    EXPECT_EQ(3, s.allocate(3, 4));
    EXPECT_EQ(1, s.allocate(1, 1));
    EXPECT_EQ(6, s.allocate(1, 1));
    EXPECT_EQ(3, s.free(1));
    EXPECT_EQ(-1, s.allocate(10, 2));
    EXPECT_EQ(0, s.free(7));
}

}
