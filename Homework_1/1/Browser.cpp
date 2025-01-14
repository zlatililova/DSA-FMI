#include "Browser.h"
#include "MyString.cpp"

//taken from the internet
int64_t getTimestamp() {
	auto now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}

Browser::Browser(){
    Tab* blank = new Tab(getTimestamp());
    head = current = blank;
}

void Browser::free(){
    Tab* curr = head;
    while(curr){
        Tab* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}

void Browser::moveFrom(Browser&& other){
    this->head = other.head;
    this->current = other.current;
    other.head = other.current = nullptr;
}

void Browser::copyFrom(const Browser& other){
    this->head = new Tab(other.head->url, other.head->timestamp);
    Tab* toAdd = other.head->next;
    Tab* curr = head;

    while(toAdd){
        Tab* newTab = new Tab(toAdd->url, toAdd->timestamp);
        if(toAdd == other.current){
            this->current = newTab;
        }
        newTab->prev = curr;
        curr->next = newTab;
        curr = curr->next;
        toAdd = toAdd->next;
    }

}

Browser::Browser(const Browser &other)
{
    copyFrom(other);
}

Browser::Browser(Browser &&other)
{
    moveFrom(std::move(other));
}

Browser &Browser::operator=(Browser &&other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Browser &Browser::operator=(const Browser &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Browser::~Browser(){
    free();
}

void Browser::forward(){
    if(current->next)
        current = current->next;
}

void Browser::back(){
    if(current->prev)
        current = current->prev;
}

void Browser::insert(MyString url){
    Tab* newTab = new Tab(url, getTimestamp());
    newTab->next = current->next;
    newTab->prev = current;
    if(current->next)
        current->next->prev = newTab;
    current->next = newTab;
    current = newTab;

}

void Browser::remove(){
    Tab* toRemove = current;

    if(!current->prev && !current->next){ //this was the only tab available
        current = new Tab(getTimestamp());
    }
    else if(current->prev && !current->next){ // no tab after this
        current = current->prev;
        current-> next = nullptr;
    }
    else {
        current = current->next;
        current->prev = toRemove->prev;
        toRemove->prev->next = current;        
    }

    delete toRemove;
}

void Browser::go(MyString url){
    current->url = url;
    current->timestamp = getTimestamp();
}

void Browser::print(){
    Tab* curr = head;
    while(curr){
        if(curr == current){
            std::cout << "> ";
        }
        std::cout << curr->url << " " << curr->timestamp <<std::endl;
        curr = curr->next;
    }
}

Browser::Tab* Browser::merge(Tab* tabs1, Tab* tabs2, bool (*f)(Tab& t1, Tab&t2)){

    Tab* result = nullptr;
    Tab* head = nullptr;

    while(tabs1 && tabs2){
        if(f(*tabs1, *tabs2)){
            if(!head){
                result = tabs1;
                head = result;
                tabs1 = tabs1->next;
            }else{
                result->next = tabs1;
                tabs1->prev = result;
                result = result->next; 
                tabs1 = tabs1->next;
            }
        } else {
            if(!head){
                result = tabs2;
                head = result;
                tabs2 = tabs2->next;
            }else{
                result->next = tabs2;
                tabs2->prev = result;
                result = result->next; 
                tabs2 = tabs2->next;
            }
        }
    }

    if(tabs1){
        result->next = tabs1;
        tabs1->prev = result;
    }
    if(tabs2){
        result->next = tabs2;
        tabs2->prev = result;
    }

    return head;
}


//based on https://github.com/Angeld55/Data_structures_and_algorithms_FMI/blob/main/Miscellaneous/singlyLinkedList_mergeSort.cpp
Browser::Tab* Browser::getMid(Tab* list)
{
    Tab* slow = list;
    Tab* fast = list ->next;
    
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// based on https://github.com/Angeld55/Data_structures_and_algorithms_FMI/blob/main/Miscellaneous/singlyLinkedList_mergeSort.cpp
Browser::Tab* Browser::mergeSort(Tab* list, bool (*f)(Tab&t1, Tab&t2))
{
    
    if(!list || !list->next) 
        return list;
        
    Tab* mid = getMid(list);

        
    Tab* left = list;
    Tab* right = mid->next;
    mid->next = nullptr;
    
    left = mergeSort(left, f);
    right = mergeSort(right, f);
    
    return merge(left, right, f);
}

void Browser::sort(SortType sortBy){
    if(sortBy == SortType::TIME){
        head = mergeSort(head, [](Tab&t1, Tab&t2){
            if(t1.timestamp == t2.timestamp){
                return t1.url < t2.url;
            }
            return t1.timestamp < t2.timestamp;
        });
    }

    if(sortBy == SortType::URL){
        head = mergeSort(head, [](Tab&t1, Tab&t2){
            if(t1.url == t2.url){
                return t1.timestamp < t2.timestamp;
            }
            return t1.url < t2.url;
        });
    }
    current = head;

}