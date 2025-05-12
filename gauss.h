#ifndef GAUSS_H
#define GAUSS_H

#include <Eigen/Dense>

class GaussianSolver {
public:
    static Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
    
private:
    static void forwardElimination(Eigen::MatrixXd& Ab);
    static void backwardSubstitution(Eigen::MatrixXd& Ab, Eigen::VectorXd& x);
};

#endif // GAUSS_H
