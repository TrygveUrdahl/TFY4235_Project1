#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

std::vec<int> getLogSum(int max) {
  std::vec<int> logSum(max + 1);
  logSum(0) = 0;
  for (int i = 1; i < max + 1; i++) {
    logSum(i) = logSum(i - 1) + std::log(i);
  }
}

// C-style random number generator.
// Input
// min: lowest possible number generated.
// max: highest possible number generated.
int otherRandomGenerator(int min, int max) {
  int randomNumber = rand() % (max - min + 1) + min;
  return randomNumber;
}

// Random number generator using the Mersenne Twister P-RNG.
// Result will be an int in [min, max].
// Input
// min: lowest possible number generated.
// max: highest possible number generated.
// generator: pre-initialized Mersenne Twister-generator.
int generateRandomNumber(int min, int max, std::mt19937 &generator) {
  //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  //std::mt19937 generator(seed);
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

// Find the root node of a cluster recursively
// Inputs
// j: node to be checked for root
// nodeStatusList: list of which nodes are roots
int findRootNode(int node, std::vector<int> &nodeStatusList) {
  if (nodeStatusList.at(node) < 0) { // true: node is root
    //std::cout << "Node: " << node << ". nodeStatusList.at(node): " << nodeStatusList.at(node) << std::endl;
    return node;
  }
  else {
    //std::cout << "Node: " << node << ". nodeStatusList.at(node): " << nodeStatusList.at(node) << std::endl;
    nodeStatusList.at(node) = findRootNode(nodeStatusList.at(node), nodeStatusList);
    return nodeStatusList.at(node);
  }
}

// Generate the Node status list used to keep track of root nodes and tree sizes.
// The list is called sites(i) in the assignment.
// Inputs
// N: Number of nodes
std::vector<int> generateNodeStatusList(int N) {
  std::vector<int> nodeStatusList(N, -1);
  return nodeStatusList;
}

// Helper-function to read lattice from file.
// Inputs
// filename: name of output file to which the lattice is written.
std::vector< std::pair<int, int> > readLatticeFromFile(std::string filename) {
  int numNodes, numBonds;
  std::vector< std::pair<int, int> > lattice;
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::runtime_error("File not opened! ")
  }

  std::string line;
  std::getline(file, line); // Read first line containing number of nodes and bonds
  std::stringstream stream(line);
  stream >> numNodes >> numBonds;
  while (std::getline(file, line)) { // Read all bonds
    std::stringstream stream(line);
    std::pair<int, int> bond;
    stream >> bond.first >> bond.second;
    lattice.push_back(bond);
  }
  file.close();
  return lattice;
}

// Helper-function to write lattice to file.
// First line of file contains number of nodes and number of bonds.
// Inputs
// lattice: The list of all bonds in the lattice.
// filename: name of output file to which the lattice is written.
void writeLatticeToFile(std::vector< std::pair<int, int> > &lattice, std::string filename, int numNodes) {
  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::runtime_error("File not opened! ")
  }
  file << numNodes << " " << lattice.size() << std::endl;
  for (auto bond : lattice) {
    file << bond.first << " " << bond.second << std::endl;
  }
  file.close();
}

// Helper-function to write largest cluster to file.
// Inputs
// mainCluster: The list of nodes in largest cluster.
// filename: name of output file to which the lattice is written.
void writeVectorToFile(std::vector<int> &theVector, std::string filename = "../output/cluster.txt") {
  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::runtime_error("File not opened! ")
  }
  for (auto elem : theVector) {
    file << elem << std::endl;
  }
  file.close();
}
