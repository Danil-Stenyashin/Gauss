#include "csv_utils.h"
#include "gauss.h"
#include "random_generator.h"
#include <iostream>
#include <Eigen/Dense>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode> [options]\n"
                  << "Modes:\n"
                  << "  generate <size> <output.csv>\n"
                  << "  solve <input.csv> <output.csv>\n";
        return 1;
    }

    const std::string mode(argv[1]); // Режим работы

    try {
        if (mode == "generate") {
            if (argc != 4) {
                std::cerr << "Usage: " << argv[0] << " generate <size> <output.csv>\n";
                return 1;
            }

            const int size = std::stoi(argv[2]);
            const auto [A, b] = RandomSystemGenerator::generateSystem(size, 42);
            
            Eigen::MatrixXd Ab(A.rows(), A.cols() + 1);
            Ab << A, b;
            
            CSVutils::writeMatrix(argv[3], Ab);

        } else if (mode == "solve") {
            if (argc != 4) {
                std::cerr << "Usage: " << argv[0] << " solve <input.csv> <output.csv>\n";
                return 1;
            }

            const Eigen::MatrixXd Ab = CSVutils::readMatrix(argv[2]);
            const Eigen::MatrixXd A = Ab.leftCols(Ab.cols() - 1);
            const Eigen::VectorXd b = Ab.rightCols(1);
            
            const Eigen::VectorXd x = GaussianSolver::solve(A, b);
            
            Eigen::MatrixXd result(x.size(), 1);
            result.col(0) = x;
            CSVutils::writeMatrix(argv[3], result);

        } else {
            std::cerr << "Unknown mode: " << mode << "\n";
            return 1;
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
