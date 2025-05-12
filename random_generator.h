#ifndef RANDOM_H
#define RANDOM_H

#include <Eigen/Dense>
#include <random>
#include <utility>

class RandomSystemGenerator {
public:
    static std::pair<Eigen::MatrixXd, Eigen::VectorXd> generateSystem(int size, unsigned int seed = 42);
    
private:
    static double randomDouble(std::mt19937& gen, double min, double max);
};

#endif
