//
// Created by Kurna on 2025/11/5.
//
#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode *children[26]{};
    bool isEnd;
    int prefixCnt;
    int wordCnt;

    TrieNode() {
        for (auto &i: children) {
            i = nullptr;
        }
        isEnd = false;
        prefixCnt = 0;
        wordCnt = 0;
    }

    ~TrieNode() {
        for (auto &i: children) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
    }
};

class Trie {
    TrieNode *root;

public:
    explicit Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string &word) {
        TrieNode *current = root;
        for (auto c : word) {
            int idx = c - 'a';
            if (current->children[idx] == nullptr) {
                current->children[idx] = new TrieNode();
            }
            current = current->children[idx];
            current->prefixCnt++;
        }
        current->isEnd = true;
        current->wordCnt++;
    }

    bool search(const string &word) {
        TrieNode *current = root;
        for (auto c : word) {
            int idx = c - 'a';
            if (current->children[idx] == nullptr) {
                return false;
            }
            current = current->children[idx];
        }
        // Only return true if this node marks the end of a word
        return current->isEnd; // previously returned true even for prefixes
    }

    bool startsWith(const string& prefix) {
        TrieNode *current = root;
        for (auto c : prefix) {
            int idx = c - 'a';
            if (current->children[idx] == nullptr) {
                return false;
            }
            current = current->children[idx];
        }
        return true;
    }
};

int main() {
    auto trie = Trie();
    trie.insert("apple");
    cout << trie.search("apple") << trie.search("app") << trie.startsWith("app");
    trie.insert("app");
    cout << trie.search("app") << endl;
    return 0;
}
