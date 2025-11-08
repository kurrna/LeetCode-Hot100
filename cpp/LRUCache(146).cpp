//
// Created by Kurna on 25-11-1.
//
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename K, typename V>
class LRUCache {
    int capacity;
    int size;
    using ListIter = typename std::list<K>::iterator;
    std::unordered_map<K, std::pair<V, ListIter> > cache_map;
    std::list<K> access_list;

public:
    explicit LRUCache(int _capacity) : capacity(_capacity), size(0) {
        cache_map = unordered_map<int, pair<int, ListIter> >(_capacity);
        access_list = list<int>();
    }

    V get(K key) {
        auto it = cache_map.find(key);
        if (it != cache_map.end()) {
            auto list_it = it->second.second;
            access_list.splice(access_list.begin(), access_list, list_it);
            return it->second.first;
        }
        return -1;
    }

    void put(K key, V value) {
        auto it = cache_map.find(key);
        if (it != cache_map.end()) {
            // old
            auto list_it = it->second.second;
            access_list.splice(access_list.begin(), access_list, list_it);
            if (value != it->second.first) {
                cache_map[key] = pair(value, list_it);
            }
        } else {
            // new
            if (++size > capacity) {
                access_list.push_front(key);
                auto list_it = access_list.begin();
                cache_map[key] = pair(value, list_it);
                size = capacity;
                cache_map.erase(access_list.back());
                access_list.pop_back();
            } else {
                access_list.push_front(key);
                auto list_it = access_list.begin();
                cache_map[key] = pair(value, list_it);
            }
        }
    }
};
int main() {
    ifstream inputFile("C:/Users/Kurna/Desktop/hot100/src/input.txt");
    string line1, line2;
    getline(inputFile, line1);
    getline(inputFile, line2);

    stringstream ss1(line1);
    stringstream ss2(line2);
    string segment;
    vector<string> operations;
    vector<vector<int> > values;

    while (getline(ss1, segment, ',')) {
        operations.push_back(segment);
    }
    operations[0] = operations[0].substr(2, operations[0].length() - 3);
    for (size_t i = 1; i < operations.size(); ++i) {
        operations[i] = operations[i].substr(1, operations[i].length() - 2);
    }
    operations.back() = operations.back().substr(0, operations.back().length() - 1);

    ss2.get(); // Consume the first '['
    while (ss2.peek() != ']') {
        if (ss2.peek() == ',') {
            ss2.get(); // Consume ','
        }
        ss2.get(); // Consume '['
        string item;
        getline(ss2, item, ']');
        stringstream item_ss(item);
        vector<int> temp_values;
        string val_str;
        while (getline(item_ss, val_str, ',')) {
            if (!val_str.empty()) {
                temp_values.push_back(stoi(val_str));
            }
        }
        values.push_back(temp_values);
    }

    LRUCache<int, int> *obj = nullptr;

    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i] == "LRUCache") {
            obj = new LRUCache<int, int>(values[i][0]);
            cout << "null,";
        } else if (operations[i] == "put") {
            obj->put(values[i][0], values[i][1]);
            cout << "null,";
        } else if (operations[i] == "get") {
            int res = obj->get(values[i][0]);
            cout << res << ",";
        }
    }
    cout << endl;

    delete obj;
    return 0;
}
