#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "utils.hpp"

// Function to generate, return, and write to filename a square lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the square lattice is written
std::vector< std::pair<int, int> > generateSquareLattice(int L, std::string filename) {
  int numNodes = L*L;
  std::vector< std::pair<int, int> > latticeList;
  latticeList.reserve(numNodes);
  for (int i = 0; i < numNodes; i++) {
    std::pair<int, int> bondRight  = std::make_pair(i, i + 1);
    std::pair<int, int> bondBottom = std::make_pair(i, i + L);
    if ((i + 1) % L == 0) {
      bondRight.second = i - L + 1;
    }
    if ((i + 1) > L * (L - 1)) {
      bondBottom.second = i % L;
    }
    latticeList.push_back(bondRight);
    latticeList.push_back(bondBottom);

  }
  //writeLatticeToFile(latticeList, filename, numNodes);
  return latticeList;
}

// Function to generate, return, and write to filename a triangular lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the triangular lattice is written
std::vector< std::pair<int, int> > generateTriangularLattice(int L, std::string filename) {
  int numNodes = 3 * L * L;
  std::vector< std::pair<int, int> > latticeList(numNodes);
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < L; j++) {
      int right = (j + 1)%L + i*L;
      int downRight = (i + 1)%L*L + j;
      int downLeft = (i + 1)%L*L + (j + L - 1)%L;

      int idx = j + i*L;
      latticeList.at(3 * idx) = std::make_pair(idx, right);
      latticeList.at(3 * idx + 1) = std::make_pair(idx, downRight);
      latticeList.at(3 * idx + 2) = std::make_pair(idx, downLeft);
    }
  }
  return latticeList;
}

// Function to generate, return, and write to filename a honeycomb lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the honeycomb lattice is written
std::vector< std::pair<int, int> > generateHoneycombLattice(int L, std::string filename) {
  int numNodes = 3*L*L/2;
  std::vector< std::pair<int, int> > latticeList;
  latticeList.resize(numNodes);
  int k = 0;
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < L; j++) {
      std::pair<int, int> bond0, bond1, bond2, bond3, bond4, bond5;
      int idx = j + i*L;
      int node0 = idx;
      int node1 = idx + 1;
      int node2 = idx + 2;
      int node3 = idx + 3;
      int node;

      node = (i + L - 1)%L*L + (j + L -1)%L;
      latticeList.at(k) = std::make_pair(node0, node);
      k++;
      latticeList.at(k) = std::make_pair(node0, node1);
      k++;

      node = (i + L - 1)%L*L + (j + 1 + 1)/L;
      latticeList.at(k) = std::make_pair(node1, node);
      k++;
      latticeList.at(k) = std::make_pair(node1, node2);
      k++;

      latticeList.at(k) = std::make_pair(node2, node3);
      k++;

      node = i * L + (j + 4)%L;
      latticeList.at(k) = std::make_pair(node3, node);
      k++;
    }
  }
  return latticeList;
}
