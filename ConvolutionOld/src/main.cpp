#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <random>
#include <algorithm>
#include <cstdio>
#include <ctime>

#include <GaloisScalar.hpp>
#include <GaloisOneZeroTensor.hpp>
#include <GaloisZeroOneTensor.hpp>
#include <GaloisOneOneTensor.hpp>
#include <GaloisZeroTwoTensor.hpp>
#include <GaloisTwoZeroTensor.hpp>

#include <FiniteProjectiveGeometry.hpp>

using namespace galois;


int main(int argc, char *argv[]) {

  // Use the first command line argument as the prime number
  int primeNumber{std::atoi(argv[1])};
  set_prime(primeNumber);

  int dimension{2};
  set_dimension(dimension+1);

  int squaresCardinality{static_cast<int>((primeNumber - 1)*0.5)};

  int ceiledSquareRootOfPrimeNumber{static_cast<int>(ceil(sqrt(primeNumber)))};

  std::ofstream q, q_bar, /* q_bar2, */  background, non_squares, countMapFinal;
  q.open("q.txt"); q_bar.open("q_bar.txt"); /* q_bar2.open("q_bar2.txt"); */ background.open("background.txt"); non_squares.open("non_squares.txt"); countMapFinal.open("count_map.txt");

  std::vector <GaloisScalar> squares;
  for(GaloisScalar candidate{1}; candidate < squaresCardinality + 1; ++candidate) {
    squares.push_back(candidate*candidate);
  }
  std::vector<GaloisScalar> nonSquares;
  non_squares << "Numbers without a square root for p = " << primeNumber << ":" << std::endl;
  for(int candidate{1}; candidate < primeNumber; ++candidate) {
    if(std::find(squares.begin(), squares.end(), candidate) != squares.end()) {
    } else {
      nonSquares.push_back(candidate);
      non_squares << candidate << " ";
    }
  }

  GaloisScalar m11{std::atoi(argv[2])};
  GaloisScalar m12{std::atoi(argv[3])};
  GaloisScalar m22{std::atoi(argv[4])};

  GaloisScalar zero{0}; GaloisScalar one{1};


  std::vector<std::vector<double> > countMap(ceiledSquareRootOfPrimeNumber, std::vector <double>(ceiledSquareRootOfPrimeNumber));

  int range{squaresCardinality};
  for(int x{range}; x>-range-1; --x) {
    for(int y{-range}; y<range+1; ++y) {
      //if(x + y == zero) {
      if(((x*x)*m11 + 2*((y*x)*m12) + (y*y)*m22 + one) == zero) {
        q << x << "\t" << y << std::endl;

        GaloisScalar projX{x + primeNumber}, projY{y + primeNumber};
        int convProjX{static_cast<int>(floor(sqrt(static_cast<double>(projX*projX))))}, convProjY{static_cast<int>(floor(sqrt(static_cast<double>(projY*projY))))};
        ++countMap[convProjX][convProjY];
      }
      if(((x*x)*m11 + 2*((y*x)*m12) + (y*y)*m22 + nonSquares[std::atoi(argv[5])]) == zero) {
        q_bar << x << "\t" << y << std::endl;
        //std::cout << "Here!" << std::endl;

        GaloisScalar projX{x + primeNumber}, projY{y + primeNumber};
        int convProjX{static_cast<int>(floor(sqrt(static_cast<double>(projX*projX))))}, convProjY{static_cast<int>(floor(sqrt(static_cast<double>(projY*projY))))};
        ++countMap[convProjX][convProjY];
      }
      
      /*
      if(((x*x)*m11 + 2*((y*x)*m12) + (y*y)*m22 + nonSquares[std::atoi(argv[6])]) == zero) {
        q_bar2 << x << "\t" << y << std::endl;
      }
      */
      //background << x << "\t" << y << std::endl;
    }
  }

  for (auto countColumn : countMap) {
    for (auto count : countColumn) {
      countMapFinal << count << " ";
    }
    countMapFinal << std::endl;
  }
  q.close(); q_bar.close(); /* q_bar2.close(); */ background.close(); non_squares.close(); countMapFinal.close();

  return 0;
}
