#include "boolvector.h"

BoolVector::BoolVector(unsigned capacity)
{
    bucketsCount = capacity / elementsInBucket + 1;
    buckets = new uint8_t[bucketsCount]{0};
    this->capacity = capacity;
}

BoolVector::BoolVector()
{
    bucketsCount = 1;
    buckets = new uint8_t[bucketsCount]{0};
    this->capacity = elementsInBucket;
}

void BoolVector::free()
{
    delete[] buckets; //!!!
    bucketsCount = size = capacity = 0;
    buckets = nullptr;
}

void BoolVector::copyFrom(const BoolVector &other)
{
    buckets = new uint8_t[other.bucketsCount];
    for (size_t i = 0; i < other.bucketsCount; i++)
        buckets[i] = other.buckets[i];
    bucketsCount = other.bucketsCount;
    size = other.size;
    capacity = other.capacity;
}

void BoolVector::moveFrom(BoolVector &&other)
{
    buckets = other.buckets;
    other.buckets = nullptr;
    bucketsCount = other.bucketsCount;
    size = other.size;
    capacity = other.capacity;
    other.size = other.capacity = other.bucketsCount = 0;
}

BoolVector::BoolVector(const BoolVector &other)
{
    copyFrom(other);
}

BoolVector::BoolVector(BoolVector &&other)
{
    moveFrom(std::move(other));
}

