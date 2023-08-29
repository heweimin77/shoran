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
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        priority_queue < pair<int, int>> counts;

        function<void(const pair<int, int>&)> qpush = [&](const pair<int, int>& p) {
            if (p.first > 1) counts.push(p);
        };

        map<int, int> ranges;
        int n = s.size();
        int count = 0;
        char ch = s[0];
        for (int i = 0; i < n; ++i) {
            if (s[i] == ch) ++count;
            else {
                ranges.insert({ i - count, count });
                qpush({ count, i - count });
                ch = s[i];
                count = 1;
            }
        }
        ranges.insert({ n - count, count });
        qpush({ count, n - count });

        vector<int> results;
        for (int i = 0; i < queryCharacters.size(); ++i) {
            int index = queryIndices[i];
            char prev = s[index], next = queryCharacters[i];
            if (prev == next) {
                //results.push_back(counts.top().first);
            } else {
                if (index == 0) {
                    auto it = ranges.begin();
                    if (prev == s[index + 1]) {
                        qpush({ it->second - 1, 1 });
                        ranges[1] = it->second - 1;
                        ranges[0] = 1;
                    } else if (next == s[index + 1]) {
                        ++it;
                        int v = it->second + 1;
                        qpush({ v, 0 });
                        ranges.erase(it);
                        ranges[0] = v;
                    } else {
                        //do noting
                    }
                } else if (index == n - 1) {
                    auto it = ranges.rbegin();
                    if (prev == s[index - 1]) {
                        qpush({ it->second - 1, it->first });
                        qpush({ 1, n - 1 });
                        it->second -= 1;
                        ranges.insert({ n - 1, 1 });
                    } else if (next == s[index - 1]) {
                        ++it;
                        qpush({ it->second + 1, it->first });
                        it->second += 1;
                        auto jt = ranges.end();
                        --jt;
                        ranges.erase(jt);
                    } else {
                        // do nothing
                    }

                } else {
                    auto it = ranges.upper_bound(index);
                    --it;

                    if (s[index - 1] == prev) {
                        if (s[index + 1] == prev) {
                            qpush({ index - it->first, it->first });
                            qpush({ 1, index });
                            int v = it->second - 1 - index + it->first;
                            qpush({ v, index + 1 });
                            it->second = index - it->first;
                            ranges[index] = 1;
                            ranges[index + 1] = v;
                        } else if (s[index + 1] == next) {
                            auto jt = it++;
                            qpush({ jt->second - 1, jt->first });
                            int v = it->second + 1;
                            qpush({ v, index });
                            jt->second -= 1;
                            ranges.erase(it);
                            ranges[index] = v;
                        } else {
                            qpush({ it->second - 1, it->first });
                            qpush({ 1, index });
                            it->second -= 1;
                            ranges[index] = 1;
                        }
                    } else if (s[index - 1] == next) {
                        if (s[index + 1] == prev) {
                            auto jt = it;
                            --jt;
                            qpush({ jt->second + 1, jt->first });
                            int v = it->second - 1;
                            qpush({ v, index + 1 });
                            jt->second += 1;
                            ranges.erase(it);
                            ranges[index + 1] = v;
                        } else if (s[index + 1] == next) {
                            auto jt = it;
                            ++it, --jt;
                            qpush({ it->second + jt->second + 1, jt->first });
                            jt->second += it->second + 1;
                            ranges.erase(it);
                            ranges.erase(index);
                        } else {
                            --it;
                            qpush({ it->second + 1, it->first });
                            it->second += 1;
                            ranges.erase(index);
                        }
                    } else {
                        if (prev == s[index + 1]) {
                            qpush({ 1, index });
                            int v = it->second - 1;
                            qpush({ v, index + 1 });
                            ranges[index + 1] = v;
                            ranges[index] = 1;
                        } else if (next == s[index + 1]) {
                            ++it;
                            int v = it->second + 1;
                            qpush({ v, index });
                            ranges.erase(it);
                            ranges[index] = v;
                        } else {
                            //do noting
                        }

                    }
                }
            }

            s[index] = next;

            while (!counts.empty()) {
                auto [len, now] = counts.top();
                auto it = ranges.find(now);
                if (it != ranges.end() && it->second == len) {
                    break;
                }
                counts.pop();
            }

            results.push_back(counts.empty() ? 1 : counts.top().first);

        }

        return results;
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
    vector<int> queryIndices = { 1,3,3 };
    Solution s;
    auto actual = s.longestRepeating("babacc", "bcb", queryIndices);
    decltype(actual) expect = {3, 3, 4};
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<int> queryIndices = { 3,4,2,6,5,6,5,4,3,2 };
    Solution s;
    auto actual = s.longestRepeating("geuqjmt", "bgemoegklm", queryIndices);
    decltype(actual) expect = { 1,1,2,2,2,2,2,2,2,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<int> queryIndices = { 5,4,0,1,5 };
    Solution s;
    auto actual = s.longestRepeating("exjwgrh", "qreuu", queryIndices);
    decltype(actual) expect = { 1,1,1,1,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<int> queryIndices = { 2,0,0,1,2,0,2,0,2 };
    Solution s;
    auto actual = s.longestRepeating("mef", "dmdaucfak", queryIndices);
    decltype(actual) expect = { 1,1,1,1,1,1,1,2,2 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> queryIndices = { 3,4,1,3,4,0,3,1,1,2 };
    Solution s;
    auto actual = s.longestRepeating("rzfqgn", "bllcqhbbfd", queryIndices);
    decltype(actual) expect = { 1,1,1,1,1,1,1,1,2,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
