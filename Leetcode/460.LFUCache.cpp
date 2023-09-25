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

class LFUCache {
    using KVS = list<pair<int, int>>;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto it = keys.find(key);
        if (it == keys.end()) return -1;
        KVS::iterator jt = *(it->second.second);
        int count = it->second.first;
        counts[count].erase(it->second.second);
        if (counts[count].empty()) counts.erase(count);
        auto& cnts = counts[count + 1];
        it->second.first = count + 1;
        it->second.second = cnts.insert(cnts.end(), jt);
        return jt->second;
    }

    void put(int key, int value) {
        auto it = keys.find(key);
        if (it == keys.end()) {
            if (capacity == data.size()) {
                auto icnt = counts.begin();
                auto &klist = icnt->second;
                int key = (*klist.begin())->first;
                data.erase(*klist.begin());
                klist.erase(klist.begin());
                if (klist.empty()) counts.erase(counts.begin());
                keys.erase(key);
            }
            auto it = data.insert(data.end(), { key, value });
            auto jt = counts[1].insert(counts[1].end(), it);
            keys[key] = { 1, jt };
        } else {

            KVS::iterator jt = *(it->second.second);
            int count = it->second.first;
            counts[count].erase(it->second.second);
            if (counts[count].empty()) counts.erase(count);
            auto& cnts = counts[count + 1];
            it->second.first = count + 1;
            it->second.second = cnts.insert(cnts.end(), jt);
            jt->second = value;
        }
    }

private:
    KVS data;
    map<int, list<KVS::iterator>> counts;
    unordered_map<int, pair<int, list<KVS::iterator>::iterator>> keys;
    int capacity;

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
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    EXPECT_EQ(1, lfu.get(1));
    lfu.put(3, 3);
    EXPECT_EQ(-1, lfu.get(2));
    EXPECT_EQ(3, lfu.get(3));

    lfu.put(4, 4);
    EXPECT_EQ(-1, lfu.get(1));
    EXPECT_EQ(3, lfu.get(3));
    EXPECT_EQ(4, lfu.get(4));
}
}
