//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.cpp
// DATE: Fall 2022
// DESC: Helper functions for performance testing.
//---------------------------------------------------------------------------

#include <chrono>
#include <vector>
#include "util.h"
#include "graph.h"

#include <iostream>

using namespace std::chrono;


void load_sparse(Graph<int>& g)
{
  int n = g.node_count();
  int i = 1; // for edge labels
  for (int x = 0; x < (n-1); ++x)
    g.add_edge(x, i++, x+1);
  for (int x = (n-1); x > 1; --x)
    g.add_edge(x, i++, x-2);
}


void load_sparse(Graph<int>& g, int start, int end)
{
  int n = g.node_count();
  if (start < 0 or start >= n or end < 0 or end >= n or start >= end)
    return;
  int i = start + 1;
  for (int x = start; x < end; ++x)
    g.add_edge(x, i++, x+1);
  for (int x = end; x > start + 1; --x)
    g.add_edge(x, i++, x-2);
}


void load_sparse_acyclic_bipartite(Graph<int>& g)
{
  int n = g.node_count();
  int i = 1; // for edge labels
  for (int x = 0; x < (n-1); ++x)
    g.add_edge(x, i++, x+1);
  for (int x = 0; x < (n-3); x = x + 3)
    g.add_edge(x, i++, x + 3);
}

void load_sparse_mini_cycles(Graph<int>& g)
{
  int n = g.node_count();
  int i = 1; // for edge labels
  for (int x = 0; x < (n-1); ++x)
    g.add_edge(x, i++, x+1);
  for (int x = (n-1); x > 1; --x)
    g.add_edge(x, i++, x-1);
}

void load_dense(Graph<int>& g, double pct)
{
  int n = g.node_count();
  int i = 1; // for edge labels
  int skip = 1 / pct;
  for (int x = 0; x < n; ++x)
    for (int y = x+1; y < n; y += skip)
      g.add_edge(x, i++, y);  
}

void load_dense(Graph<int>& g, double pct, int start, int end)
{
  int n = g.node_count();
  int i = start + 1; // for edge labels
  int skip = 1 / pct;
  for (int x = start; x < end; ++x)
    for (int y = x+1; y < end; y += skip)
      g.add_edge(x, i++, y);  
}

void load_dense_cyclic(Graph<int>& g, double pct)
{
  int n = g.node_count();
  int i = 1;
  int skip = 1 / pct;
  if (skip < 2)
    skip = 2;
  for (int x = 0; x < n-1; ++x) {
    g.add_edge(x, i++, x+1);
    g.add_edge(x+1, i++, x);
    for (int y = x + skip; y < n; y += skip) {
      g.add_edge(x, i++, y);
      if (y > x + skip)
        g.add_edge(y, i++, x+1);
      else
        g.add_edge(y, i++, x);
    }
  }
}

void load_dense_mini_cycles(Graph<int>& g, double pct)
{
  int n = g.node_count();
  int i = 1;
  int skip = 1 / pct;
  for (int x = 0; x < n-1; ++x) {
    g.add_edge(x, i++, x+1);
    g.add_edge(x+1, i++, x);
    for (int y = x + skip; y < n; y += skip) {
      g.add_edge(x, i++, y);
      g.add_edge(y, i++, x);
    }
  }
}

double timed_load_sparse(Graph<int>& g)
{
  auto t0 = high_resolution_clock::now();
  load_sparse(g);
  auto t1 = high_resolution_clock::now();
  return duration_cast<milliseconds>(t1 - t0).count();
}


double timed_load_dense(Graph<int>& g, double pct)
{
  auto t0 = high_resolution_clock::now();
  load_dense(g, pct);
  auto t1 = high_resolution_clock::now();
  return duration_cast<milliseconds>(t1 - t0).count();
}


double timed_in_nodes(Graph<int>& g)
{
  double total = 0.0;
  // sample 1% of nodes
  int n = g.node_count() / 100;
  for (int u = 0; u < n; ++u) {
    auto t0 = high_resolution_clock::now();
    auto r = g.in_nodes(u);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  if (n <= 0)
    return 0.0;
  return (total/1000) / n;
}


double timed_out_nodes(Graph<int>& g)
{
  double total = 0.0;
  // sample 1% of nodes
  int n = g.node_count() / 100;
  for (int u = 0; u < n; ++u) {
    auto t0 = high_resolution_clock::now();
    auto r = g.out_nodes(u);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  if (n <= 0)
    return 0.0;
  return (total/1000) / n;
}


double timed_adjacent_nodes(Graph<int>& g)
{
  double total = 0.0;
  // sample 1% of nodes
  int n = g.node_count() / 100;
  for (int u = 0; u < n; ++u) {
    auto t0 = high_resolution_clock::now();
    auto r = g.adjacent(u);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  if (n <= 0)
    return 0.0;
  return (total/1000) / n;
}




