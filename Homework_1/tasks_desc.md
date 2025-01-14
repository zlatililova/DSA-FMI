# Task 1: Browser Tab Module

## Problem Description
You are tasked with implementing a **browser tab module** where each tab has a **URL** (a string) and a **timestamp** (a Unix timestamp as an integer). The user interacts with tabs through a set of commands. At any given moment, one tab is designated as the **current tab**. Your solution should handle various operations related to tab management efficiently using custom data structures without relying on built-in containers.

---

## Requirements
1. **Command Interface**: The browser supports the following commands:
   - **GO <url>**: Loads the page at the specified URL in the current tab, updating its timestamp.
   - **INSERT <url>**: Opens a new tab after the current one, loads the URL, and makes it the current tab.
   - **BACK**: Moves to the previous tab if it exists.
   - **FORWARD**: Moves to the next tab if it exists.
   - **REMOVE**: Closes the current tab and adjusts the current tab as specified.
   - **PRINT**: Displays all tabs, marking the current tab with a `>` symbol.
   - **SORT <by>** *(Optional)*: Sorts tabs lexicographically by URL or timestamp, keeping the sorted first tab as the current one.

2. **Startup and Default State**:  
   - The browser starts with one tab (`about:blank`).
   - If only one tab is open and removed, a new tab is created with `about:blank`.

3. **Data Structures and Algorithms**:  
   Implement your own data structure(s) and sorting algorithms. Avoid using built-in containers.

---

## Example Commands
### Input
```plaintext
GO www.youtube.com/watch?v=dQw4w9WgXcQ
INSERT www.google.bg/search?q=google+plz+help+me+solve+my+data+structures+task
INSERT www.9gag.com/gag/aAV83g9/when-you-realise-today-is-the-homework-assignment-deadline
INSERT www.en.wikipedia.org/wiki/Data_structure
BACK
BACK
REMOVE
PRINT
www.youtube.com/watch?v=dQw4w9WgXcQ 150676023
>www.9gag.com/gag/aAV83g9/when-you-realise-today-is-the-homework-assignment-deadline 150670593
www.en.wikipedia.org/wiki/Data_structure 150700011
```
### Input
```plaintext
GO www.youtube.com/watch?v=dQw4w9WgXcQ
INSERT www.en.wikipedia.org/wiki/Data_structure
INSERT www.wikihow.com/Deal-With-Tons-of-Homework
INSERT www.susi.uni-sofia.bg
SORT URL
PRINT
>www.en.wikipedia.org/wiki/Data_structure 150700011
www.susi.uni-sofia.bg 163750320
www.wikihow.com/Deal-With-Tons-of-Homework 150787241
www.youtube.com/watch?v=dQw4w9WgXcQ 150676023
```
###Notes
	•	Choose data structures that optimize tab manipulation.
	•	Handle memory efficiently while following good coding practices.
	•	Sorting should account for ties in URL and timestamp.

# Task 2 : Bool Vector

## Objective
Implement a specialized version of the `Vector` class template for storing boolean values (`bool`). This class must optimize memory usage by representing each boolean value using only **one bit**.

---

### Implementation Requirements

#### Methods for Adding and Removing Elements
1. **`void push_back(value)`**  
   Adds an element to the end of the vector.

2. **`void pop_back()`**  
   Removes the last element in the vector.

3. **`void insert(iterator, value)`**  
   Inserts an element at the position specified by the iterator.

4. **`void remove(iterator)`**  
   Removes an element from the position specified by the iterator.

5. **`void pop_front()`**  
   Removes the first element in the vector.

---

### Indexing
- Overload the `[]` operator to access and modify elements by index.  
- Provide both constant and non-constant versions.

---

### Iterators
The class must provide iterators that allow traversal of all elements in the vector with support for:
- **Increment (`++`)**  
- **Decrement (`--`)**  
- **Dereference (`*`)**  
- **Comparison (`!=`, `==`)**  

At least the following iterator types are required:
- `iterator`
- `const_iterator`
- `reverse_iterator`

---

### Memory Optimization
- Implement bit-level storage so that each boolean value occupies only **one bit** to minimize memory usage.
