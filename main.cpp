#include "csv_utils.h"
#include "gauss.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.csv> <output.csv>" << std::endl;
        return 1;
    }

    try {
        Eigen::MatrixXd Ab = CSVutils::readMatrix(argv[1]);
        Eigen::MatrixXd A = Ab.leftCols(Ab.cols() - 1);
        Eigen::VectorXd b = Ab.rightCols(1);
        
        Eigen::VectorXd x = GaussianSolver::solve(A, b);
        
        Eigen::MatrixXd result(x.size(), 1);
        result.col(0) = x;
        CSVutils::writeMatrix(argv[2], result);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
