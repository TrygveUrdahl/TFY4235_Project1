#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "latticegenerator.hpp"
#include "utils.hpp"

// Function to randomly shuffle the list of bonds.
// Inputs
// latticeList: list of all bonds in the lattice
void shuffleLatticeList(std::vector<std::pair<int, int> > &latticeList) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  #pragma omp parallel for schedule(static)
  for (int i = 0; i < latticeList.size() - 1; i++) {
    int swap = generateRandomNumber(i + 1, latticeList.size() - 1, generator);
    //int swap = otherRandomGenerator(i + 1, latticeList.size() - 1);
    std::swap(latticeList.at(i), latticeList.at(swap));
  }
}


// Function to find the main cluster of the system
std::vector<int> extractMainCluster(std::vector<int> &nodeStatusList, std::pair<int, int> largestCluster) {
  std::vector<int> mainClusterNodes;
  mainClusterNodes.push_back(largestCluster.first);
  for (int i = 0; i < nodeStatusList.size(); i++) {
    int node = nodeStatusList.at(i);
    if (!(node < 0)) {
      int nodeToCheck = findRootNode(node, nodeStatusList);
      if (nodeToCheck == largestCluster.first) {
        mainClusterNodes.push_back(i);
      }
    }
  }
  return mainClusterNodes;
}

std::vector<int> extractAllClusters(std::vector<int> &nodeStatusList) {
  std::vector<int> cluster;
  for (int i = 0; i < nodeStatusList.size(); i++) {
    if (nodeStatusList.at(i) != -1) {
      cluster.push_back(i);
    }
  }
  return cluster;
}


// Function to update one bond in the nodeStatusList.
// Inputs
// nodeStatusList: list of which nodes are root nodes and which are not.
// latticeList: list of all bonds in lattice.
// bond: index of which bond to update.
// largestCluster: index and size of largest cluster.
void updateNodeStatusListOnce(std::vector< std::pair<int, int> > &latticeList,
        std::vector<int> &nodeStatusList, int bond,
        std::pair<int, int> &largestCluster, float &averageS) {
  auto currentBond = latticeList.at(bond);
  int firstRoot = findRootNode(currentBond.first, nodeStatusList);
  int secondRoot = findRootNode(currentBond.second, nodeStatusList);
  if (firstRoot == secondRoot) { // Same cluster
    return;
  }
  else { // Different clusters, need to be combined
    if (nodeStatusList.at(firstRoot) < nodeStatusList.at(secondRoot)) {
      // Calculate average cluster size
      averageS -= std::pow(nodeStatusList.at(firstRoot), 2);
      averageS -= std::pow(nodeStatusList.at(secondRoot), 2);
      averageS += std::pow(nodeStatusList.at(firstRoot) + nodeStatusList.at(secondRoot), 2);

      nodeStatusList.at(firstRoot) += nodeStatusList.at(secondRoot);
      nodeStatusList.at(secondRoot) = firstRoot;
      if (std::abs(nodeStatusList.at(firstRoot)) > std::abs(largestCluster.second)) {
        largestCluster.first = firstRoot;
        largestCluster.second = nodeStatusList.at(firstRoot);
      }
    }
    else {
      // Calculate average cluster size
      averageS -= std::pow(nodeStatusList.at(firstRoot), 2);
      averageS -= std::pow(nodeStatusList.at(secondRoot), 2);
      averageS += std::pow(nodeStatusList.at(firstRoot) + nodeStatusList.at(secondRoot), 2);

      nodeStatusList.at(secondRoot) += nodeStatusList.at(firstRoot);
      nodeStatusList.at(firstRoot) = secondRoot;
      if (std::abs(nodeStatusList.at(secondRoot)) > std::abs(largestCluster.second)) {
        largestCluster.first = secondRoot;
        largestCluster.second = nodeStatusList.at(secondRoot);
      }
    }
  }
}

// Function to activate bonds and run the percolation
// Inputs
// latticeList: list of all bonds in the lattice.
// nodeStatusList: list of status of all nodes, which are roots and size of clusters
// numBondsToActivate: how many bonds are activated
std::vector<int> percolate(std::vector< std::pair<int, int> > &latticeList,
        std::vector<int> &nodeStatusList, int numBondsToActivate, int numNodes) {
  std::pair<int, int> largestCluster = std::make_pair(0, -1);
  std::vector<float> PinfArray;
  std::vector<float> PinfSquaredArray;
  std::vector<float> sMedianArray;
  float averageS = static_cast<float>(numNodes);
  float Pinf, PinfSquared, sMedian;
  for (int i = 0; i < numBondsToActivate; i++) {
    updateNodeStatusListOnce(latticeList, nodeStatusList, i, largestCluster, averageS);
    Pinf = std::abs(largestCluster.second)/numNodes;
    //std::cout << "Largest: " << largestCluster.second << ". numNodes: " << numNodes << std::endl;
    PinfSquared = std::pow((largestCluster.second/numNodes), 2);
    sMedian = (averageS - std::pow(numNodes * Pinf, 2))/(numNodes * (1 - Pinf));
    PinfArray.push_back(Pinf);
    PinfSquaredArray.push_back(PinfSquared);
    sMedianArray.push_back(sMedian);
  }
  std::cout << "Pinf: " << Pinf  << ". PinfSquared: " << PinfSquared << ". sMedian: " << sMedian << std::endl;
  std::vector<int> mainCluster = extractMainCluster(nodeStatusList, largestCluster);

  return mainCluster;
}

std::vec<double> convolution(int L, const std::vec<double> &Q, const std::vec<double> &pvec, const std::vec<int> &logBin) {
  const std::vec<double> logQ = logV(Q);
  const std::vec<int> logSum = getLogSum(L);
  const int nProbs = pvec.size();
  const int nBonds = Q.size();
  std::vec<double> Qprob(nProbs);

  #pragma omp parallel for schedule(static)
  for (int i = 0; i < nProbs; i++) {
    const double prob = pvec(i);
    const double logProb = std::log(prob);
    const double logNotProb = std::log(1.0 - prob);

    double Qpi = 0;
    for (int j = 0; j < nBonds; j++) {
      const double a = logBin(j);
      const double b = j * logProb;
      const double c = (nBonds - j) * logNotProb;
      const double d = logQ(j);

      const double term = a + b + c + d;
      Qpi += term;
    }
    Qprob(i) = Qpi;
  }
  return Qprob;
}
