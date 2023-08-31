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
#include <string>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
        if (p == 2 && target != 1) return 0;
        if (p == 5 && target != 4) return 0;
        int n = gem.size();
        array < vector<int>, 10 > masks;
        for (int i = 0; i < (1 << n); ++i) {
            int x = i;
            int cnt = 0;
            while (x > 0) {
                ++cnt;
                x &= (x - 1);
            }
            masks[cnt].push_back(i);
        }
        if (p == 2 || p == 5) {
            array<int, 512> counts;
            fill(counts.begin(), counts.end(), 0);
            for (int i = 0; i < n; ++i) {
                counts[1 << i] = 1;
            }
            for (int cnt = 2; cnt <= n; ++cnt) {
                for (int i = 1; i < cnt; ++i) {
                    for (auto lm : masks[i]) {
                        for (auto rm : masks[cnt - i]) {
                            if (lm & rm) continue;
                            counts[lm | rm] += counts[lm] * counts[rm];
                        }
                    }
                }
            }
            return counts[(1 << n) - 1];
        }
        
        array<long long, 134> power10;
        array<long long, 134> ipower10;

        long long r = 1;
        for (int i = 0; i < power10.size(); ++i) {
            power10[i] = r;
            ipower10[i] = fast_power(r, p - 2, p);
            r = (r * 10) % p;
        }

        array<int, 512> lens;
        fill(lens.begin(), lens.end(), 0);
        for (int i = 0; i < n; ++i) {
            lens[1 << i] = to_string(gem[i]).size() + 2;
        }
        for (int cnt = 2; cnt <= n; ++cnt) {
            for (auto lm : masks[1]) {
                for (auto rm : masks[cnt - 1]) {
                    if (lm & rm) continue;
                    lens[lm | rm] = lens[lm] + lens[rm] + 2;
                }
            }
        }

        array<unordered_map<long long, int>, 512> results;
        for (int i = 0; i < n; ++i) {
            int len = to_string(gem[i]).size();
            long long r = power10[len + 1] + 10LL * gem[i] + 9;
            results[1 << i][r % p] = 1;
        }

        if (n == 1) {
            return results[1][target];
        }
        int limit = min(6, n);
        for (int cnt = 2; cnt <= limit; ++cnt) {
            for (int i = 1; i < cnt; ++i) {
                for (auto lm : masks[i]) {
                    for (auto rm : masks[cnt - i]) {
                        if (lm & rm) continue;
                        auto& result = results[lm | rm];
                        int llen = lens[lm];
                        int rlen = lens[rm];
                        for (auto lr : results[lm]) {
                            for (auto rr : results[rm]) {
                                long long r = power10[llen + rlen + 1] + lr.first * power10[rlen + 1] + rr.first * 10 + 9;
                                result[r % p] += lr.second * rr.second;
                            }
                        }
                    }
                }
            }
        }
        if (n <= 6) {
            return results[(1 << n) - 1][target];
        }

        function<int(int, int, int)> dfs = [&](int cnt, int flag, int value){
            if (cnt <= 6) {
                auto it = results[flag].find(value);
                return it == results[flag].end() ? 0 : it->second;
            }
            auto it = results[flag].find(value);
            if (it != results[flag].end()) return it->second;
            int count = 0;
            for (int i = 1, j = cnt - i; i <= j; ++i, --j) {
                for (auto lm : masks[i]) {
                    if ((lm | flag) != flag) continue;
                    auto gm = lm ^ flag;
                    for (auto& lr : results[lm]) {
                        // lr & gm
                        long long part = (power10[lens[lm] + lens[gm] + 1] + lr.first * power10[lens[gm] + 1] + 9) % p;
                        long long x = (value + p - part) * ipower10[1] % p;
                        count += lr.second * dfs(j, gm, x);

                        if (i < j) {
                            // gm & lr
                            part = (power10[lens[lm] + lens[gm] + 1] + lr.first * power10[1] + 9) % p;
                            x = (value + p - part) * ipower10[1 + lens[lm]] % p;
                            count += lr.second * dfs(j, gm, x);
                        }
                    }

                }
            }
            results[flag][value] = count;
            return count;
        };
        return dfs(n, (1 << n) - 1, target);
    }

    long long fast_power(long long base, long long n, long long module) {
        long long result = 1;
        int mask = 1;
        for (int mask = 1; mask <= n; mask <<= 1) {
            if (mask & n) {
                result *= base;
                result %= module;
            }
            base *= base;
            base %= module;
        }
        return result;
    }
};

