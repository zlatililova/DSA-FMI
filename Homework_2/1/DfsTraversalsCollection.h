#include <iostream>
#include <vector>

using namespace std;

/*
Done using help from https://cplusplus.com/reference/algorithm/next_permutation/
https://www.geeksforgeeks.org/tree-back-edge-and-cross-edges-in-dfs-of-graph/
https://github.com/Angeld55/Data_structures_and_algorithms_FMI/blob/main/GraphTraversals/traversals.cpp
and seminar notes
*/

class DfsTraversalsCollection{
public: 
    class DfsTraversal;
private:
    vector<vector<int>> adj;
    vector<DfsTraversal> allTraversals;
    int startNode;

    void init_dfs_traversals();
    const DfsTraversal operator[](size_t index) const;
    void dfs_rec(int curr,
    vector<unsigned>& visited,
    unordered_map<int, int>& parent,
    DfsTraversal& traversal);
    void gen_adj_list_permutations(size_t row, vector<vector<int>>& possibleTraversals);

public:
    using Edge = std::pair<int, int>;

    DfsTraversalsCollection(vector<vector<int>>& adjList, int start);

    class DfsTraversal{
    public:
        vector<Edge> getTreeEdges() const;
        vector<Edge> getBackEdges() const;
        vector<Edge> getCrossEdges() const;
        vector<Edge> getForwardEdges() const;  
        
        bool operator<(const DfsTraversal& other) const;
        friend std::ostream& operator<<(std::ostream& os, const DfsTraversal& g);

    private:
        DfsTraversal() = default;
        vector<int> traversal;
        vector<Edge> treeEdges;
        vector<Edge> backEdges;
        vector<Edge> forwardEdges;
        vector<Edge> crossEdges;
        friend void DfsTraversalsCollection::gen_adj_list_permutations(size_t row, vector<vector<int>>& possibleTraversals);
        friend void DfsTraversalsCollection::dfs_rec(int curr,
                                                    vector<unsigned>& visited,
                                                    unordered_map<int, int>& parent,
                                                    DfsTraversal& traversal);
    };

    class ConstDfsTraversalIterator{
    public:
        const DfsTraversal& operator*() const;
        ConstDfsTraversalIterator& operator++();
        ConstDfsTraversalIterator operator++(int);
        const DfsTraversal* operator->() const;
        bool operator==(const ConstDfsTraversalIterator& other) const;
        bool operator!=(const ConstDfsTraversalIterator& other) const;
    private:
        vector<DfsTraversal>& data;
        int _index;
        ConstDfsTraversalIterator(vector<DfsTraversal>& current, int index): data(current), _index(index) {};
        friend class DfsTraversalsCollection;
    };

    ConstDfsTraversalIterator cbegin();
    ConstDfsTraversalIterator cend();
    
};