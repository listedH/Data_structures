/*******************************************************************************
*
* FileName : hash_table.cpp
* Comment  : double linked hash table

*******************************************************************************/

#include <iostream>
#include <list>


using namespace std;

class HashTable {
private:
    static const int hashGroups = 13;
    std::list<std::pair<int, string>> table[hashGroups];
    int a{};
public:
    bool isEmpty() const;

    int hashFunction(int key);

    void insertItem(int key, string value);

    void removeItem(int key);

    void searchKey(int key);

    void searchValue(string value);

    void printTable();

    void loadIndex();
};

bool HashTable::isEmpty() const {
    int sum{};
    for (int i = {}; i < hashGroups; ++i) {
        sum += table[i].size();
    }
    if (!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) {
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];\
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            cout << "[WARNING] Key exists. Value replaced." << endl;
            break;
        }
    }
    if (!keyExists) {
        cell.emplace_back(key, value);
        this->a += 1;
    }
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];\
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr);
            cout << "[INFO] Item removed." << endl;
            this->a -= 1;
            break;
        }
    }
    if (!keyExists) {
        cout << "[WARNING] Item not found." << endl;
    }
}

void HashTable::printTable() {
    for (int i = 0; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;
        auto bItr = table[i].begin();
        cout << "table[" << i << "]" << endl;
        for (; bItr != table[i].end(); bItr++) {
            cout << "[INFO] key: " << bItr->first << " Value: " << bItr->second << endl;
        }
        cout << endl;
    }
}

void HashTable::searchKey(int key) {
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];\
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            cout << "[INFO] key: " << bItr->first << " Value: " << bItr->second << " found" << endl;
            break;
        }
    }
    if (!keyExists) {
        cout << "[WARNING] Item not found." << endl;
    }
}

void HashTable::searchValue(string value) {
    auto &cell = table[0];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->second == value) {
            keyExists = true;
            cout << "[INFO] key: " << bItr->first << " Value: " << bItr->second << " found" << endl;
            break;
        }
    }
    if (!keyExists) {
        cout << "[WARNING] Item not found." << endl;
    }
}


void HashTable::loadIndex() {
    double d = 1.0 * (this->a) / hashGroups;
    cout << "LoadIndex=" << d << endl;
}

int main() {
    HashTable HT;
    if (HT.isEmpty()) {
        cout << "normal" << endl;
    } else {
        cout << "abnormal" << endl;
    }
    HT.insertItem(7, "7");
    //    HT.printTable();
    HT.insertItem(42, "42");
    //    HT.printTable();
    HT.insertItem(25, "25");
    //    HT.printTable();
    HT.insertItem(70, "70");
    //    HT.printTable();
    HT.insertItem(14, "14");
    //    HT.printTable();
    HT.insertItem(38, "38");
    //    HT.printTable();
    HT.insertItem(8, "8");
    //    HT.printTable();
    HT.insertItem(21, "21");
    //    HT.printTable();
    HT.insertItem(34, "34");
    //    HT.printTable();
    HT.insertItem(11, "11");
    HT.printTable();
    HT.loadIndex();
    cout << "在一次失败的搜索中，最多查找slot数为3(table[8]最长)，平均查找slot数为(5*1+2+3)/13=10/13" << endl;
    cout << "在一次成功的搜索中，最多查找slot数为3(table[8]最长)，平均查找slot数为(7*1+2*2+1*3)/13=14/13" << endl;
    return 0;
}
