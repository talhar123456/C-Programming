#include "simple_matrix.hpp"

// SimpleMatrix::SimpleMatrix(std::size_t nrows, std::size_t ncols)
//     : data_(nrows, std::vector<double>(ncols, 0.0)) {}

SimpleMatrix::SimpleMatrix(std::size_t nrows, std::size_t ncols)
    : data_((nrows > 0 && ncols > 0) ? std::vector<std::vector<double>>(nrows, std::vector<double>(ncols, 0.0)) : throw Invalid{}) {}


SimpleMatrix::SimpleMatrix(std::initializer_list<std::initializer_list<double>> data) {
    data_.clear();
    if (data.size() == 0 || data.begin()->size() == 0) {
        throw Invalid{};
    }

    std::size_t expected_size = data.begin()->size();
    for (const auto& row : data) {
        if (row.size() != expected_size) {
            throw Invalid{};
        }
        data_.emplace_back(row);
    }
}



SimpleMatrix::SimpleMatrix(const SimpleMatrix& other_mat)
    : data_(other_mat.data_) {}

SimpleMatrix& SimpleMatrix::operator=(const SimpleMatrix& other_mat) {
    if (this != &other_mat) {
        data_ = other_mat.data_;
    }
    return *this;
}

SimpleMatrix::SimpleMatrix(SimpleMatrix&& other_mat) noexcept
    : data_(std::move(other_mat.data_)) {}

SimpleMatrix& SimpleMatrix::operator=(SimpleMatrix&& other_mat) noexcept {
    if (this != &other_mat) {
        data_ = std::move(other_mat.data_);
    }
    return *this;
}

std::size_t SimpleMatrix::nrows() const {
    return data_.size();
}

std::size_t SimpleMatrix::ncols() const {
    return (data_.empty() ? 0 : data_[0].size());
}

double& SimpleMatrix::operator()(std::size_t i, std::size_t j) {
    if (i < nrows() && j < ncols()) {
        return data_[i][j];
    } else {
        throw Invalid{};
    }
}

double SimpleMatrix::operator()(std::size_t i, std::size_t j) const {
    if (i < nrows() && j < ncols()) {
        return data_[i][j];
    } else {
        throw Invalid{};
    }
}

void SimpleMatrix::set_matrix(std::vector<std::vector<double>> data) {
    data_ = std::move(data);
}
