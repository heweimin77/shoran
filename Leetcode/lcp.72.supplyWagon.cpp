#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<int> supplyWagon(vector<int> &supplies)
    {
        int n = supplies.size();
        vector<pair<int, int>> links(n);
        for (int i = 0; i < n; ++i) {
            links[i] = { i - 1, i + 1 };
        }

        using Info = pair<int, int>;
        priority_queue<Info, vector<Info>, greater<Info>> q;
        for (int i = 1; i < supplies.size(); ++i) {
            q.push({ supplies[i - 1] + supplies[i], i - 1 });
        }
        int count = n - n / 2;
        while (count > 0) {
            auto t = q.top();
            q.pop();
            if (supplies[t.second] == 0) continue;
            auto &link = links[t.second];
            if (supplies[link.second] == 0 || t.first != supplies[t.second] + supplies[link.second]) continue;
            supplies[t.second] = t.first;
            supplies[link.second] = 0;
            link.second = links[link.second].second;
            if (link.second < n) {
                q.push({supplies[t.second] + supplies[link.second], t.second});
                links[link.second].first = t.second;
            }
            if (link.first >= 0) {
                q.push({ supplies[t.second] + supplies[link.first], link.first });
            }
            --count;
        }
        supplies.erase(remove(supplies.begin(), supplies.end(), 0), supplies.end());
        return supplies;
    }
};



class Solution2 {
public:
    vector<int> supplyWagon(vector<int> &supplies)
    {
        int count = supplies.size() - supplies.size() / 2;
        for (int i = 0; i < count; ++i) {
            int r = 1;
            int msu = supplies[0] + supplies[1];
            for (int j = 2; j < supplies.size(); ++j) {
                if (supplies[j - 1] + supplies[j] < msu) {
                    msu = supplies[j - 1] + supplies[j];
                    r = j;
                }
            }
            supplies[r - 1] += supplies[r];
            supplies.erase(supplies.begin() + r);
        }
        return supplies;
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
    vector<int> supplies = { 1,3,1,5 };
    Solution s;
    auto actual = s.supplyWagon(supplies);
    decltype(actual) expect = {5,5};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
