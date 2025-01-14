#pragma once
#include <iostream>

//the idea for the Bit handling was taken from Last year's OOP course: https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2010/Sets/DynamicSet
//the idea for the iterators was taken from this course's materials: https://github.com/Angeld55/Data_structures_and_algorithms_FMI/tree/main/Vector/iterator

class BoolVector
{
    friend class BitProxy;
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned size = 0;
    unsigned capacity = 0;
	const unsigned elementsInBucket = sizeof(uint8_t) * 8;

	void free();
	void copyFrom(const BoolVector& other);
    void moveFrom(BoolVector&& other);

	unsigned getBucketIndex() const;
    void resize();

public:
	BoolVector(); 
    BoolVector(unsigned n); 
	BoolVector(const BoolVector& other);
    BoolVector(BoolVector&& other);
	BoolVector& operator=(const BoolVector& other);
    BoolVector& operator=(BoolVector&& other);
	~BoolVector();

    class BitProxy{
        private: 
            uint8_t& bucket;
            unsigned bitIndex;
            uint8_t mask;
            friend class Iterator;
        public:
            BitProxy(uint8_t& bucket, unsigned bitIndex);
            operator bool() const;
            BitProxy& operator=(bool value);
    };

    class Iterator{
        public:

        Iterator(BoolVector* vec, unsigned index) : vec(vec), index(index) {}

            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);

            Iterator operator+(int off) const;
            Iterator operator-(int off) const;

            BitProxy operator->();
            bool operator->() const;
            BitProxy operator*();

            bool operator==(const Iterator& it) const;
            bool operator!=(const Iterator& it) const;

        private:
            BoolVector* vec;
            unsigned index;
            friend class BoolVector;
    };

    class Const_Iterator{
        public:

        Const_Iterator(const BoolVector* vec, unsigned index) : vec(vec), index(index) {}

            Const_Iterator& operator++();
            Const_Iterator operator++(int);
            Const_Iterator& operator--();
            Const_Iterator operator--(int);

            Const_Iterator operator+(int off) const;
            Const_Iterator operator-(int off) const;

            bool operator->() const;
            bool operator*() const;

            bool operator==(const Const_Iterator& it) const;
            bool operator!=(const Const_Iterator& it) const;

        private:
            const BoolVector* vec;
            unsigned index;
            friend class BoolVector;
    };

    class Reverse_Iterator{
        public:

        Reverse_Iterator(BoolVector* vec, unsigned index): it(Iterator(vec, index)) {};

            Reverse_Iterator& operator++();
            Reverse_Iterator operator++(int);
            Reverse_Iterator& operator--();
            Reverse_Iterator operator--(int);

            Reverse_Iterator operator+(int off) const;
            Reverse_Iterator operator-(int off) const;

            BitProxy operator->();
            bool operator->() const;
            BitProxy operator*();

            bool operator==(const Reverse_Iterator& iter) const;
            bool operator!=(const Reverse_Iterator& iter) const;

        private:
            Iterator it;
            friend class BoolVector;
    };


    Iterator begin();
    Iterator end();

    Const_Iterator cbegin() const;
    Const_Iterator cend() const;

    Reverse_Iterator rev_begin();
    Reverse_Iterator rev_end();
 
    void push_back(bool value);
    void pop_back();
    void insert(Iterator it, bool value);
    void remove(Iterator it);
    void pop_front();

    bool operator[](unsigned index) const;
    BitProxy operator[](unsigned index);
};