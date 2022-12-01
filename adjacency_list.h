//----------------------------------------------------------------------
// FILE: adjacency_list.h
// AUTH: Zach Sahlin
// DATE: Fall 2022
// DESC: Represents a graph as an adjacency list
//----------------------------------------------------------------------


#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <set>
#include <list>
#include <algorithm>
#include "graph.h"


template<typename T>
class AdjacencyList : public Graph<T>
{
public:
  
  // constructor that creates a graph with n nodes
  AdjacencyList(int n, bool is_directed);
  
  // Returns true if the graph is directed and false otherwise. Note
  // that an edge (x,y) in an undirected graph always has a
  // corresponding edge (y,x). Since both (x,y) and (y,x) in an
  // undirected graph count as a single edge, these edges count as 1
  // edge towards the given edge count.
  bool is_directed() const;

  // Returns true if the graph has the edge (x,y) and false otherwise.
  bool has_edge(int x, int y) const;

  // Adds the edge (x,y) to the graph and assigns the edge the given
  // (optional) label. If the edge already exists in the graph, this
  // function does nothing.
  void add_edge(int x, std::optional<T> label, int y);

  // Removes the edge (x,y) from the graph. If the edge is not present
  // in the graph, the function does nothing.
  void rem_edge(int x, int y);

  // Returns the corresponding label of the edge (x,y). If the edge
  // doesn't exist in the graph, the optional value returned is false.
  std::optional<T> get_label(int x, int y) const;

  // Sets the label of the edge (x,y) to label. If edge (x,y) isn't in
  // the graph, this function does nothing. 
  void set_label(int x, const T& label, int y);

  // Returns the list of nodes that x is connected to on its outgoing
  // edges (i.e., the direct successors of x).  
  std::vector<int> out_nodes(int x) const;

  // Returns the list of nodes that x is connected to on its incoming
  // edges (i.e., the direct predecessors of x).
  std::vector<int> in_nodes(int x) const;

  // Returns the list of nodes that x is connected to. In a directed
  // graph, should return the union of the nodes on outgoing and
  // incoming edges.
  std::vector<int> adjacent(int x) const;

  // Returns the total number of nodes in the graph.
  int node_count() const;

  // Returns the total number of edges in the graph. In a directed
  // graph, it returns the total number of directed edges. In an
  // undirected graph, it returns the total number of undirected
  // edges.
  int edge_count() const;

private:
  // the total number of nodes and edges
  int nodes;
  int edges;

  // true if the graph is directed
  bool directed;

  // underlying list representation with n linked lists
  std::vector<std::list<std::pair<std::optional<T>,int>>> adj_list;
};

template<typename T>
AdjacencyList<T>::AdjacencyList(int n, bool is_directed) : adj_list(n, std::list<std::pair<std::optional<T>,int>>()) {
  directed = is_directed;
  nodes = n;
  edges = 0;
}

template<typename T>
bool AdjacencyList<T>::is_directed() const {
  return directed;
}

template<typename T>
bool AdjacencyList<T>::has_edge(int x, int y) const {
  // check for invalid nodes
  if (x < 0 || x >= nodes || y < 0 || y >= nodes) {
    return false;
  }

  // loop through pairs with matching x
  for (std::pair<std::optional<T>,int> pair : adj_list.at(x)) {
    if (pair.second == y)  // look for matching y
      return true;
  }
  return false;
}

template<typename T>
void AdjacencyList<T>::add_edge(int x, std::optional<T> label, int y) {
  // check for invalid nodes
  if (x < 0 || x >= nodes || y < 0 || y >= nodes) {
    return;
  }

  // return if edge already exists
  if (has_edge(x, y)) {
    return;
  }

  // add new edge to adj_list
  std::pair<std::optional<T>, int> new_pair = std::make_pair<>(label, y);
  adj_list.at(x).push_back(new_pair);

  // if undirected, add the inverse edge
  if (!is_directed()) {
    std::pair<std::optional<T>,int> inverse_pair = std::make_pair<>(label, x);
    adj_list.at(y).push_back(inverse_pair);
  }

  edges++;
}

template<typename T>
void AdjacencyList<T>::rem_edge(int x, int y) {  
  for (auto it = adj_list[x].begin(); it != adj_list[x].end(); ++it) {
    if (it->second == y) {
      adj_list[x].erase(it);
      edges--;

      break;
    }
  }

  // if undirected remove corresponding edge
  if (!is_directed()) {
    for (auto it = adj_list[y].begin(); it != adj_list[y].end(); ++it) {
      if (it->second == x) {
        adj_list[y].erase(it);

        return;
      }
    }
  }
}

template<typename T>
std::optional<T> AdjacencyList<T>::get_label(int x, int y) const {
  std::list<std::pair<std::optional<T>, int>> row = adj_list.at(x);
  
  for (auto it = row.begin(); it != row.end(); ++it) {
    if (it->second == y) {
      return it->first;
    }
  }

  return std::nullopt;
}

template<typename T>
void AdjacencyList<T>::set_label(int x, const T& label, int y) {
  for (auto it = adj_list[x].begin(); it != adj_list[x].end(); ++it) {
    if (it->second == y) {
      it->first = std::make_optional<T>(label);

      break;
    }
  }

  // if undirected set the corresponding label as well
  if (!is_directed()) {
    for (auto it = adj_list[y].begin(); it != adj_list[y].end(); ++it) {
      if (it->second == x) {
        it->first = std::make_optional<T>(label);

        return;
      }
    }
  }
}

template<typename T>
std::vector<int> AdjacencyList<T>::out_nodes(int x) const {
  // check for invalid nodes
  if (x < 0 || x >= nodes) {
    return std::vector<int>();
  }

  std::list<std::pair<std::optional<T>, int>> row = adj_list.at(x);  // get the row at x

  std::vector<int> nodes;  // new vector for out_nodes

  for (const auto & item : row) {  // iterate through list
    nodes.push_back(item.second);  // add to nodes
  }

  return nodes;
}

template<typename T>
std::vector<int> AdjacencyList<T>::in_nodes(int x) const {
  // check for invalid nodes
  if (x < 0 || x >= nodes) {
    return std::vector<int>();
  }

  std::vector<int> nodes;  // new vector for in_nodes

  for (int i = 0; i < adj_list.size(); i++) {  // iterate through vector
    for (auto item : adj_list[i]) {  // iterate through inside list
      if (item.second == x) {  // check for x value
        nodes.push_back(i);  // add i to nodes
        
        break;
      }
    }
  }
  
  return nodes;
}

template<typename T>
std::vector<int> AdjacencyList<T>::adjacent(int x) const {
    
  std::vector<int> out = out_nodes(x);
  std::vector<int> in = in_nodes(x);

  // concat the two lists
  std::vector<int> combined;
  for (int i : out) {
    combined.push_back(i);
  }

  for (int i : in) {
    combined.push_back(i);
  }

  // make vector unique
  std::sort(combined.begin(), combined.end());
  auto last = std::unique(combined.begin(), combined.end());
  combined.erase(last, combined.end());

  // return combined vector
  return combined;
}

template<typename T>
int AdjacencyList<T>::node_count() const {
  return nodes;
}

template<typename T>
int AdjacencyList<T>::edge_count() const {
  return edges;
}


#endif
