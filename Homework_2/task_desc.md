# Task 1 : DFSTraversalsCollections

## Objective
Implement a class `DfsTraversalsCollection` that represents a collection of different Depth-First Search (DFS) traversals for an oriented, non-weighted, simple graph (not a multigraph). The vertices of the graph are indexed from `0` to `n - 1`, where `n` is the number of vertices.

---

### Implementation Requirements

#### Constructor
- The class must have a constructor that accepts a graph (as described) and a starting vertex index for the traversal.

#### Functionality
1. **`treeEdges()`**  
   Returns all tree edges from the DFS traversal.

2. **`crossEdges()`**  
   Returns all cross edges from the DFS traversal.

3. **`backEdges()`**  
   Returns all back edges from the DFS traversal.

4. **`forwardEdges()`**  
   Returns all forward edges from the DFS traversal.

5. **Overloaded `<<` operator**  
   Prints the vertices in their traversal order, separated by a space.

---

### Additional Requirements

1. **Iterator Support**  
   The class must provide an iterator to traverse all objects in the collection in **ascending order**.

2. **Traversal Comparison**  
   Provide a comparison operator for traversals based on lexicographical order:  
   Traversal `a1, a2, ..., an < b1, b2, ..., bn` if:  
   - `a1 < b1`  
   - or `(a1 == b1 and a2 < b2)`  
   - or `(a1 == b1, a2 == b2, and a3 < b3)`  
   - and so on.
  
### Example
```plaintext
Traversal 1: 0 1 2 3 
Tree: (0→1), (1→2), (1→3)
Back: (2→1), (3→0)
Forward: (0→2)
Cross: None

Traversal 2: 0 1 3 2 
Tree: (0→1), (1→3), (1→2)
Back: (3→0), (2→1)
Forward: (0→2)
Cross: None

Traversal 3: 0 2 1 3 
Tree: (0→2), (2→1), (1→3)
Back: (1→2), (3→0)
Forward: (0→1)
Cross: None
```

# Task 2 : Unordered Set

## Objective
Implement a template class `UnorderedSet` that represents a set. The templates should specify:
- The **type** of the set elements.
- The **hash function** used.

The set uses **separate chaining** for its internal hash table representation. Elements with the same hash must maintain consistent iteration order.

---

### Implementation Requirements

#### Basic Operations

1. **`void insert(const T& element)`**  
   Adds a new element to the set.  
   If the element already exists, no duplicate is added.

2. **`void remove(const T& element)`**  
   Removes the element corresponding to the given key if it exists.

3. **`void remove(iterator pos)`**  
   Removes the element at the position pointed to by the iterator.  
   After removal, the iterator becomes invalid and must handle future use safely.

4. **`iterator find(const T& element)`**  
   Returns an iterator to the element with the given key if it exists.  
   Returns an iterator to `end()` if the element is not found.

5. **`void clear()`**  
   Deletes all elements from the set, leaving it empty.

6. **`bool empty() const`**  
   Returns `true` if the set is empty, `false` otherwise.

7. **`size_type erase_if(Predicate predicate)`**  
   Removes all elements for which the predicate returns `true`.  
   A **predicate** is a function or object that takes an element and returns a boolean.

---

### Iterators
The class must provide iterators to traverse the set. Elements with the same hash should be consistent in order when iterating.
