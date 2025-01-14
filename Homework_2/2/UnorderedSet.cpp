#pragma once
#include "UnorderedSet.h"

template <typename Key, typename Hash>
size_t Unordered_Set<Key,Hash>::getHashCode(const Key &key) const
{
    return getHash(key) % hashTable.size();
}

template <typename Key, typename Hash>
Unordered_Set<Key,Hash>::Unordered_Set()
{
    hashTable.resize(5, data.end());
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::insert(const Key &key)
{
    size_t hashCode = getHashCode(key);

    auto &bucket = hashTable[hashCode];

    if (bucket != data.end())
    {
        for (auto it = bucket; it != data.end() && getHashCode(*it) == hashCode; ++it)
        {
            if (*it == key)
            {
                return;
            }
        }
    }
    else
    {
        data.push_back(key);
        auto iter = --data.end();
        hashTable[hashCode] = iter;
        return;
    }

    data.insert(bucket, key);
    bucket--;
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::remove(const Key& key) {
    

    auto it = std::find(data.begin(), data.end(), key);
    if (it != data.end()) {
        handleBucketRemoval(key);
        data.erase(it);
    }
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::handleBucketRemoval(Key key){
    size_t hashCode = getHashCode(key);
    auto& bucket = hashTable[hashCode];

    if (*bucket == key) {
        bucket++;
        if (bucket == data.end() || getHashCode(*bucket) != hashCode) {
            bucket = data.end(); 
        }
    }
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::remove(ConstIterator& it) {
    if(it == cend()){
        return;
    }
    remove(*it);
    it = cend();
}

template <typename Key, typename Hash>
bool Unordered_Set<Key,Hash>::empty() const {
    return data.size() == 0;
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::clear(){
    data.clear();
    hashTable.assign(5, data.end());
}

template <typename Key, typename Hash>
void Unordered_Set<Key,Hash>::erase_if( bool (*pred)(int)){
     for (auto it = data.begin(); it != data.end(); ) {
        if (pred(*it)) {
            handleBucketRemoval(*it);
            it = data.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename Key, typename Hash>
const Key& Unordered_Set<Key,Hash>::ConstIterator::operator*() const {
    return *currElement;
}

template <typename Key, typename Hash>
const Key* Unordered_Set<Key,Hash>::ConstIterator::operator->() const {
    return &(*currElement);
}

template <typename Key, typename Hash>
bool Unordered_Set<Key,Hash>::ConstIterator::operator==(const ConstIterator& other) const {
    return currElement == other.currElement;
}

template <typename Key, typename Hash>
bool Unordered_Set<Key,Hash>::ConstIterator::operator!=(const ConstIterator& other) const {
    return currElement != other.currElement;
}

template <typename Key, typename Hash>
typename Unordered_Set<Key,Hash>::ConstIterator& Unordered_Set<Key,Hash>::ConstIterator::operator++(){
    ++currElement;
    return *this;
}

template <typename Key, typename Hash>
typename Unordered_Set<Key,Hash>::ConstIterator Unordered_Set<Key,Hash>::ConstIterator::operator++(int){
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template <typename Key, typename Hash>
typename Unordered_Set<Key,Hash>::ConstIterator Unordered_Set<Key,Hash>::cbegin() const{
    return ConstIterator(data.cbegin());
}

template <typename Key, typename Hash>
typename Unordered_Set<Key,Hash>::ConstIterator Unordered_Set<Key,Hash>::cend() const{
    return ConstIterator(data.cend());
}

template <typename Key, typename Hash>
typename Unordered_Set<Key,Hash>::ConstIterator Unordered_Set<Key,Hash>::find(const Key& key) const {
    size_t hashCode = getHashCode(key);
    auto &bucket = hashTable[hashCode];

    if (bucket != data.end())
    {
        for (auto it = bucket; it != data.end() && getHashCode(*it) == hashCode; ++it)
        {
            if (*it == key)
            {
                return ConstIterator(it);
            }
        }
    }
    
    return cend();
}
