//----------------------------------------------------------------------
// FILE: graph_algorithms.h
// AUTH: Zach Sahlin
// DATE: Fall 2022
// DESC: 11/30/2022
//----------------------------------------------------------------------


#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include <tuple>
#include "graph.h"
#include "adjacency_list.h"

using std::vector;
using std::pair;

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

  //----------------------------------------------------------------------
  // Single-source shortest paths from the given source using
  // Bellman-Ford's algorithm. Allows negative edge weights and
  // detects negative cycles. Assumes graph is directed and maximum
  // edge weight is given by numeric_limits<int>::max().
  // Input:
  //  g -- the given directed weighted graph
  //  s -- the source vertex
  // Output: the minimum path cost from src to each vertex v given as
  //         a vector with indexes as nodes and values as path costs
  //         from s. If the graph has a negative cycle, an empty
  //         vector is returned.
  //----------------------------------------------------------------------
  static vector<int> bellman_ford_shortest_path(const Graph<int>& g, int s);

  //----------------------------------------------------------------------
  // Single-source shortest paths from the given source using
  // Dijkstra's algorithm. Asumes maximum weight is given by 
  // numeric_limits<int>::max()
  // Input:
  //  g -- the given directed weighted graph
  //  s -- the source vertex
  // Output: the minimum path cost from src to each vertex v given as
  //         a vector with indexes as nodes and values as path costs
  //         from s
  //----------------------------------------------------------------------
  static vector<int> dijkstra_shortest_path(const Graph<int>& g, int s);
};


template <typename T>
vector<vector<int>> GraphAlgorithms<T>::johnsons(const Graph<int>& g) {
  vector<vector<int>> dists;

  // reweighting using bellman ford
  // create new graph h
  int s = g.node_count();
  AdjacencyList<int> h(s + 1, true);
  // for each edge in g
  for (int u = 0; u < g.node_count(); u++) {
    for (int v : g.out_nodes(u)) {
      h.add_edge(u, g.get_label(u, v).value(), v);
    }
    h.add_edge(s, 0, u);
  }

  auto bellman_ford_dists = bellman_ford_shortest_path(h, s);

  AdjacencyList<int> reweighted_g(g.node_count(), true);
  // for each edge in g
  for (int u = 0; u < g.node_count(); u++) {
    for (int v : g.out_nodes(u)) {
      int new_weight = g.get_label(u, v).value() + bellman_ford_dists[u] - bellman_ford_dists[v];  // w(u, v) + h[u] – h[v]
      reweighted_g.add_edge(u, new_weight, v);
    }
  }

  // run dijkstras on each node in reweighted path
  for (int u = 0; u < g.node_count(); u++) {
    dists.push_back(vector<int>());

    vector<int> dijkstras_dist = dijkstra_shortest_path(reweighted_g, u);

    for (int v = 0; v < g.node_count(); v++) {
      int real_dist = dijkstras_dist[v] - bellman_ford_dists[u] + bellman_ford_dists[v];  // get real distance without reweighting
      dists[u].push_back(real_dist);
    } 
  }

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


template<typename T>
vector<int> GraphAlgorithms<T>::bellman_ford_shortest_path(const Graph<int>& g, int s) {
  vector<int> dists;
  for (int v = 0; v < g.node_count(); v++) {
    dists.push_back(std::numeric_limits<int>::max());
  }

  dists[s] = 0;

  for (int i = 0; i < g.node_count(); i++) {
    // for each edge
    for (int u = 0; u < g.node_count(); u++) {
      vector<int> out_nodes = g.out_nodes(u);
      for (int v : out_nodes) {
        if (dists[v] > dists[u] + g.get_label(u, v).value() && dists[u] != std::numeric_limits<int>::max()) {
          dists[v] = dists[u] + g.get_label(u, v).value();
        }
      }
    }
  }

  // for each edge
  for (int u = 0; u < g.node_count(); u++) {
    auto out_nodes = g.out_nodes(u);
    for (auto v : out_nodes) {
      if (dists[v] > dists[u] + g.get_label(u, v).value() && dists[u] != std::numeric_limits<int>::max()) {
        return vector<int>();
      }
    }
  }
  
  return dists;
}


template <typename T>
vector<int> GraphAlgorithms<T>::dijkstra_shortest_path(const Graph<int>& g, int s) {
  vector<int> dist;

  if (g.node_count() == 0) {
    return dist;
  }

  for (int i = 0; i < g.node_count(); i++) {
    dist.push_back(std::numeric_limits<int>::max());
  }
  bool excluded[g.node_count()] = { false };

  dist[s] = 0;
  excluded[s] = true;

  // compute E
  vector<pair<int,int>> edges;
  for (int i = 0; i < g.node_count(); i++) {
    vector<int> adj = g.out_nodes(i);
    for (int j : adj) {
      edges.push_back(std::pair<int,int>(i,j));
    }
  }

  while (true) {
    int minDist = -1;
    pair<int,int> minEdge;
    int minIndex;
    for (int i = 0; i < edges.size(); i++) {
      pair<int,int> edge = edges[i];
      if (excluded[edge.first] && !excluded[edge.second]) {
        int edgeDist = dist[edge.first] + g.get_label(edge.first, edge.second).value();
        if (edgeDist < minDist || minDist == -1) {
          minDist = edgeDist;
          minEdge = edge;
          minIndex = i;
        }
      }
    }
    if (minDist == -1) {
      break;
    }
    excluded[minEdge.second] = true;
    
    dist[minEdge.second] = minDist;

    edges.erase(edges.begin() + minIndex);
  }

  return dist;
}


#endif
