#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <lazycsv.hpp>

#include "util.h"
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_csv>\n";
        return 1;
    }

    try {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        if (ab.rows() == 0 || ab.cols() == 0) {
            std::cerr << "Error: Empty matrix or failed to read CSV.\n";
            return 1;
        }

        GaussVector x = Gauss_solve(ab);

        GaussMatrix sol(x.size(), 1);
        for (int i = 0; i < x.size(); ++i) {
            sol(i, 0) = x(i);
        }

        print_matrix_as_csv(std::cout, sol);
    } 
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}