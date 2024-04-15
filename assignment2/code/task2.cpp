#include "simple_matrix.hpp"

int main(int, char *[]) {
    // The following should compile
    SimpleMatrix m1(50, 10);
    SimpleMatrix m2 = {{1, 2, 3}, {4, 5, 6}};
    SimpleMatrix m3(m2);
    m3 = m1;
    SimpleMatrix m4(std::move(m1));
    m4 = std::move(m2);
    m4.ncols();
    m4.nrows();
    m4(1, 1);
    const auto m5 = m4;
    m5(0, 1);

    return 0;
}