#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();
    if (ab.cols() != n + 1) {
        throw std::invalid_argument("Matrix must be of size N x (N+1)");
    }

    for (int i = 0; i < n; ++i) {
        int max_row = i;
        double max_val = std::abs(ab(i, i));
        for (int k = i + 1; k < n; ++k) {
            double val = std::abs(ab(k, i));
            if (val > max_val) {
                max_val = val;
                max_row = k;
            }
        }

        if (max_val < 1e-12) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        if (max_row != i) {
            ab.row(i).swap(ab.row(max_row));
        }

        for (int k = i + 1; k < n; ++k) {
            double factor = ab(k, i) / ab(i, i);
            ab.row(k) -= factor * ab.row(i);
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = ab(i, n);
        for (int j = i + 1; j < n; ++j) {
            sum -= ab(i, j) * x(j);
        }
        x(i) = sum / ab(i, i);
    }

    return x;
}