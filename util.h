//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.h
// DATE: Fall 2022
// DESC: Helper functions for performance testing.
//---------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H


#include "graph.h"


//----------------------------------------------------------------------
// Add edges to given graph
// Input: a graph g with n nodes and no edges
// Output: g consists of O(n) labeled edges
//----------------------------------------------------------------------
void load_sparse(Graph<int>& g);

//----------------------------------------------------------------------
// Add edges to given graph within specified region
// Input: a graph g with n nodes and no edges, start node, end node
// Output: g consists of O(n) labeled edges
//----------------------------------------------------------------------
void load_sparse(Graph<int>& g, int start, int end);

//----------------------------------------------------------------------
// Add edges to given graph such that for an empty graph, creates a
// sparse, acyclic, bipartite graph
// Input: a graph g with n nodes and no edges, start node, end node
// Output: g consists of O(n) labeled edges
//----------------------------------------------------------------------
void load_sparse_acyclic_bipartite(Graph<int>& g);

//----------------------------------------------------------------------
// Add edges to given graph
// Input: a graph g with n nodes and no edges
// Output: g consists of O(n) labeled edges
//----------------------------------------------------------------------
void load_sparse_mini_cycles(Graph<int>& g);

//----------------------------------------------------------------------
// Add edges to given graph.
// Input: a graph g with n nodes and no edges and the constant
//        percentage of edges to retain (e.g., 25% of n^2).
// Output: g consists of O(n^2) labeled edges
//----------------------------------------------------------------------
void load_dense(Graph<int>& g, double pct);

//----------------------------------------------------------------------
// Add edges to given graph within specified region
// Input: a graph g with n nodes and no edges and the constant
//        percentage of edges to retain (e.g., 25% of n^2).
// Output: g consists of O(n^2) labeled edges
//----------------------------------------------------------------------
void load_dense(Graph<int>& g, double pct, int start, int end);

//----------------------------------------------------------------------
// Add edges to given graph.
// Input: a graph g with n nodes and no edges and the constant
//        percentage of edges to retain (e.g., 25% of n^2).
// Output: g consists of O(n^2) labeled edges
//----------------------------------------------------------------------
void load_dense_cyclic(Graph<int>& g, double pct);

//----------------------------------------------------------------------
// Add edges to given graph
// Input: a graph g with n nodes and no edges and the constant
//        percentage of edges to retain (e.g., 25% of n^2)
// Output: g consists of O(n) labeled edges
//----------------------------------------------------------------------
void load_dense_mini_cycles(Graph<int>& g, double pct);

//----------------------------------------------------------------------
// The total time required to load edges to a given graph
// Input: a graph g with n nodes and no edges
// Output: g consists of O(n) edges
// Returns: total time required in milliseconds
//----------------------------------------------------------------------
double timed_load_sparse(Graph<int>& g);

//----------------------------------------------------------------------
// The total time required to load edges to a given graph
// Input: a graph g with n nodes and no edges and constant percentage
// Output: g consists of O(n^2) edges
// Returns: total time required in milliseconds
//----------------------------------------------------------------------
double timed_load_dense(Graph<int>& g, double pct);

//----------------------------------------------------------------------
// Average time to obtain incoming nodes per graph node
// Input: a graph g with n nodes 
// Returns: average time required per in node call in milliseconds
//----------------------------------------------------------------------
double timed_in_nodes(Graph<int>& g);

//----------------------------------------------------------------------
// Average time to obtain outgoing nodes per graph node
// Input: a graph g with n nodes 
// Returns: average time required per out node call in milliseconds
//----------------------------------------------------------------------
double timed_out_nodes(Graph<int>& g);

//----------------------------------------------------------------------
// Average time to obtain adjacent nodes per graph node
// Input: a graph g with n nodes 
// Returns: average time required per adjacent call in milliseconds
//----------------------------------------------------------------------
double timed_adjacent_nodes(Graph<int>& g);


#endif

