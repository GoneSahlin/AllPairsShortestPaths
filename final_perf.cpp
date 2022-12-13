//---------------------------------------------------------------------------
// NAME: Zach Sahlin
// FILE: final_perf.cpp
// DATE: Fall 2022
// DESC: Performance test driver for my final project. Built based off of hw6_perf. To run from the
//       command line use:
//          ./final_perf 
//       which will print out the corresponding timing data. To
//       save this data to a file, run the command:
//          ./final_perf > perf_output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <set>
#include <chrono>
#include "util.h"
#include "adjacency_list.h"
#include "graph_algorithms.h"

using namespace std;
using namespace std::chrono;

// test parameters
const int start = 0;
const int step = 100;
const int stop = 1000;
const int runs = 1;

// function prototypes
double timed_johnsons(const Graph<int>&);
double timed_floyd_warshall(const Graph<int>&);

int main(int argc, char* argv[])
{
  
  // configure remaining output
  cout << fixed << showpoint;
  cout << setprecision(2);

  
  // output data header
  cout << "# All times in milliseconds (millis)" << endl;
  cout << "# Column 1 = node count" << endl;
  cout << "# Column 2 = adj-list sparse johnsons" << endl;
  cout << "# Column 3 = adj-list sparse floyd warshall" << endl;
  cout << "# Column 4 = adj-list dense johnsons" << endl;
  cout << "# Column 5 = adj-list dense floyd warshall" << endl;
  
  // generate the timing data
  for (int n = start; n <= stop; n += step) {
    cout << n << " " << flush;

    // johnsons graphs
    AdjacencyList<int> sparse_johnsons_graph(n, true);
    AdjacencyList<int> dense_johnsons_graph(n, true); 
    load_sparse(sparse_johnsons_graph);
    load_dense(dense_johnsons_graph, 0.02); // small to keep overall time down

    // floyd warshall graphs
    AdjacencyList<int> sparse_floyd_warshall_graph(n, true);
    AdjacencyList<int> dense_floyd_warshall_graph(n, true); 
    load_sparse(sparse_floyd_warshall_graph);
    load_dense(dense_floyd_warshall_graph, 0.02); // small to keep overall time down

    // sparse results
    cout << timed_johnsons(sparse_johnsons_graph) << " " << flush;
    cout << timed_floyd_warshall(sparse_floyd_warshall_graph) << " " << flush;

    // dense results
    cout << timed_johnsons(dense_johnsons_graph) << " " << flush;
    cout << timed_floyd_warshall(dense_floyd_warshall_graph) << " " << flush;  

    // end row
    cout << endl;
  }
  
}

double timed_johnsons(const Graph<int>& g)
{
  double total = 0.0;
  int n = g.node_count();
  for (int i = 0; i < runs; ++i) {
    auto t0 = high_resolution_clock::now();
    auto cliques = GraphAlgorithms<int>::johnsons(g);
    if (n > 0)
      assert(cliques.size() > 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  if (g.node_count() <= 0)
    return 0.0;
  return (total/runs);
}

double timed_floyd_warshall(const Graph<int>& g)
{
  double total = 0.0;
  int n = g.node_count();
  for (int i = 0; i < runs; ++i) {
    auto t0 = high_resolution_clock::now();
    auto cliques = GraphAlgorithms<int>::floyd_warshall(g);
    if (n > 0)
      assert(cliques.size() > 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  if (g.node_count() <= 0)
    return 0.0;
  return (total/runs);
}
