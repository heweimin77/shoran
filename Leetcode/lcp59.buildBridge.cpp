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
        long long buildBridge(int num, vector<vector<int>>& wood) {
            using XKPair = pair<long long, long long> ;
            long long x = wood[0][0], y = 0;
            long long ldx = 0, rdx = 0;
            priority_queue<XKPair> left;
            priority_queue<XKPair, vector<XKPair>, greater<XKPair>> right;
            left.push({ 0, -1 });
            right.push({ 0, 1 });
            int d = wood[0][1] - wood[0][0];
            for (int i = 1; i < wood.size(); ++i) {
                auto& w = wood[i];
                int nd = w[1] - w[0];
                x -= nd;
                rdx += d + nd;
                if (right.top().second == 0) {
                    right.pop();
                }
                if (right.top().first != -rdx) {
                    right.push({ -rdx, 0 });
                }
                y += abs(x - w[0]);

                if (w[0] == x) {
                    left.push({ -ldx, -1 });
                    right.push({ -rdx, 1 });
                } else if (w[0] > x) {
                    right.push({ w[0] - x - rdx, 2});
                    int k = -1;
                    while (!right.empty() && right.top().first == -rdx) {
                        k += right.top().second;
                        right.pop();
                    }
                    if (k >= 0) {
                        left.push({ -ldx, -1 });
                        right.push({ -rdx, k });
                    } else {
                        int xx = x + rdx + right.top().first;
                        int dx = xx - x;
                        x += dx;
                        y -= dx;
                        ldx -= dx;
                        rdx -= dx;
                        left.push({-ldx, -1});
                        k = -1;
                        while (!right.empty() && right.top().first == -rdx) {
                            k += right.top().second;
                            right.pop();
                        }
                        right.push({ -rdx, k });
                    }
                }
                else {
                    left.push({ w[0] - x - ldx , -2});
                    int k = 1;
                    while (!left.empty() && left.top().first == -ldx) {
                        k += left.top().second;
                        left.pop();
                    }
                    if (k < 0) {
                        left.push({ -ldx, k });
                        right.push({ -rdx, 1 });
                    } else {
                        right.push({ -rdx, 1 });
                        int xx = x + ldx + left.top().first;
                        int dx = xx - x;
                        x += dx;
                        // y 
                        ldx -= dx;
                        rdx -= dx;
                        right.push({ -rdx, 0 });
                    }
                }
                d = nd;
            }
            return y;
        }
    };

    // O(N * N * M)
    class Solution2PrimDP {
    public:
        long long buildBridge(int num, vector<vector<int>>& wood) {
            vector<long long> results(num + 1, 0);
            vector<long long> nexts;
            int d = 0;
            for (auto& w : wood) {
                int nd = w[1] - w[0];
                for (int j = 0; j + nd <= num; ++j) {
                    long long r = LLONG_MAX;
                    for (int k = max(0, j - d); k < min(j + nd + 1, (int)results.size()); ++k) {
                        r = min(r, results[k]);
                    }
                    nexts.push_back(abs(j - w[0]) + r);
                }
                d = nd;
                results.swap(nexts);
                nexts.resize(0);
            }
            return *min_element(results.begin(), results.end());
        }
    };

    // O(N * M * log(M)
    class Solution3DP {
    public:
        long long buildBridge(int num, vector<vector<int>>& wood) {
            vector<long long> results(num + 1, 0);

            int d = 0;
            for (auto& w : wood) {
                int nd = w[1] - w[0];
                priority_queue<pair<int, int>, std::vector<pair<int, int>>, greater<pair<int, int>>> q;
                for (int j = 0; j < nd; ++j) {
                    q.push({ results[j], j });
                }
                int ll = -d, rr = nd;
                for (int j = 0; j <= num; ++j, ++ll, ++rr) {
                    if (rr < results.size()) q.push({ results[rr], rr });
                    while (q.top().second < ll) q.pop();
                    results[j] = q.top().first + abs(j - w[0]);
                }
                d = nd;
            }

            return *min_element(results.begin(), results.end());
        }
    };

    // O(M * M)
    class Solution4 {
    public:
        long long buildBridge(int num, vector<vector<int>>& wood) {
            int left = wood[0][0];
            list < pair<int, long long>> results = { {left, 0}, {0, left}, {num + 1 - left, num + 1} };

            int d = wood[0][1] - wood[0][0];
            for (size_t i = 1; i < wood.size(); ++i) {
                auto& w = wood[i];
                int nd = w[1] - w[0];
                auto mit = min_element(results.begin(), results.end());
                int ll = w[0], rr = mit->first;
                // 计算ll, [ll-d, ll+nd]
                if (ll + nd < mit->second || ll - d > mit->second) {
                    int x = ll - d;
                    if (ll + nd < mit->second) {
                        x = ll + nd;
                    }
                    auto it = results.begin();
                    for (; it != results.end(); ++it) {
                        if (it->second > x) {
                            break;
                        }
                    }
                    auto ij = it--;
                    if (it->second == x) {
                        rr = it->first;
                    }
                    else {
                        auto k = (ij->first - it->first) / (ij->second - it->second);
                        rr = it->first + k * (x - it->second);
                    }
                }
                auto mv = *mit;
                ++mit;
                if (mit->first != mv.first) {
                    mit = results.insert(mit, mv);
                }
                bool isinsert = false;
                for (auto it = results.begin(); it != mit; ++it) {
                    it->second -= nd;
                    it->first += abs(it->second - ll);
                    if (!isinsert) {
                        if (it->second == ll) {

                        }
                        else if (it->second > ll) {
                            it = results.insert(it, { rr, ll });
                            ++it;
                            isinsert = true;
                        }

                    }
                }
                for (auto it = mit; it != results.end(); ++it) {
                    it->second += d;
                    it->first += abs(it->second - ll);
                    if (!isinsert) {
                        if (it->second == ll) {

                        }
                        else if (it->second > ll) {
                            it = results.insert(it, { rr, ll });
                            ++it;
                            isinsert = true;
                        }
                    }
                }

                d = nd;

                //for (auto it = results.begin(); it != results.end(); ++it) {
                //    cout << "(" << it->second << ", " << it->first << ") ";
                //}
                //cout << endl;
            }

            return min_element(results.begin(), results.end())->first;

        }
    };

    // O(M * log(M))
    class Solution5SlowMap {
    public:
        long long buildBridge(int num, vector<vector<int>>& wood) {
            long long x = wood[0][0], y = 0;
            long long ldx = 0, rdx = 0;
            map<long long, long long> left, right;
            left[0] = -1;
            right[0] = 1;
            int d = wood[0][1] - wood[0][0];
            for (int i = 1; i < wood.size(); ++i) {
                auto& w = wood[i];
                int nd = w[1] - w[0];
                x -= nd;
                rdx += d + nd;
                if (right.begin()->second == 0) {
                    right.erase(right.begin());
                }
                right[-rdx] += 0;
                y += abs(x - w[0]);

                auto ileft = left.rbegin();
                auto iright = right.begin();
                if (w[0] == x) {
                    ileft->second += -1;
                    iright->second += 1;
                }
                else if (w[0] > x) {
                    right[w[0] - x - rdx] += 2;
                    iright->second -= 1;
                    if (iright->second >= 0) {
                        ileft->second -= 1;
                    }
                    else {
                        right.erase(iright);
                        iright = right.begin();
                        iright->second -= 1;
                        int xx = x + rdx + iright->first;
                        int dx = xx - x;
                        x += dx;
                        y -= dx;
                        ldx -= dx;
                        rdx -= dx;
                        left.insert({ -ldx, -1 });
                    }
                }
                else {
                    left[w[0] - x - ldx] -= 2;
                    ileft->second += 1;
                    if (ileft->second < 0) {
                        iright->second += 1;
                    }
                    else {
                        auto it = left.end();
                        left.erase(--it);
                        ileft = left.rbegin();
                        int xx = x + ldx + ileft->first;
                        int dx = xx - x;
                        x += dx;
                        // y 
                        ldx -= dx;
                        rdx -= dx;
                        iright->second += 1;
                        right.insert({ -rdx, 0 });
                    }
                }
                d = nd;
            }
            return y;
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
        vector<vector<int>> para = { {1,2},{2,4}};
        vector<int> ipara = { 0,0,2 };
        vector<int> ipara2 = { 2,3,5 };
        Solution s;
        auto actual = s.buildBridge(5, para);
        decltype(actual) expect = 0;
        EXPECT_EQ(expect, actual);
    }
}



