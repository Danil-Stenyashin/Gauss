#include "gauss.h"
#include <Eigen/Dense>
#include <cmath>

Eigen::VectorXd GaussianSolver::solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
    if (A.rows() != A.cols() || A.rows() != b.size()) {
        throw std::invalid_argument("Matrix and vector dimensions do not match");
    }

    int n = A.rows();
    Eigen::MatrixXd Ab(n, n + 1);
    Ab << A, b;

    forwardElimination(Ab);

    Eigen::VectorXd x(n);
    backwardSubstitution(Ab, x);

    return x;
}

void GaussianSolver::forwardElimination(Eigen::MatrixXd& Ab) {
    int n = Ab.rows();
    
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        double maxVal = std::abs(Ab(i, i));
        
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(Ab(k, i)) > maxVal) {
                maxVal = std::abs(Ab(k, i));
                maxRow = k;
            }
        }
        
        if (maxRow != i) {
            Ab.row(i).swap(Ab.row(maxRow));
        }

        double pivot = Ab(i, i);
        if (std::abs(pivot) < 1e-10) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        for (int j = i; j < n + 1; ++j) {
            Ab(i, j) /= pivot;
        }

        for (int k = i + 1; k < n; ++k) {
            double factor = Ab(k, i);
            for (int j = i; j < n + 1; ++j) {
                Ab(k, j) -= factor * Ab(i, j);
            }
        }
    }
}

void GaussianSolver::backwardSubstitution(Eigen::MatrixXd& Ab, Eigen::VectorXd& x) {
    int n = Ab.rows();
    for (int i = n - 1; i >= 0; --i) {
        x(i) = Ab(i, n);
        for (int j = i + 1; j < n; ++j) {
            x(i) -= Ab(i, j) * x(j);
        }
    }
}
