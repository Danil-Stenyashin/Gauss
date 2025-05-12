#include "random_generator.h"
#include <cmath>

using namespace Eigen;

double RandomSystemGenerator::randomDouble(std::mt19937& gen, double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

std::pair<MatrixXd, VectorXd> RandomSystemGenerator::generateSystem(int size, unsigned int seed) {
    std::mt19937 gen(seed);
    
    MatrixXd A = MatrixXd::Zero(size, size);
    VectorXd b = VectorXd::Zero(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A(i, j) = randomDouble(gen, -10.0, 10.0);
        }
        b(i) = randomDouble(gen, -10.0, 10.0);
    }

    for (int i = 0; i < size; ++i) {
        double sum = 0.0;
        for (int j = 0; j < size; ++j) {
            if (j != i) {
                sum += std::abs(A(i, j));
            }
        }
        
 
        A(i, i) = sum + randomDouble(gen, 0.1, 1.0);
    }

    return {A, b};
}
