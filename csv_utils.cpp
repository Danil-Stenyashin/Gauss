#include "csv_utils.h"
#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <iomanip>

Eigen::MatrixXd CSVutils::readMatrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::vector<double>> data;
    std::string line;
    
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        
        data.push_back(row);
    }

    size_t rows = data.size();
    if (rows == 0) return Eigen::MatrixXd(0, 0);
    
    size_t cols = data[0].size();
    Eigen::MatrixXd matrix(rows, cols);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = data[i][j];
        }
    }
    
    return matrix;
}

void CSVutils::writeMatrix(const std::string& filename, const Eigen::MatrixXd& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            file << std::setprecision(15) << matrix(i, j);
            if (j != matrix.cols() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}
