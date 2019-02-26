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
  int numNodes = L*L;
  std::vector< std::pair<int, int> > latticeList;
  latticeList.reserve(numNodes);
  for (int i = 0; i < numNodes; i++) {
    std::pair<int, int> bondRight       = std::make_pair(i, i + 1);
    std::pair<int, int> bondBottomLeft  = std::make_pair(i, i + L - 1);
    std::pair<int, int> bondBottomRight = std::make_pair(i, i + L);
    // TODO: edge case fixes
    if ((i + 1) % L == 0) {
      bondRight.second = i - L + 1;
    }
    if (i % L == 0) {
      bondBottomLeft.second = i + L + (L - 1);
      if (( (i / L) % 2) == 1) {
        bondBottomLeft.second = i + L;
        bondBottomRight.second = i + L + 1;
      }
    }
    if ((i + 1) > L * (L - 1)) {
      bondBottomLeft.second  = i % L;
      bondBottomRight.second = i % L + 1;
      if ((i + 1) % L == 0) {
        bondBottomRight.second = 0;
      }
    }
    latticeList.push_back(bondRight);
    latticeList.push_back(bondBottomLeft);
    latticeList.push_back(bondBottomRight);
  }
  //writeLatticeToFile(latticeList, filename, numNodes);
  return latticeList;
}

// Function to generate, return, and write to filename a honeycomb lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the honeycomb lattice is written
std::vector< std::pair<int, int> > generateHoneycombLattice(int L, std::string filename) {
  int numNodes;
  std::vector< std::pair<int, int> > latticeList;
  latticeList.reserve(numNodes);


  //writeLatticeToFile(latticeList, filename, numNodes);
  return latticeList;
}
