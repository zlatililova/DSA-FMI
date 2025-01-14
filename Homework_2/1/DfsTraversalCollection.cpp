#pragma once
#include "DfsTraversalsCollection.h"

vector<DfsTraversalsCollection::Edge> DfsTraversalsCollection::DfsTraversal::getTreeEdges() const {
    return treeEdges;
}

vector<DfsTraversalsCollection::Edge> DfsTraversalsCollection::DfsTraversal::getBackEdges() const {
    return backEdges;
}

vector<DfsTraversalsCollection::Edge> DfsTraversalsCollection::DfsTraversal::getCrossEdges() const {
    return crossEdges;
}

vector<DfsTraversalsCollection::Edge> DfsTraversalsCollection::DfsTraversal::getForwardEdges() const {
    return forwardEdges;
}

void DfsTraversalsCollection::dfs_rec(
    int curr,
    vector<unsigned>& visited,
    unordered_map<int, int>& parent,
    DfsTraversal& trav
) {

    /*visited states: 0 - not visited, white
                      1 - visiting, grey
                      2 - visited, black
    */

    visited[curr] = 1; // Mark current node as visiting
    trav.traversal.push_back(curr);

    for (auto& neighbor : adj[curr]) {

        if (visited[neighbor] == 0) { // Tree Edge
            trav.treeEdges.push_back({curr, neighbor});
            parent[neighbor] = curr;
            dfs_rec(neighbor, visited, parent, trav);
        
        } else if (visited[neighbor] == 1) { // Back Edge
            trav.backEdges.push_back({curr, neighbor});

        } else if (visited[neighbor] == 2) { // Forward or Cross Edge
            int ancestor = neighbor;
            bool is_descendant = false;
            while (parent.find(ancestor) != parent.end()) {
                if(parent[ancestor] == -1){ //reached the begining node, no more parents
                    break;
                }
                if (parent[ancestor] == curr) {
                    is_descendant = true;
                    break;
                }
                ancestor = parent[ancestor];
            }

            if (is_descendant) {
                trav.forwardEdges.push_back({curr, neighbor});
            } else {
                trav.crossEdges.push_back({curr, neighbor});
            }
        }
    }

    visited[curr] = 2; // Mark current node as fully processed
}

void DfsTraversalsCollection::init_dfs_traversals() { 
    vector<vector<int>> possibleTrav;       
    gen_adj_list_permutations(0, possibleTrav);

}


void DfsTraversalsCollection::gen_adj_list_permutations(size_t row, vector<vector<int>>& possibleTraversals) {
    if (row == adj.size()) {

        std::vector<unsigned> visited(adj.size(), 0);
        std::unordered_map<int, int> parent;
        parent[startNode] = -1;

        DfsTraversal trav;

        dfs_rec(startNode, visited, parent, trav);

        if(std::find(possibleTraversals.begin(), possibleTraversals.end(), trav.traversal) == possibleTraversals.end()){ // the traversal is unique
            possibleTraversals.push_back(trav.traversal);
            allTraversals.push_back(trav);
        }
        return;
    }

    std::sort(adj[row].begin(), adj[row].end());

    do {
        gen_adj_list_permutations(row + 1, possibleTraversals);
    } while (std::next_permutation(adj[row].begin(), adj[row].end()));

}


DfsTraversalsCollection::DfsTraversalsCollection(vector<vector<int>>& adjList, int start){
    startNode = start;
    adj = adjList;
    init_dfs_traversals();
    sort(allTraversals.begin(), allTraversals.end(), [](DfsTraversalsCollection::DfsTraversal& lhs, DfsTraversalsCollection::DfsTraversal& rhs){
        return lhs < rhs;
    });
}

const DfsTraversalsCollection::DfsTraversal DfsTraversalsCollection::operator[](size_t index) const{
    return allTraversals[index];
}


std::ostream& operator<<(std::ostream& os, const DfsTraversalsCollection::DfsTraversal& trav){
    for(int v: trav.traversal){
        os << v << " ";
    }
    return os;
}

const DfsTraversalsCollection::DfsTraversal& DfsTraversalsCollection::ConstDfsTraversalIterator::operator*() const{
    return data[_index];
}

const DfsTraversalsCollection::DfsTraversal* DfsTraversalsCollection::ConstDfsTraversalIterator::operator->() const{
    return &(data[_index]);
}

DfsTraversalsCollection::ConstDfsTraversalIterator& DfsTraversalsCollection::ConstDfsTraversalIterator::operator++(){
    _index++;
    return *this;
}

DfsTraversalsCollection::ConstDfsTraversalIterator DfsTraversalsCollection::ConstDfsTraversalIterator::operator++(int){
    auto tmp = *this;
    ++(*this);
    return tmp;
}

bool DfsTraversalsCollection::ConstDfsTraversalIterator::operator==(const ConstDfsTraversalIterator& other) const {
    return _index == other._index && 
    data[_index].getTreeEdges() == other.data[other._index].getTreeEdges() &&
    data[_index].getBackEdges() == other.data[other._index].getBackEdges() &&
    data[_index].getForwardEdges() == other.data[other._index].getForwardEdges() &&
    data[_index].getCrossEdges() == other.data[other._index].getCrossEdges();

}

bool DfsTraversalsCollection::ConstDfsTraversalIterator::operator!=(const ConstDfsTraversalIterator& other) const {
    return !(*this == other);
}

DfsTraversalsCollection::ConstDfsTraversalIterator DfsTraversalsCollection::cbegin(){
    return ConstDfsTraversalIterator(allTraversals, 0);
}

DfsTraversalsCollection::ConstDfsTraversalIterator DfsTraversalsCollection::cend(){
    return ConstDfsTraversalIterator(allTraversals, allTraversals.size());
}

bool DfsTraversalsCollection::DfsTraversal::operator<(const DfsTraversalsCollection::DfsTraversal& other) const{
    return traversal < other.traversal;
}
