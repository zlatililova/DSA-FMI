#include <list>
#include <iostream>
#include <vector>

using namespace std;

//Done using help from 
//https://github.com/Angeld55/Data_structures_and_algorithms_FMI/blob/main/SeparateChainingHash_InsertionOrder/InsertionOrderHashMap.hpp
//and seminar notes

template <typename Key, typename Hash = std::hash<Key>>
class Unordered_Set{
    private: 
        list<Key> data;
        vector<typename list<Key>::iterator> hashTable;   
        Hash getHash;
        size_t getHashCode(const Key& key) const;
        void handleBucketRemoval(Key key);

    public:

        class ConstIterator 
        {
        public:
            const Key& operator*() const;
            ConstIterator& operator++();
            ConstIterator operator++(int);
            const Key* operator->() const;
            bool operator==(const ConstIterator& other) const;
            bool operator!=(const ConstIterator& other) const;

        private:
            typename std::list<Key>::const_iterator currElement;
            ConstIterator(typename std::list<Key>::const_iterator curr): currElement(curr) {};
        };

        Unordered_Set(); 
        void insert(const Key& key); 
        void remove(const Key& key);
        void clear();
        bool empty() const;

        void remove(ConstIterator& it);
        ConstIterator find(const Key& key) const;
        void erase_if(bool(*pred)(int));

        ConstIterator cbegin() const;
        ConstIterator cend() const;

};