//----------------------------------------------------------------------
// FILE: final_test.cpp
// NAME: Zach Sahlin
// DATE: Fall 2022 (CPSC 450)
// DESC: Various unit tests for final algorithms.
//----------------------------------------------------------------------

#include <iostream>
#include <gtest/gtest.h>
#include "graph.h"
#include "adjacency_list.h"
#include "graph_algorithms.h"

using std::nullopt;
using std::vector;
using std::set;


// helper functions

bool contains_set(vector<set<int>> sets, set<int> s)
{
  for (auto t : sets)
    if (s == t)
      return true;
  return false;
}


//----------------------------------------------------------------------
// Johnson's Tests
//----------------------------------------------------------------------

TEST(BasicJohnsonsTests, OneNodeTest) {
  AdjacencyList<int> g(1, true);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(1, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(1, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
}

TEST(BasicJohnsonsTests, TwoNodeOneEdgeTest) {
  AdjacencyList<int> g(2, true);
  g.add_edge(0,1,1);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(2, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(2, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
}

TEST(BasicJohnsonsTests, TwoNodeTwoEdgeTest) {
  AdjacencyList<int> g(2, true);
  g.add_edge(0,1,1);
  g.add_edge(1,2,0);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(2, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(2, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(2, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
}

TEST(BasicJohnsonsTests, ThreeNodeCycleTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0,1,1);
  g.add_edge(1,2,2);
  g.add_edge(2,3,0);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(3, path_costs[0][2]);
  ASSERT_EQ(5, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(3, path_costs[1][2]);
  ASSERT_EQ(3, path_costs[2][0]);
  ASSERT_EQ(4, path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicJohnsonsTests, ThreeNodeShortcutTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 3, 2);
  g.add_edge(0, 2, 2);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(2, path_costs[0][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(3, path_costs[1][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][0]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicJohnsonsTests, ThreeNodeLongRouteTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 2);
  g.add_edge(0, 4, 2);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(3, path_costs[0][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(2, path_costs[1][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][0]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicJohnsonsTests, FourNodeTest) {
  AdjacencyList<int> g(4, true);
  g.add_edge(0, 1, 1);
  g.add_edge(0, 4, 3);
  g.add_edge(1, 6, 2);
  g.add_edge(1, 2, 3);
  g.add_edge(2, 1, 0);
  g.add_edge(3, 3, 2);
  auto path_costs = GraphAlgorithms<int>::johnsons(g);
  ASSERT_EQ(4, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(4, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(6, path_costs[0][2]);
  ASSERT_EQ(3, path_costs[0][3]);
  ASSERT_EQ(6, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(5, path_costs[1][2]);
  ASSERT_EQ(2, path_costs[1][3]);
  ASSERT_EQ(1, path_costs[2][0]);
  ASSERT_EQ(2, path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
  ASSERT_EQ(4, path_costs[2][3]);
  ASSERT_EQ(4, path_costs[3][0]);
  ASSERT_EQ(5, path_costs[3][1]);
  ASSERT_EQ(3, path_costs[3][2]);
  ASSERT_EQ(0, path_costs[3][3]);
}

//----------------------------------------------------------------------
// Floyd-Warshall Tests
//----------------------------------------------------------------------

TEST(BasicFloydWarshallTests, OneNodeTest) {
  AdjacencyList<int> g(1, true);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(1, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(1, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
}

TEST(BasicFloydWarshallTests, TwoNodeOneEdgeTest) {
  AdjacencyList<int> g(2, true);
  g.add_edge(0,1,1);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(2, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(2, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
}

TEST(BasicFloydWarshallTests, TwoNodeTwoEdgeTest) {
  AdjacencyList<int> g(2, true);
  g.add_edge(0,1,1);
  g.add_edge(1,2,0);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(2, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(2, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(2, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
}

TEST(BasicFloydWarshallTests, ThreeNodeCycleTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0,1,1);
  g.add_edge(1,2,2);
  g.add_edge(2,3,0);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(3, path_costs[0][2]);
  ASSERT_EQ(5, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(3, path_costs[1][2]);
  ASSERT_EQ(3, path_costs[2][0]);
  ASSERT_EQ(4, path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicFloydWarshallTests, ThreeNodeShortcutTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 3, 2);
  g.add_edge(0, 2, 2);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(2, path_costs[0][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(3, path_costs[1][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][0]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicFloydWarshallTests, ThreeNodeLongRouteTest) {
  AdjacencyList<int> g(3, true);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 2);
  g.add_edge(0, 4, 2);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(3, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(3, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(3, path_costs[0][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(2, path_costs[1][2]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][0]);
  ASSERT_EQ(std::numeric_limits<int>::max(), path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
}

TEST(BasicFloydWarshallTests, FourNodeTest) {
  AdjacencyList<int> g(4, true);
  g.add_edge(0, 1, 1);
  g.add_edge(0, 4, 3);
  g.add_edge(1, 6, 2);
  g.add_edge(1, 2, 3);
  g.add_edge(2, 1, 0);
  g.add_edge(3, 3, 2);
  auto path_costs = GraphAlgorithms<int>::floyd_warshall(g);
  ASSERT_EQ(4, path_costs.size());
  for (int i = 0; i < path_costs.size(); i++) {
    ASSERT_EQ(4, path_costs[i].size());
  }
  ASSERT_EQ(0, path_costs[0][0]);
  ASSERT_EQ(1, path_costs[0][1]);
  ASSERT_EQ(6, path_costs[0][2]);
  ASSERT_EQ(3, path_costs[0][3]);
  ASSERT_EQ(6, path_costs[1][0]);
  ASSERT_EQ(0, path_costs[1][1]);
  ASSERT_EQ(5, path_costs[1][2]);
  ASSERT_EQ(2, path_costs[1][3]);
  ASSERT_EQ(1, path_costs[2][0]);
  ASSERT_EQ(2, path_costs[2][1]);
  ASSERT_EQ(0, path_costs[2][2]);
  ASSERT_EQ(4, path_costs[2][3]);
  ASSERT_EQ(4, path_costs[3][0]);
  ASSERT_EQ(5, path_costs[3][1]);
  ASSERT_EQ(3, path_costs[3][2]);
  ASSERT_EQ(0, path_costs[3][3]);
}

//----------------------------------------------------------------------
// main
//----------------------------------------------------------------------

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

