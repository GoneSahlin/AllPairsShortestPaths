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
  int A[g.node_count() + 1][g.node_count()][g.node_count()];

  for (int u = 0; u < g.node_count(); u++) {
    for (int v = 0; v < g.node_count(); v++) {
      if (u == v) {
        A[0][u][v] = 0;
      } else if (g.has_edge(u, v)) {
        A[0][u][v] = g.get_label(u, v).value();
      } else {
        A[0][u][v] = std::numeric_limits<int>::max();
      }
    }
  }

  for (int k = 0; k < g.node_count(); k++) {
    for (int u = 0; u < g.node_count(); u++) {
      for (int v = 0; v < g.node_count(); v++) {
        int cur_length = A[k][u][v];
        int first_segment = A[k][u][k];
        int second_segment = A[k][k][v];
        int combined = first_segment + second_segment;
        if (cur_length <= combined || first_segment == std::numeric_limits<int>::max() || second_segment == std::numeric_limits<int>::max()) {
          A[k+1][u][v] = cur_length;
        } else {
          A[k+1][u][v] = first_segment + second_segment;
        }
      }
    }
  }

  for (int u = 0; u < g.node_count(); u++) {
    if (A[g.node_count()][u][u] < 0) {
      return vector<vector<int>>();
    }
  }

  vector<vector<int>> dists;
  for (int u = 0; u < g.node_count(); u++) {
    dists.push_back(vector<int>());
    for (int v = 0; v < g.node_count(); v++) {
      dists[u].push_back(A[g.node_count()][u][v]);
    }
  }

  return dists;

}

#endif

