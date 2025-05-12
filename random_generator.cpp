#include "random_generator.h"
#include "csv_utils.h" 
#include <Eigen/Dense>
#include <iostream>
#include <random>

std::pair<Eigen::MatrixXd, Eigen::VectorXd> RandomSystemGenerator::generateSystem(int size, unsigned int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(size, size);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A(i,j) = dist(gen);
        }
        b(i) = dist(gen);
    }

    for (int i = 0; i < size; ++i) {
        double sum = A.row(i).cwiseAbs().sum() - std::abs(A(i,i));
        A(i,i) = sum + 1.0;
    }

    return {A, b};
}

int generator_main(int argc, char** argv) {
    if (argc < 2) {  
        std::cerr << "Usage: generate <size> <output.csv>" << std::endl;
        return 1;
    }
    
    try {
        int size = std::stoi(argv[0]);
        auto [A, b] = RandomSystemGenerator::generateSystem(size, 42);
        
        Eigen::MatrixXd Ab(A.rows(), A.cols() + 1);
        Ab << A, b;
        
        CSVutils::writeMatrix(argv[1], Ab);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
