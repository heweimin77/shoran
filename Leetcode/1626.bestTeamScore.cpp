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
        int bestTeamScore(vector<int>& scores, vector<int>& ages) {
            int n = scores.size();
            vector<int> indexes(n);
            for (int i = 0; i < n; ++i) indexes[i] = i;
            sort(indexes.begin(), indexes.end(), [&](int lhs, int rhs) {
                return ((ages[lhs] << 20) | scores[lhs]) < ((ages[rhs] << 20) | scores[rhs]);
                });
            list<pair<int, int>> results;
            results.push_back({ 0, 0 });
            auto now = results.begin();

            int age = 0;
            for (int i = 0; i < n; ++i) {
                int a = ages[indexes[i]], s = scores[indexes[i]];
                if (a > age) {
                    now = results.begin();
                }

                for (; now != results.end(); ++now) {
                    if (now->first > s) break;
                }

                --now;
                if (now->first == s) {
                    now->second += s;
                } else {
                    auto n = now;
                    now = results.insert(++n, { s, s + now->second });
                }
                auto n = now;
                for (++n; n != results.end() && n->second <= now->second; ) {
                    n = results.erase(n);
                }
            }
            return results.back().second;
        }
    };

   class Solution2 {
    public:
        int bestTeamScore(vector<int>& scores, vector<int>& ages) {
            int n = scores.size();
            vector<int> indexes(n);
            for (int i = 0; i < n; ++i) indexes[i] = i;
            sort(indexes.begin(), indexes.end(), [&](int lhs, int rhs) {
                return ((ages[lhs] << 20) | scores[lhs]) < ((ages[rhs] << 20) | scores[rhs]);
                });
            vector < pair<int, int>> nows;
            vector < pair<int, int>> results = { {0, 0} };
            int nowindex = 0;
            int age = 0;
            for (int i = 0; i < n; ++i) {
                int a = ages[indexes[i]], s = scores[indexes[i]];
                if (a > age) {
                    age = a;
                    for (; nowindex < nows.size(); ++nowindex) {
                        if (nows[nowindex].second > results.back().second) break;
                    }
                    for (; nowindex < nows.size(); ++nowindex) {
                        results.push_back(nows[nowindex]);
                    }
                    nows = std::move(results);
                    nowindex = 0;
                    results = { {0, 0} };
                }
                for (; nowindex < nows.size(); ++nowindex) {
                    if (nows[nowindex].first > s) break;
                    if (results.back().second < nows[nowindex].second) {
                        results.push_back(nows[nowindex]);
                    }
                }
                auto& last = results.back();
                if (last.first == s) {
                    last.second += s;
                }
                else {
                    results.push_back({ s, s + last.second });
                }
            }
            return max(results.back().second, nows.back().second);
        }
    };



    class Solution3 {
    public:
        int bestTeamScore(vector<int>& scores, vector<int>& ages) {
            int n = scores.size();
            vector<int> indexes(n);
            for (int i = 0; i < n; ++i) indexes[i] = i;
            sort(indexes.begin(), indexes.end(), [&](int lhs, int rhs) {
                return ((ages[lhs] << 20) | scores[lhs]) < ((ages[rhs] << 20) | scores[rhs]);
                });
            vector < pair<int, int>> nows = { {0, 0} };
            vector < pair<int, int>> results = { {0, 0} };
            auto now = nows.begin();
            auto nowlimit = nows.end();
            int age = ages[indexes[0]];
            for (int i : indexes) {
                int a = ages[i], s = scores[i];
                if (a > age) {
                    age = a;
                    for (; now != nowlimit; ++now) {
                        if (now->second > results.back().second) break;
                    }
                    for (; now != nowlimit; ++now) {
                        results.push_back(*now);
                    }
                    nows.swap(results);
                    now = nows.begin() + 1;
                    nowlimit = nows.end();
                    results.resize(1);
                }
                for (; now != nowlimit && now->first <= s; ++now) {
                    if (results.back().second < now->second) {
                        results.push_back(*now);
                    }
                }
                auto& last = results.back();
                if (last.first == s) {
                    last.second += s;
                }
                else {
                    results.push_back({ s, s + last.second });
                }
            }
            return max(results.back().second, nows.back().second);
        }
    };

    class Solution5 {
    public:
        int bestTeamScore(vector<int>& scores, vector<int>& ages) {
            int n = scores.size();
            int* indexes = (int*)malloc(sizeof(int) * n);
            int* results1 = (int*)malloc(sizeof(int) * (n + 2) * 4);
            int* results2 = results1 + (n + 1) * 2;
            *results1 = *(results1 + 1) = 0;
            *results2 = *(results2 + 1) = 0;
            int* r = results1;
            int* now = results2 + 2, * nowlimit = results2 + 2;

            for (int i = 0; i < n; ++i) indexes[i] = i;
            sort(indexes, indexes + n, [&](int lhs, int rhs) {
                return ((ages[lhs] << 20) | scores[lhs]) < ((ages[rhs] << 20) | scores[rhs]);
                });

            int age = ages[indexes[0]];
            for (int* i = indexes; i < indexes + n; ++i) {
                int a = ages[*i], s = scores[*i];
                if (a > age) {
                    age = a;
                    for (; now != nowlimit; now += 2) {
                        if (*(now + 1) > *(r + 1)) break;
                    }
                    for (; now != nowlimit; now += 2) {
                        r += 2;
                        *r = *now;
                        *(r + 1) = *(now + 1);
                    }

                    swap(results1, results2);
                    now = results2 + 2;
                    nowlimit = r + 2;
                    r = results1;
                }
                for (; now != nowlimit && *now <= s; now += 2) {
                    if (*(r + 1) < *(now + 1)) {
                        r += 2;
                        *r = *now;
                        *(r + 1) = *(now + 1);
                    }
                }
                if (r[0] == s) {
                    *(r + 1) += s;
                }
                else {
                    r += 2;
                    *r = s;
                    *(r + 1) = s + *(r - 1);
                }
            }
            return max(*(r + 1), *(nowlimit - 1));
        }
    };

    class Solution6 {
    public:
        int bestTeamScore(vector<int>& scores, vector<int>& ages) {
            int n = scores.size();
            int* indexes = (int*)malloc(sizeof(int) * n);
            int* results1 = (int*)malloc(sizeof(int) * (n + 2) * 4);
            int* results2 = results1 + (n + 1) * 2;
            *results1++ = 0;
            *results1++ = 0;
            *results2++ = 0;
            *results2++ = 0;
            int* r = results1;
            int* now = results2, * nowlimit = results2;

            for (int i = 0; i < n; ++i) indexes[i] = i;
            sort(indexes, indexes + n, [&](int lhs, int rhs) {
                return ((ages[lhs] << 20) | scores[lhs]) < ((ages[rhs] << 20) | scores[rhs]);
                });

            int age = ages[indexes[0]];
            for (int* i = indexes; i < indexes + n; ++i) {
                int a = ages[*i], s = scores[*i];
                if (a > age) {
                    age = a;
                    for (; now != nowlimit; now += 2) {
                        if (*(now + 1) > *(r - 1)) break;
                    }
                    while (now != nowlimit) {
                        *r++ = *now++;
                        *r++ = *now++;
                    }

                    swap(results1, results2);
                    now = results2;
                    nowlimit = r;
                    r = results1;
                }
                while (now != nowlimit && *now <= s) {
                    if (*(r - 1) < *(now + 1)) {
                        *r++ = *now++;
                        *r++ = *now++;
                    }
                    else {
                        ++now, ++now;
                    }
                }
                if (*(r - 2) == s) {
                    *(r - 1) += s;
                }
                else {
                    *r++ = s;
                    *r = s + *(r - 2);
                    ++r;
                }
            }
            return max(*(r - 1), *(nowlimit - 1));
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
        vector<int> para = { 1, 2, 3, 5 };
        vector<int> ipara = {8, 9, 10, 1};
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        auto actual = s.bestTeamScore(para, ipara);
        decltype(actual) expect = 6;
        EXPECT_EQ(expect, actual);
    }
}