class Solution3Timeout79 {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
        if (p == 2 && target != 1) return 0;
        if (p == 5 && target != 4) return 0;

        long long r = 1;
        int n = gem.size();
        for (int i = 0; i < power10.size(); ++i) {
            power10[i] = r;
            r = (r * 10) % p;
        }
        for (int i = 0; i < 512; ++i) {
            int x = i;
            int cnt = 0;
            while (x > 0) {
                ++cnt;
                x &= (x - 1);
            }
            masks[cnt].push_back(i);
        }
        array<pair<unordered_map<long long, int>, int>, 512> results;
        for (int i = 0; i < n; ++i) {
            int len = to_string(gem[i]).size();
            long long r = power10[len + 1] + 10LL * gem[i] + 9;
            results[1 << i].second = len + 2;
            results[1 << i].first[r % p] = 1;
        }

        if (n == 1) {
            return results[1].first[target];
        }

        for (int cnt = 2; cnt < n; ++cnt) {
            for (int i = 1; i < cnt; ++i) {
                for (auto lm : masks[i]) {
                    for (auto rm : masks[cnt - i]) {
                        if (lm & rm) continue;
                        auto& result = results[lm | rm];
                        int llen = results[lm].second;
                        int rlen = results[rm].second;
                        result.second = llen + rlen + 2;
                        auto& rmap = result.first;
                        for (auto lr : results[lm].first) {
                            for (auto rr : results[rm].first) {
                                long long r = power10[llen + rlen + 1] + lr.first * power10[rlen + 1] + rr.first * 10 + 9;
                                rmap[r % p] += lr.second * rr.second;
                            }
                        }
                    }
                }
            }
        }

        long long invert10 = fast_power(10, p - 2, p);
        int count = 0;
        for (int i = 1; i < n; ++i) {
            for (auto lm : masks[i]) {
                for (auto rm : masks[n - i]) {
                    if (lm & rm) continue;
                    auto& result = results[lm | rm];
                    int llen = results[lm].second;
                    int rlen = results[rm].second;
                    if (p == 2 || p == 5) {
                        if (!results[lm].first.empty() && !results[rm].first.empty()) {
                            count += results[lm].first.begin()->second * results[rm].first.begin()->second;
                        }
                        continue;
                    } 
                    for (auto lr : results[lm].first) {
                        long long part = (power10[llen + rlen + 1] + lr.first * power10[rlen + 1] + 9) % p;
                        long long x = (target + p - part) * invert10 % p;
                        count += lr.second * results[rm].first[x];
                       
                    }
                }
            }
        }
        return count;
    }

    long long fast_power(long long base, long long n, long long module) {
        long long result = 1;
        int mask = 1;
        for (int mask = 1; mask <= n; mask <<= 1) {
            if (mask & n) {
                result *= base;
                result %= module;
            }
            base *= base;
            base %= module;
        }
        return result;
    }
 
private:
    array<long long, 134> power10;
    array < vector<int>, 10 > masks;
};

class Solution2Timeout55 {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
        long long r = 1;
        for (int i = 0; i < power10.size(); ++i) {
            power10[i] = r;
            r = (r * 10) % p;
        }
        for (int i = 0; i < 512; ++i) {
            int x = i;
            int cnt = 0;
            while (x > 0) {
                ++cnt;
                x &= (x - 1);
            }
            masks[cnt].push_back(i);
        }

