#include "gtest/gtest.h"
#include "gauss.h"
#include "csv_utils.h"

TEST(GaussianSolverTest, SimpleSystem) {
    Eigen::MatrixXd A(2, 2);
    A << 2, -1, 
         1, 3;
    Eigen::VectorXd b(2);
    b << 1, 11;
    
    Eigen::VectorXd x = GaussianSolver::solve(A, b);
    EXPECT_NEAR(x(0), 2.0, 1e-6);
    EXPECT_NEAR(x(1), 3.0, 1e-6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
