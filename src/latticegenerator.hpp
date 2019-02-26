#pragma once

// Function to generate, return, and write to filename a list of all bonds in a square lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the square lattice is written
std::vector< std::pair<int, int> > generateSquareLattice(int L, std::string filename);

// Function to generate, return, and write to filename a triangular lattice.
// Intputs
// L: width/height of lattice (which is of size N = L*L)
// filename: name of output file to which the triangular lattice is written
std::vector< std::pair<int, int> > generateTriangularLattice(int L, std::string filename);

// Function to generate, return, and write to filename a honeycomb lattice.
// Intputs
// L: width/height of lattice
// filename: name of output file to which the honeycomb lattice is written
std::vector< std::pair<int, int> > generateHoneycombLattice(int L, std::string filename);