        vector<long long> results;
        traverse(gem, p, results);
        return count(results.begin(), results.end(), target);
    }
    int traverse(vector<int>& gem, long long p, vector<long long>& results) {
        int len = 0;
        long long r = 0;
        if (gem.size() == 1) {
            len = to_string(gem[0]).size() + 1;
            r = power10[len] + 9LL + gem[0] * 10LL;
            r %= p;
            results.push_back(r);
            ++len;
        } else {
            for (int i = 1; i < gem.size(); ++i) {
                len = traverse2(gem, p, results, i);
            }
        }
        return len;
    }
    int traverse2(vector<int>& gem, long long  p, vector<long long>& results, int cnt1) {
        int limit = 1 << gem.size();
        vector<int> lgem;
        vector<int> rgem;
        int len = 0;
        for (auto mask : masks[cnt1]) {
            if (mask >= limit) break;
            lgem.clear(), rgem.clear();
            for (int i = 0, flag = 1; i < gem.size(); ++i, flag <<= 1) {
                if (mask & flag) {
                    lgem.push_back(gem[i]);
                } else {
                    rgem.push_back(gem[i]);
                }
            }
            vector<long long> lrs, rrs;
            int len1 = traverse(lgem, p, lrs);
            int len2 = traverse(rgem, p, rrs);
            long long r = power10[len1 + len2 + 1] + 9;
            for (auto lr : lrs) {
                for (auto rr : rrs) {
                    long long r = power10[len1 + len2 + 1] + lr * power10[len2 + 1] + rr * 10 + 9;
                    results.push_back(r % p);
                }
            }
            len = len1 + len2 + 2;
        }
        return len;
    }
private:
    array<long long, 134> power10;
    array < vector<int>, 10 > masks;
};

class Solution1Timeout82 {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
        long long r = 1;
        int n = gem.size();
        for (int i = 0; i < power10.size(); ++i) {
            power10[i] = r;
            r = (r * 10) % p;
        }
        for (int i = 0; i < 512; ++i) {
            int x = i;
            int cnt = 0;
            while (x > 0) {
                ++cnt;
                x &= (x - 1);
            }
            masks[cnt].push_back(i);
        }
        array<pair<unordered_map<long long, int>, int>, 512> results;
        for (int i = 0; i < n; ++i) {
            int len = to_string(gem[i]).size();
            long long r = power10[len + 1] + 10LL * gem[i] + 9;
            results[1 << i].second = len + 2;
            results[1 << i].first[r % p] = 1;
        }
        for (int cnt = 2; cnt <= n; ++cnt) {
            for (int i = 1; i < cnt; ++i) {
                for (auto lm : masks[i]) {
                    for (auto rm : masks[cnt - i]) {
                        if (lm & rm) continue;
                        auto& result = results[lm | rm];
                        int llen = results[lm].second;
                        int rlen = results[rm].second;
                        result.second = llen + rlen + 2;
                        auto& rmap = result.first;
                        for (auto lr : results[lm].first) {
                            for (auto rr : results[rm].first) {
                                long long r = power10[llen + rlen + 1] + lr.first * power10[rlen + 1] + rr.first * 10 + 9;
                                rmap[r % p] += lr.second * rr.second;
                            }
                        }
                    }
                }
            }
        }
        int count = 0;
        for (auto& r : results[(1 << n) - 1].first) {
            if (r.first == target) {
                count += r.second;
            }
        }
        return count;
    }

private:
    array<long long, 134> power10;
    array < vector<int>, 10 > masks;
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
    vector<int> gem = { 2, 3 };
    Solution s;
    auto actual = s.treeOfInfiniteSouls(gem, 100000007, 11391299);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, Test2)
{
    vector<int> gem = { 32,81,75,43 };
    //vector<int> gem = { 2,3,4,5 };
    Solution s;
    auto actual = s.treeOfInfiniteSouls(gem, 14591, 5395);
    //auto actual = s.treeOfInfiniteSouls(gem, 200000000000000000, 5395);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, Test3)
{
    vector<int> gem = { 941,831,772,84 };
    Solution s;
    auto actual = s.treeOfInfiniteSouls(gem, 5, 4);
    decltype(actual) expect = 120;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<int> gem = { 1, 2, 3, 4, 5, 6, 7, 8 };
    Solution s;
    auto actual = s.treeOfInfiniteSouls(gem, 90007, 12345);
    decltype(actual) expect = 221;
    EXPECT_EQ(expect, actual);
}
}

