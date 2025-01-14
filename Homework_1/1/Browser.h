#pragma once
#include "MyString.h"

// MyString was taken from last year's OOP course: https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2007/MyString


class Browser {
    private:
        struct Tab{
            MyString url = "about:blank";
            int64_t timestamp = 0;
            Tab* next = nullptr;
            Tab* prev = nullptr;
            Tab(MyString url, int64_t ts): url(url), timestamp(ts){};
            Tab(int64_t ts): timestamp(ts){};

        };
        Tab* head;
        Tab* current;

        void free();
        void moveFrom(Browser&& other);
        void copyFrom(const Browser& other);
        Tab* merge(Tab* tabs1, Tab* tabs2, bool (*f)(Tab& t1, Tab&t2));
        Tab* getMid(Tab* list);
        Tab* mergeSort(Tab* list, bool (*f)(Tab&t1, Tab&t2));
    public:

        enum class SortType{
            TIME,
            URL,
        };

        Browser();
        ~Browser();
        Browser(const Browser& other);
        Browser& operator=(const Browser& other);
        Browser(Browser&& other);
        Browser& operator=(Browser&& other);

        void forward();
        void back();
        void go(MyString url);
        void insert(MyString url);
        void remove();
        void print();
        void sort(SortType sortBy);

};