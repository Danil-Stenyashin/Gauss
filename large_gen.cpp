#include "random_generator.h"
#include "csv_utils.h"
#include <Eigen/Dense>
#include <iostream>

int main(int argc, char** argv) {  
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <size> <output.csv>" << std::endl;
        return 1;
    }

    try {
        int size = std::stoi(argv[1]);
        auto [A, b] = RandomSystemGenerator::generateSystem(size, 42);
        
        Eigen::MatrixXd Ab(A.rows(), A.cols() + 1);
        Ab << A, b;
        
        CSVutils::writeMatrix(argv[2], Ab);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
