#ifndef LARGE_GEN_H
#define LARGE_GEN_H

#include <Eigen/Dense>
#include <utility>

std::pair<Eigen::MatrixXd, Eigen::VectorXd> generateRandomSystem(int size, unsigned int seed = 42);

#endif 
