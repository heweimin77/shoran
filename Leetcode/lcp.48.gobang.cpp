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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
    using ull = unsigned long long;
#define MAKEPOS(x, y)  (((ull)(x) << 32) | ((ull)(y) & 0xFFFFFFFF))
#define GETX(pos)  (int)(unsigned int)((pos) >> 32)
#define GETY(pos)  (int)(unsigned int)((pos) & 0xFFFFFFFF)
    enum {BLACK = 0, WHITE = 1};
public:
    string gobang(vector<vector<int>> &pieces) {
        unordered_map<ull, int> states;
        for (auto &p : pieces) {
            states[MAKEPOS(p[0], p[1])] = p[2];
        }

        int delta[][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
        function<unordered_set<ull>(ull p, int state, int num)> getbyp = [&](ull p, int state, int num) {
            unordered_set<ull> results;
            int x = GETX(p);
            int y = GETY(p);
            for (auto &d : delta) {
                int cnt = 0;
                for (int i = 0; i < 5; ++i) {
                    ull pp = MAKEPOS(x - i * d[0], y - i * d[1]);
                    auto it = states.find(pp);
                    if (it != states.end() && it->second == state) ++cnt;
                }
                for (int i = -4, j = 1; i <= 0; ++i, ++j) {
                    if (cnt == num) {
                        vector<ull> rr;
                        for (int k = i; k < j; ++k) {
                            ull p = MAKEPOS(x + k * d[0], y + k * d[1]);
                            auto it = states.find(p);
                            if (it == states.end()) {
                                rr.push_back(p);
                            } else if (it->second != state) {
                                rr.clear();
                                break;
                            }
                        }
                        for (auto p : rr) {
                            results.insert(p);
                        }
                    }
                    ull p = MAKEPOS(x + j * d[0], y + j * d[1]);
                    auto it = states.find(p);
                    if (it != states.end() && it->second == state) ++cnt;
                    p = MAKEPOS(x + i * d[0], y + i * d[1]);
                    it = states.find(p);
                    if (it != states.end() && it->second == state) --cnt;
                    
                }
            }
            return results;
        };

        function<unordered_set<ull>(int state, int num)> get = [&](int state, int num) {
            unordered_set<ull> results;
            for (auto p : states) {
                if (p.second != state) continue;
                for (auto &r : getbyp(p.first, state, num)) {
                    results.insert(r);
                }
            }
            return results;
        };

        auto r = get(BLACK, 4);
        if (!r.empty()) {
            return "Black";
        }
        r = get(WHITE, 4);
        if (r.size() > 1) {
            return "White";
        }
        if (r.size() == 1) {
            states[*r.begin()] = BLACK;
            auto rr = get(BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(*r.begin());
            return "None";
        }
        r = get(BLACK, 3);
        for (auto p : r) {
            states[p] = BLACK;
            //auto rr = get(BLACK, 4);
            auto rr = getbyp(p, BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(p);
        }
        return "None";
    }
};

class Solution2Ok {
    using ull = unsigned long long;
#define MAKEPOS(x, y)  (((ull)(x) << 32) | ((ull)(y) & 0xFFFFFFFF))
#define GETX(pos)  (int)(unsigned int)((pos) >> 32)
#define GETY(pos)  (int)(unsigned int)((pos) & 0xFFFFFFFF)
    enum { BLACK = 0, WHITE = 1 };
public:
    string gobang(vector<vector<int>> &pieces)
    {
        unordered_map<ull, int> states;
        for (auto &p : pieces) {
            states[MAKEPOS(p[0], p[1])] = p[2];
        }

        int delta[][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
        function<unordered_set<ull>(ull p, int state, int num)> getbyp = [&](ull p, int state, int num) {
            unordered_set<ull> results;
            int x = GETX(p);
            int y = GETY(p);
            for (auto &d : delta) {
                int cnt = 0;
                for (int i = 0; i < 5; ++i) {
                    ull pp = MAKEPOS(x - i * d[0], y - i * d[1]);
                    auto it = states.find(pp);
                    if (it != states.end() && it->second == state) ++cnt;
                }
                for (int i = -4, j = 1; i <= 0; ++i, ++j) {
                    if (cnt == num) {
                        vector<ull> rr;
                        for (int k = i; k < j; ++k) {
                            ull p = MAKEPOS(x + k * d[0], y + k * d[1]);
                            auto it = states.find(p);
                            if (it == states.end()) {
                                rr.push_back(p);
                            } else if (it->second != state) {
                                rr.clear();
                                break;
                            }
                        }
                        for (auto p : rr) {
                            results.insert(p);
                        }
                    }
                    ull p = MAKEPOS(x + j * d[0], y + j * d[1]);
                    auto it = states.find(p);
                    if (it != states.end() && it->second == state) ++cnt;
                    p = MAKEPOS(x + i * d[0], y + i * d[1]);
                    it = states.find(p);
                    if (it != states.end() && it->second == state) --cnt;

                }
            }
            return results;
        };

        function<unordered_set<ull>(int state, int num)> get = [&](int state, int num) {
            unordered_set<ull> results;
            for (auto p : states) {
                if (p.second != state) continue;
                int x = GETX(p.first);
                int y = GETY(p.first);
                for (auto &d : delta) {
                    int cnt = 0;
                    for (int i = 0; i < 5; ++i) {
                        ull pp = MAKEPOS(x - i * d[0], y - i * d[1]);
                        auto it = states.find(pp);
                        if (it != states.end() && it->second == state) ++cnt;
                    }
                    for (int i = -4, j = 1; i <= 0; ++i, ++j) {
                        if (cnt == num) {
                            vector<ull> rr;
                            for (int k = i; k < j; ++k) {
                                ull p = MAKEPOS(x + k * d[0], y + k * d[1]);
                                auto it = states.find(p);
                                if (it == states.end()) {
                                    rr.push_back(p);
                                } else if (it->second != state) {
                                    rr.clear();
                                    break;
                                }
                            }
                            for (auto p : rr) {
                                results.insert(p);
                            }
                        }
                        ull p = MAKEPOS(x + j * d[0], y + j * d[1]);
                        auto it = states.find(p);
                        if (it != states.end() && it->second == state) ++cnt;
                        p = MAKEPOS(x + i * d[0], y + i * d[1]);
                        it = states.find(p);
                        if (it != states.end() && it->second == state) --cnt;
                    }
                }
            }
            return results;
        };

        auto r = get(BLACK, 4);
        if (!r.empty()) {
            return "Black";
        }
        r = get(WHITE, 4);
        if (r.size() > 1) {
            return "White";
        }
        if (r.size() == 1) {
            states[*r.begin()] = BLACK;
            auto rr = get(BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(*r.begin());
            return "None";
        }
        r = get(BLACK, 3);
        for (auto p : r) {
            states[p] = BLACK;
            //auto rr = get(BLACK, 4);
            auto rr = getbyp(p, BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(p);
        }
        return "None";
    }
};

class Solution1Timeout151of157 {
    using ull = unsigned long long;
#define MAKEPOS(x, y)  (((ull)(x) << 32) | ((ull)(y) & 0xFFFFFFFF))
#define GETX(pos)  (int)(unsigned int)((pos) >> 32)
#define GETY(pos)  (int)(unsigned int)((pos) & 0xFFFFFFFF)
    enum { BLACK = 0, WHITE = 1 };
public:
    string gobang(vector<vector<int>> &pieces)
    {
        unordered_map<ull, int> states;
        for (auto &p : pieces) {
            states[MAKEPOS(p[0], p[1])] = p[2];
        }

        int delta[][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
        function<unordered_set<ull>(int state, int num)> get = [&](int state, int num) {
            unordered_set<ull> results;
            for (auto p : states) {
                if (p.second != state) continue;
                int x = GETX(p.first);
                int y = GETY(p.first);
                for (auto &d : delta) {
                    int cnt = 0;
                    for (int i = 0; i < 5; ++i) {
                        ull pp = MAKEPOS(x - i * d[0], y - i * d[1]);
                        auto it = states.find(pp);
                        if (it != states.end() && it->second == state) ++cnt;
                    }
                    for (int i = -4, j = 1; i <= 0; ++i, ++j) {
                        if (cnt == num) {
                            vector<ull> rr;
                            for (int k = i; k < j; ++k) {
                                ull p = MAKEPOS(x + k * d[0], y + k * d[1]);
                                auto it = states.find(p);
                                if (it == states.end()) {
                                    rr.push_back(p);
                                } else if (it->second != state) {
                                    rr.clear();
                                    break;
                                }
                            }
                            for (auto p : rr) {
                                results.insert(p);
                            }
                            ull p = MAKEPOS(x + j * d[0], y + j * d[1]);
                            auto it = states.find(p);
                            if (it != states.end() && it->second == state) ++cnt;
                            p = MAKEPOS(x + i * d[0], y + i * d[1]);
                            it = states.find(p);
                            if (it != states.end() && it->second == state) --cnt;
                        }
                    }
                }
            }
            return results;
        };

        auto r = get(BLACK, 4);
        if (!r.empty()) {
            return "Black";
        }
        r = get(WHITE, 4);
        if (r.size() > 1) {
            return "White";
        }
        if (r.size() == 1) {
            states[*r.begin()] = BLACK;
            auto rr = get(BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(*r.begin());
            return "None";
        }
        r = get(BLACK, 3);
        for (auto p : r) {
            states[p] = BLACK;
            auto rr = get(BLACK, 4);
            if (rr.size() > 1) {
                return "Black";
            }
            states.erase(p);
        }
        return "None";
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
    vector<vector<int>> pieces = { {0,0,1}, {1,1,1}, {2,2,0} };
    Solution s;
    auto actual = s.gobang(pieces);
    decltype(actual) expect = "None";
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> pieces = { {1,2,1}, {1,4,1}, {1,5,1}, {2,1,0}, {2,3,0}, {2,4,0}, {3,2,1}, {3,4,0}, {4,2,1}, {5,2,1} };
    Solution s;
    auto actual = s.gobang(pieces);
    decltype(actual) expect = "Black";
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<vector<int>> pieces = { {-1000000000,-1000000000,0}, {-999999999,-1000000000,0}, {-999999998,-1000000000,0} };
    Solution s;
    auto actual = s.gobang(pieces);
    decltype(actual) expect = "Black";
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<vector<int>> pieces = { {0,-2,1}, {0,0,0}, {0,1,0}, {0,2,0}, {0,4,1}, {1,4,0}, {2,4,0}, {4,4,0} };
    Solution s;
    auto actual = s.gobang(pieces);
    decltype(actual) expect = "None";
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> pieces = { {0,0,1}, {0,1,0}, {0,3,0}, {0,4,0}, {0,7,0}, {0,8,1} };
    Solution s;
    auto actual = s.gobang(pieces);
    decltype(actual) expect = "Black";
    EXPECT_EQ(expect, actual);
}

}
