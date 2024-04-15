#ifndef SIMPLE_MATRIX_HPP
#define SIMPLE_MATRIX_HPP

#include <vector>
#include <initializer_list>

class SimpleMatrix {
public:
    class Invalid {};

    SimpleMatrix(std::size_t nrows, std::size_t ncols);
    SimpleMatrix(std::initializer_list<std::initializer_list<double>> data);

    // Copy constructor and copy assignment operator
    SimpleMatrix(const SimpleMatrix& other_mat);
    SimpleMatrix& operator=(const SimpleMatrix& other_mat);

    // Move constructor and move assignment operator
    SimpleMatrix(SimpleMatrix&& other_mat) noexcept;
    SimpleMatrix& operator=(SimpleMatrix&& other_mat) noexcept;

    std::size_t nrows() const;
    std::size_t ncols() const;

    double& operator()(std::size_t i, std::size_t j);
    double operator()(std::size_t i, std::size_t j) const;

    void set_matrix(std::vector<std::vector<double>> data);

private:
    std::vector<std::vector<double>> data_;
};

#endif  // SIMPLE_MATRIX_HPP
