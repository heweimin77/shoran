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
    int maxJump(vector<int> &stones)
    {
        vector<bool> visited(stones.size());
        int low = stones[1], high = stones.back();
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            if (isOK(stones, visited, mid)) {
                high = mid;
            } else {
                low = mid;
            }
            cout << mid << ": " << isOK(stones, visited, mid) << ". " << low << "," << high << endl;
        }
        return high;
    }
    bool isOK(vector<int> &stones, vector<bool> &visited, int x)
    {
        fill(visited.begin(), visited.end(), false);
        visited[0] = true;
        int i = 0;
        for (int next = x; next < stones.back(); next += x) {
            while (stones[i] <= next) ++i;
            --i;
            if (visited[i]) return false;
            visited[i] = true;
            next = stones[i];
        }
        i = 0;
        for (int next = x; next < stones.back(); next += x) {
            while (stones[i] <= next) ++i;
            --i;
            if (visited[i]) {
                if (visited[i - 1]) return false;
                --i;
            }
            visited[i] = true;
            next = stones[i];
        }
        return true;
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
    vector<int> stones = { 0,2,5,6,7 };
    Solution s;
    auto actual = s.maxJump(stones);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
    
}

}
