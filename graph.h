//----------------------------------------------------------------------
// File: graph.h
// Auth: S. Bowers
// Date: Fall 2022
// Desc: Abstract class for representing graphs. Assumes nodes are
//       labeled using integer values, but edges can be labeled with
//       labels of any type T.
//----------------------------------------------------------------------


#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <optional>


template<typename T>
class Graph
{
public:
  
  // virtual destructor
  virtual ~Graph() {}

  // Returns true if the graph is directed and false otherwise. Note
  // that an edge (x,y) in an undirected graph always has a
  // corresponding edge (y,x). Since both (x,y) and (y,x) in an
  // undirected graph count as a single edge, these edges count as 1
  // edge towards the given edge count.
  virtual bool is_directed() const = 0;

  // Returns true if the graph has the edge (x,y) and false otherwise.
  virtual bool has_edge(int x, int y) const = 0;

  // Adds the edge (x,y) to the graph and assigns the edge the given
  // (optional) label. If the edge already exists in the graph, this
  // function does nothing.
  virtual void add_edge(int x, std::optional<T> label, int y) = 0;

  // Removes the edge (x,y) from the graph. If the edge is not present
  // in the graph, the function does nothing.
  virtual void rem_edge(int x, int y) = 0;

  // Returns the corresponding label of the edge (x,y). If the edge
  // doesn't exist in the graph, the optional value returned is false.
  virtual std::optional<T> get_label(int x, int y) const = 0;

  // Sets the label of the edge (x,y) to label. If edge (x,y) isn't in
  // the graph, this function does nothing. 
  virtual void set_label(int x, const T& label, int y) = 0;

  // Returns the list of nodes that x is connected to on its outgoing
  // edges (i.e., the direct successors of x).  
  virtual std::vector<int> out_nodes(int x) const = 0;

  // Returns the list of nodes that x is connected to on its incoming
  // edges (i.e., the direct predecessors of x).
  virtual std::vector<int> in_nodes(int x) const = 0;

  // Returns the list of nodes that x is connected to. In a directed
  // graph, should return the union of the nodes on outgoing and
  // incoming edges.
  virtual std::vector<int> adjacent(int x) const = 0;

  // Returns the total number of nodes in the graph.
  virtual int node_count() const = 0;

  // Returns the total number of edges in the graph. In a directed
  // graph, it returns the total number of directed edges. In an
  // undirected graph, it returns the total number of undirected
  // edges.
  virtual int edge_count() const = 0;

};

#endif
