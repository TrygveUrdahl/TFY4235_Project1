#pragma once


// Function to activate bonds and run the percolation
// Inputs
// latticeList: list of all bonds in the lattice.
// nodeStatusList: list of status of all nodes, which are roots and size of clusters
// numBondsToActivate: how many bonds are activated
// numNodes: total number of nodes in the network
std::vector<int> percolate(std::vector< std::pair<int, int> > &latticeList,
        std::vector<int> &nodeStatusList, int numBondsToActivate, int numNodes);


// Function to randomly shuffle the list of bonds.
// Inputs
// latticeList: list of all bonds in the lattice
void shuffleLatticeList(std::vector<std::pair<int, int> > &latticeList);

// Compute convolution of measurement Q with probabilites in pvec.
std::vector<double> convolution(int L, const std::vector<double> &Q, const std::vector<double> &pvec, const std::vector<int> &logBin);
