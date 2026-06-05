#include <gtest/gtest.h>
#include <random>
#include <cmath>
#include "Gauss_solve.h"

// Проверка невязки Ax - b
bool verify_solution(const GaussMatrix &original_ab, const GaussVector &x, double tol = 1e-9)
{
    int n = original_ab.rows();
    for (int i = 0; i < n; ++i) {
        double lhs = 0.0;
        for (int j = 0; j < n; ++j) {
            lhs += original_ab(i, j) * x(j);
        }
        double rhs = original_ab(i, n);
        if (std::abs(lhs - rhs) > tol) {
            return false;
        }
    }
    return true;
}

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(3, 4);
    ab <<  2,  1, -1,   8,
          -3, -1,  2, -11,
          -2,  1,  2,  -3;

    GaussMatrix ab_copy = ab;
    GaussVector x = Gauss_solve(ab_copy);

    ASSERT_EQ(x.size(), 3);
    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 3.0, 1e-9);
    EXPECT_NEAR(x(2), -1.0, 1e-9);

    EXPECT_TRUE(verify_solution(ab, x));
}

TEST(GaussSolve, RandomLargeSolve)
{
    std::mt19937 gen(1337);
    std::uniform_real_distribution<double> dis(-10.0, 10.0);

    const int n = 100;
    GaussMatrix ab(n, n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            ab(i, j) = dis(gen);
        }
        ab(i, i) += (ab(i, i) > 0 ? 15.0 : -15.0) * n;
    }

    GaussMatrix ab_copy = ab;
    GaussVector x = Gauss_solve(ab_copy);

    EXPECT_TRUE(verify_solution(ab, x, 1e-9));
}