BoolVector &BoolVector::operator=(BoolVector &&other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

BoolVector &BoolVector::operator=(const BoolVector &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

BoolVector::~BoolVector()
{
    free();
}

unsigned BoolVector::getBucketIndex() const
{
    return size / elementsInBucket;
}

void BoolVector::resize()
{
    unsigned newBucketsCount = bucketsCount * 2;
    uint8_t *newBuckets = new uint8_t[newBucketsCount];
    for (unsigned i = 0; i < bucketsCount; i++)
    {
        newBuckets[i] = buckets[i];
    }
    delete[] buckets;
    buckets = newBuckets;
    bucketsCount = newBucketsCount;
    capacity *= 2;
}

void BoolVector::push_back(bool value)
{
    if (size == capacity)
    {
        resize();
    }
    if (!value)
    {
        size++;
        return;
    }

    unsigned bucketIndex = getBucketIndex();
    unsigned bitIndex = size % elementsInBucket;

    uint8_t mask = 1 << bitIndex;
    buckets[bucketIndex] |= mask;

    size++;
}

void BoolVector::pop_back()
{
    if (size == 0)
    {
        return;
    }

    unsigned bucketIndex = getBucketIndex();
    unsigned bitIndex = size % elementsInBucket;

    uint8_t mask = 1 << bitIndex;
    mask = ~mask;
    buckets[bucketIndex] &= mask;
    size--;
}

void BoolVector::pop_front()
{

    if (size == 0)
    {
        return;
    }
    buckets[0] >>= 1;

    for (unsigned i = 1; i < bucketsCount; ++i)
    {
        uint8_t carry_in = (buckets[i] >> (elementsInBucket - 1)) & 1;

        buckets[i] >>= 1;
        buckets[i] |= (carry_in << (elementsInBucket - 1));
    }

    size--;
}

bool BoolVector::operator[](unsigned index) const
{
    unsigned bucketInd = index / elementsInBucket;
    unsigned bitIndex = index % elementsInBucket;

    uint8_t mask = 1 << bitIndex;
    unsigned res = buckets[bucketInd] & mask;

    if (res)
        return true;
    else
        return false;
}

BoolVector::BitProxy BoolVector::operator[](unsigned index)
{

    unsigned bucketIndex = index / elementsInBucket;
    unsigned bitIndex = index % elementsInBucket;
    return BitProxy(buckets[bucketIndex], bitIndex);
}

BoolVector::BitProxy::BitProxy(uint8_t &bucket, unsigned bitIndex) : bucket(bucket), bitIndex(bitIndex)
{
    mask = 1 << bitIndex;
}

BoolVector::BitProxy::operator bool() const
{

    unsigned res = bucket & mask;

    if (res)
        return true;
    else
        return false;
}

BoolVector::BitProxy &BoolVector::BitProxy::operator=(bool value)
{
    if (value)
        bucket |= mask;
    else
        bucket &= ~mask;
    return *this;
}

BoolVector::Iterator &BoolVector::Iterator::operator++()
{
    ++index;
    if (index > vec->size)
    {
        index = vec->size;
    }
    return *this;
}

BoolVector::Iterator BoolVector::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

BoolVector::Iterator &BoolVector::Iterator::operator--()
{ // Prefix decrement
    --index;
    return *this;
}

BoolVector::Iterator BoolVector::Iterator::operator--(int)
{ // Postfix decrement
    Iterator temp = *this;
    --(*this);
    return temp;
}

BoolVector::Iterator BoolVector::Iterator::operator+(int off) const
{
    return Iterator(vec, index + off);
}

BoolVector::Iterator BoolVector::Iterator::operator-(int off) const
{
    return Iterator(vec, index - off);
}

bool BoolVector::Iterator::operator==(const Iterator &it) const
{
    return vec == it.vec && index == it.index;
}

bool BoolVector::Iterator::operator!=(const Iterator &it) const
{
    return !(*this == it);
}

BoolVector::BitProxy BoolVector::Iterator::operator*() { return (*vec)[index]; }

BoolVector::BitProxy BoolVector::Iterator::operator->() { return (*vec)[index]; }
bool BoolVector::Iterator::operator->() const { return (*vec)[index]; }

BoolVector::Iterator BoolVector::begin()
{
    return Iterator(this, 0);
}

BoolVector::Iterator BoolVector::end()
{
    return Iterator(this, size);
}
void BoolVector::remove(Iterator it)
{
    if (it.index >= size)
    {
        return;
    }

    for (unsigned i = it.index; i < size; ++i)
    {
        bool nextBit = operator[](i + 1);
        operator[](i) = nextBit;
    }
    size--;
}

void BoolVector::insert(Iterator it, bool value)
{
    if (it.index >= size)
    {
        return;
    }
    if (size == capacity)
    {
        resize();
    }
    for (unsigned i = size; i >= it.index; --i)
    {
        bool currBit = operator[](i);
        operator[](i + 1) = currBit;
    }

    operator[](it.index) = value;

    size++;
}

BoolVector::Const_Iterator &BoolVector::Const_Iterator::operator++()
{
    ++index;
    if (index > vec->size)
    {
        index = vec->size;
    }
    return *this;
}

BoolVector::Const_Iterator BoolVector::Const_Iterator::operator++(int)
{
    Const_Iterator temp = *this;
    ++(*this);
    return temp;
}

BoolVector::Const_Iterator &BoolVector::Const_Iterator::operator--()
{
    --index;
    return *this;
}

BoolVector::Const_Iterator BoolVector::Const_Iterator::operator--(int)
{
    Const_Iterator temp = *this;
    --(*this);
    return temp;
}

BoolVector::Const_Iterator BoolVector::Const_Iterator::operator+(int off) const
{
    return Const_Iterator(vec, index + off);
}

BoolVector::Const_Iterator BoolVector::Const_Iterator::operator-(int off) const
{
    return Const_Iterator(vec, index - off);
}

bool BoolVector::Const_Iterator::operator==(const Const_Iterator &it) const
{
    return vec == it.vec && index == it.index;
}

bool BoolVector::Const_Iterator::operator!=(const Const_Iterator &it) const
{
    return !(*this == it);
}

bool BoolVector::Const_Iterator::operator*() const
{
    return (*vec)[index];
}

bool BoolVector::Const_Iterator::operator->() const
{
    return (*vec)[index];
}

BoolVector::Const_Iterator BoolVector::cbegin() const
{
    return Const_Iterator(this, 0);
}

BoolVector::Const_Iterator BoolVector::cend() const
{
    return Const_Iterator(this, size);
}

BoolVector::Reverse_Iterator &BoolVector::Reverse_Iterator::operator++()
{
    --it;
    return *this;
}

BoolVector::Reverse_Iterator BoolVector::Reverse_Iterator::operator++(int)
{
    Reverse_Iterator temp = *this;
    ++(*this);
    return temp;
}

BoolVector::Reverse_Iterator &BoolVector::Reverse_Iterator::operator--()
{ // Prefix decrement
    ++it;
    return *this;
}

BoolVector::Reverse_Iterator BoolVector::Reverse_Iterator::operator--(int)
{ // Postfix decrement
    Reverse_Iterator temp = *this;
    --(*this);
    return temp;
}

BoolVector::Reverse_Iterator BoolVector::Reverse_Iterator::operator+(int off) const
{
    return Reverse_Iterator(it.vec, it.index - off);
}

BoolVector::Reverse_Iterator BoolVector::Reverse_Iterator::operator-(int off) const
{
    return Reverse_Iterator(it.vec, it.index + off);
}

bool BoolVector::Reverse_Iterator::operator==(const Reverse_Iterator &iter) const
{
    return this->it == iter.it;
}

bool BoolVector::Reverse_Iterator::operator!=(const Reverse_Iterator &iter) const
{
    return !(*this == iter);
}

BoolVector::BitProxy BoolVector::Reverse_Iterator::operator*()
{
    return *it;
}

BoolVector::BitProxy BoolVector::Reverse_Iterator::operator->() {
    return it.operator->(); 
}
bool BoolVector::Reverse_Iterator::operator->() const {
    return it.operator->();
}

BoolVector::Reverse_Iterator BoolVector::rev_begin()
{
    return Reverse_Iterator(this, size-1);
}

BoolVector::Reverse_Iterator BoolVector::rev_end()
{
    return Reverse_Iterator(this, 0);
}