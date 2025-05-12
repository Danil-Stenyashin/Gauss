#include "csv_utils.h"
#include "gauss.h"
#include "random_generator.h"
#include <iostream>

int solver_main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: solve <input.csv> <output.csv>" << std::endl;
        return 1;
    }

    try {
        Eigen::MatrixXd Ab = CSVutils::readMatrix(argv[0]);
        Eigen::MatrixXd A = Ab.leftCols(Ab.cols() - 1);
        Eigen::VectorXd b = Ab.rightCols(1);
        
        Eigen::VectorXd x = GaussianSolver::solve(A, b);
        
        Eigen::MatrixXd result(x.size(), 1);
        result.col(0) = x;
        CSVutils::writeMatrix(argv[1], result);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
