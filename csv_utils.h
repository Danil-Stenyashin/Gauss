#pragma once
#include <Eigen/Dense>
#include <string>

namespace CSVutils {
    Eigen::MatrixXd readMatrix(const std::string& filename);
    void writeMatrix(const std::string& filename, const Eigen::MatrixXd& matrix);
}
