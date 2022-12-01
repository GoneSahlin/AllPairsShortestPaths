//----------------------------------------------------------------------
// FILE: graph_algorithms.h
// AUTH: Zach Sahlin
// DATE: Fall 2022
// DESC: 11/30/2022
//----------------------------------------------------------------------


#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include "graph.h"
#include "adjacency_list.h"

using std::vector;

template<typename T>
class GraphAlgorithms
{
 public:

  //======================================================================
  // HW6
  //======================================================================

  //----------------------------------------------------------------------
  // Computes the shortest paths between all pairs of vertices
  // using Johnson's algorithm.
  // Input:
  //  g -- the given directed weighted graph
  // Output: the minimum path cost between all pairs of vertives given as
  //         a map with the key as a pair of the source and destination,
  //         and the value as the path cost
  //----------------------------------------------------------------------
  static vector<vector<int>> johnsons(const Graph<int>& g);

  //----------------------------------------------------------------------
  // Computes the shortest paths between all pairs of vertices
  // using the Floyd-Warshall algorithm.
  // Input:
  //  g -- the given directed weighted graph
  // Output: the minimum path cost between all pairs of vertives given as
  //         a map with the key as a pair of the source and destination,
  //         and the value as the path cost
  //----------------------------------------------------------------------
  static vector<vector<int>> floyd_warshall(const Graph<int>& g);

};

template <typename T>
vector<vector<int>> GraphAlgorithms<T>::johnsons(const Graph<int>& g) {
  vector<vector<int>> dists;

  return dists;
}

template <typename T>
vector<vector<int>> GraphAlgorithms<T>::floyd_warshall(const Graph<int>& g) {
  vector<vector<int>> dists;

  return dists;
}

#endif

