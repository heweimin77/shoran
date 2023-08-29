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

class Encrypter {
public:
    Encrypter(vector<char> &keys, vector<string> &values, vector<string> &dictionary)
    {
        for (int i = 0; i < keys.size(); ++i) {
            int k = keys[i] - 'a';
            k2vs[k] = values[i];
        }
        for (auto &s : dictionary) {
            ++results[encrypt(s)];
        }
    }

    string encrypt(string word1)
    {
        string result;
        for (auto ch : word1) {
            result += k2vs[ch - 'a'];
        }
        return result;
    }

    int decrypt(string word2)
    {
        return results[word2];
    }
private:
    string k2vs[26];
    unordered_map<string, int> results;
};

class Encrypter2 {
    class Dictionary {
    public:
        Dictionary()
        {
            fill(nexts, nexts + 26, nullptr);
        }
        void construct(const string &s)
        {
            Dictionary *now = this;
            for (auto c : s) {
                int k = c - 'a';
                if (now->nexts[k] == nullptr) {
                    now->nexts[k] = new Dictionary();
                }
                now = now->nexts[k];
            }
        }
        Dictionary *next(int k)
        {
            return nexts[k];
        }

    private:
        Dictionary *nexts[26];
    };

public:
    Encrypter2(vector<char> &keys, vector<string> &values, vector<string> &dictionary)
    {
        for (int i = 0; i < keys.size(); ++i) {
            int k = keys[i] - 'a';
            k2vs[k] = values[i];
            v2ks[values[i]].push_back(k);
        }
        for (auto &s : dictionary) {
            if (dicts.size() < s.size()) {
                dicts.resize(s.size());
            }
            dicts[s.size() - 1].construct(s);
        }
    }

    string encrypt(string word1)
    {
        //cout << "encrypt: " << word1 << endl;
        string result;
        for (auto ch : word1) {
            result += k2vs[ch - 'a'];
        }
        //cout << "encrypt finish: "  << endl;
        return result;
    }

    int decrypt(string word2)
    {
        //cout << "decrypt: " << word2 << endl;
        int n = word2.size() / 2;
        if (n > dicts.size()) return 0;
        vector<vector<int>> indexes;
        for (int i = 0; i < word2.size(); i += 2) {
            indexes.push_back(v2ks[word2.substr(i, 2)]);
        }
        int count = 0;
        function<void(int, Dictionary *)> traverse = [&](int now, Dictionary *dict) {
            if (dict == nullptr) return;
            if (now == indexes.size()) {
                ++count;
                return;
            }
            for (auto index : indexes[now]) {
                traverse(now + 1, dict->next(index));
            }
        };

        traverse(0, &dicts[n - 1]);
        //cout << "decrypt finish: "  << endl;
        return count;
    }
private:
    string k2vs[26];
    unordered_map<string, vector<int>> v2ks;
    vector<Dictionary> dicts;
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
    vector<char> keys = { 'a', 'b', 'c', 'd' };
    vector<string> values = { "ei", "zf", "ei", "am" };
    vector<string> dictionary = { "abcd", "acbd", "adbc", "badc", "dacb", "cadb", "cbda", "abad" };
    Encrypter en(keys, values, dictionary);
    EXPECT_EQ(string("eizfeiam"), en.encrypt("abcd"));
    EXPECT_EQ(2, en.decrypt("eizfeiam"));
}
TEST_F(TestSolution, TestMain)
{
    vector<char> keys = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    vector<string> values = { "aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa","aa" };
    vector<string> dictionary = { "abcd","acbd","adbc","badc","dacb","cadb","cbda","abad" };
    Encrypter en(keys, values, dictionary);
    EXPECT_EQ(string("aaaaaaaa"), en.encrypt("abcd"));
    EXPECT_EQ(8, en.decrypt("aaaaaaaa"));
}

}

