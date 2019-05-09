#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <random>
#include "latticegenerator.hpp"
#include "percolate.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
        std::cout << "Need one parameter: \n\tThe width of the lattice. " << std::endl;
        return 1;
  }
  srand(time(NULL));
  int L = atoi(argv[1]);
  float probabilityOfActivation = 0.45;
  if (argc > 2) {
        probabilityOfActivation = atof(argv[2]);
  }
  std::cout << "Lattice width: " << L << std::endl;
  std::cout << "Probability of Activation: " << probabilityOfActivation << std::endl;
  std::string filedir = "../output/";
  auto latticeList = generateSquareLattice(L, filedir + "squarelattice.txt");
  shuffleLatticeList(latticeList);
  auto nodeStatusList = generateNodeStatusList(L*L);
  int numBondsToActivate = probabilityOfActivation * 2  * L * L;
  std::cout << "Activated bonds: " << numBondsToActivate << ". Total bonds: " << 2 * L*L << std::endl;
  auto cluster = percolate(latticeList, nodeStatusList, numBondsToActivate, L*L);
  //writeLatticeToFile(latticeList,filedir + "swappedlattice.txt",L*L);
  //generateTriangularLattice(L, filedir + "triangularlattice.txt");
  writeVectorToFile(cluster);
  return 0;
}
