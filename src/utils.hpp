#pragma once
#include <random>


// Tabulate the log-sum up till (and including) max, and return as a vector
// Input
// int max: highest value (+ 1) to find the log-sum of
std::vector<int> getLogSum(int max);


// Calculate element-wise logarithm of a vector V
// Input
// vector V: Vector to find logarithms of
std::vector<double> logV(const std::vector<double> &V);


// C-style random number generator.
// Input
// min: lowest possible number generated.
// max: highest possible number generated.
int otherRandomGenerator(int min, int max);

// Random number generator using the Mersenne Twister P-RNG.
// Result will be an int in [min, max].
// Input
// min: lowest possible number generated.
// max: highest possible number generated.
// generator: pre-initialized Mersenne Twister-generator.
int generateRandomNumber(int min, int max, std::mt19937 &generator);

// Find the root node of a cluster recursively
// Inputs
// j: node to be checked for root
// nodeStatusList: list of which nodes are roots
int findRootNode(int j, std::vector<int> &nodeStatusList);

// Generate the Node status list used to keep track of root nodes and tree sizes
// Inputs
// N: Number of nodes
std::vector<int> generateNodeStatusList(int N);

// Helper-function to read lattice from file.
// Inputs
// filename: name of output file to which the lattice is written
std::vector< std::pair<int, int> > readLatticeFromFile(std::string filename);

// Helper-function to write lattice to file.
// First line of file contains number of nodes and number of bonds
// Inputs
// lattice: The list of all bonds in the lattice
// filename: name of output file to which the lattice is written
void writeLatticeToFile(std::vector< std::pair<int, int> > &lattice, std::string filename, int numNodes);

// Helper-function to write vector to file.
// Inputs
// theVector: The vector to print to file.
// filename: name of output file to which the lattice is written.
void writeVectorToFile(std::vector<int> &theVector, std::string filename = "../output/cluster.txt");
