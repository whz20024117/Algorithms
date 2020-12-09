#include <functional>
#include <list>
#include <vector>
#include <iostream>


class HT
{
    std::vector<std::list<std::pair<int, int>>> hashTable;
    int size = 50;
    std::hash<int> hashfunc{};
public:

    HT()
    : hashTable(50), size(50)
    {
        
    }

    int& insert(int key, int value)
    {
        int hash_key = hashfunc(key) % size;
        auto& item = hashTable[hash_key];
        
        auto ret = std::make_pair(key, value);
        item.push_back(ret);
        
        return item.back().second;
    }

    int& operator[](const int& key)
    {
        int hash_key = hashfunc(key) % size;
        auto& item = hashTable[hash_key];

        for (auto it=item.begin(); it != item.end(); it++)
        {
            if (it->first == hash_key)
                return it->second;
        }
        return insert(key, 0);
    }
};


int main()
{
    HT ht;

    ht.insert(0, 10);
    ht.insert(1, 20);
    ht.insert(2, 30);

    std::cout<< ht[0] << ht[1] << ht[2] << std::endl;

    return 0;
}