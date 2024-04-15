#include "dataframe.hpp"
#include "utils.hpp"

Dataframe::Dataframe() {}

template<typename T>
void Dataframe::add_column(const std::vector<T>& col_values) {
    if (nrows() != 0 && col_values.size() != nrows()) {
        throw Invalid();
    }

    std::vector<ColType> new_col;
    for (const auto& value : col_values) {
        new_col.emplace_back(value);
    }

    data.push_back(std::move(new_col));
}

void Dataframe::remove_column(const size_t i) {
    if (i >= ncols()) {
        throw Invalid();
    }

    auto it = std::next(data.begin(), i);
    data.erase(it);
}

void Dataframe::remove_column(const std::string& c) {
    auto col_it = std::find(colnames.begin(), colnames.end(), c);

    if (col_it == colnames.end()) {
        throw Invalid();
    }

    size_t col_index = std::distance(colnames.begin(), col_it);
    remove_column(col_index);
}

void Dataframe::set_colnames(const std::vector<std::string>& cnames) {
    if (cnames.size() != ncols()) {
        throw Invalid();
    }

    colnames = cnames;
}

void Dataframe::set_rownames(const std::vector<std::string>& rnames) {
    if (rnames.size() != nrows()) {
        throw Invalid();
    }

    rownames = rnames;
}

void Dataframe::clear_colnames() {
    colnames.clear();
}

void Dataframe::clear_rownames() {
    rownames.clear();
}

bool Dataframe::has_colnames() const {
    return !colnames.empty();
}

bool Dataframe::has_rownames() const {
    return !rownames.empty();
}

std::size_t Dataframe::nrows() const {
    return data.empty() ? 0 : data.front().size();
}

std::size_t Dataframe::ncols() const {
    return data.size();
}

const std::vector<std::string>& Dataframe::get_rownames() const {
    return rownames;
}

const std::vector<std::string>& Dataframe::get_colnames() const {
    return colnames;
}

template <typename T>
T Dataframe::get(const size_t i, const size_t j) const {
    if (i >= nrows() || j >= ncols()) {
        throw Invalid();
    }

    auto column_it = data.begin();
    std::advance(column_it, j);

    return get_type_<T>((*column_it)[i]);
}

template <typename T>
T Dataframe::get(const std::string& r, const std::string& c) const {
    auto row_it = std::find(rownames.begin(), rownames.end(), r);
    auto col_it = std::find(colnames.begin(), colnames.end(), c);

    if (row_it == rownames.end() || col_it == colnames.end()) {
        throw Invalid();
    }

    size_t row_index = std::distance(rownames.begin(), row_it);
    size_t col_index = std::distance(colnames.begin(), col_it);

    auto column_it = data.begin();
    std::advance(column_it, col_index);

    return get_type_<T>((*column_it)[row_index]);
}

template <typename T>
T& Dataframe::get(const size_t i, const size_t j) {
    if (i >= nrows() || j >= ncols()) {
        throw Invalid();
    }

    auto column_it = data.begin();
    std::advance(column_it, j);

    return get_type_<T>((*column_it)[i]);
}

template <typename T>
T& Dataframe::get(const std::string& r, const std::string& c) {
    auto row_it = std::find(rownames.begin(), rownames.end(), r);
    auto col_it = std::find(colnames.begin(), colnames.end(), c);

    if (row_it == rownames.end() || col_it == colnames.end()) {
        throw Invalid();
    }

    size_t row_index = std::distance(rownames.begin(), row_it);
    size_t col_index = std::distance(colnames.begin(), col_it);

    auto column_it = data.begin();
    std::advance(column_it, col_index);

    return get_type_<T>((*column_it)[row_index]);
}

std::ostream& operator<<(std::ostream& os, const Dataframe& df) {
    // Output column names
    if (df.has_colnames()) {
        os << "\t";
        for (const auto& colname : df.get_colnames()) {
            os << colname << "\t";
        }
        os << "\n";
    }

    // Output data
    for (size_t i = 0; i < df.nrows(); ++i) {
        // Output row names
        if (df.has_rownames()) {
            os << df.get_rownames()[i] << "\t";
        }

        // Output row data
        for (size_t j = 0; j < df.ncols(); ++j) {
            os << df.get<std::string>(i, j) << "\t";
        }

        os << "\n";
    }

    return os;
}

bool Dataframe::operator==(const Dataframe& other) const {
    if (nrows() != other.nrows() || ncols() != other.ncols()) {
        return false;
    }

    for (size_t i = 0; i < nrows(); ++i) {
        for (size_t j = 0; j < ncols(); ++j) {
            if (get<std::string>(i, j) != other.get<std::string>(i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool Dataframe::operator!=(const Dataframe& other) const {
    return !(*this == other);
}

void Dataframe::swap_columns(const size_t i, const size_t j) {
    if (i >= ncols() || j >= ncols()) {
        throw Invalid();
    }

    for (auto& row : data) {
        std::swap(row[i], row[j]);
    }

    if (has_colnames()) {
        std::swap(colnames[i], colnames[j]);
    }
}

void Dataframe::swap_columns(const std::string& i, const std::string& j) {
    auto col_it_i = std::find(colnames.begin(), colnames.end(), i);
    auto col_it_j = std::find(colnames.begin(), colnames.end(), j);

    if (col_it_i == colnames.end() || col_it_j == colnames.end()) {
        throw Invalid();
    }

    size_t col_index_i = std::distance(colnames.begin(), col_it_i);
    size_t col_index_j = std::distance(colnames.begin(), col_it_j);

    swap_columns(col_index_i, col_index_j);
}

void Dataframe::order_by(const std::string& c) {
    auto col_it = std::find(colnames.begin(), colnames.end(), c);

    if (col_it == colnames.end()) {
        throw Invalid();
    }

    size_t col_index = std::distance(colnames.begin(), col_it);

    auto sorted_indices = utils::sort_to_index(data[col_index]);
    utils::sort_by_index(data[col_index], sorted_indices);

    if (has_rownames()) {
        utils::sort_by_index(rownames, sorted_indices);
    }
}

template<typename Fun>
void Dataframe::apply(const size_t i, Fun l) {
    if (i >= nrows()) {
        throw Invalid();
    }

    for (size_t j = 0; j < ncols(); ++j) {
        l(get_type_<first_argument_t<Fun>>(data[j][i]));
    }
}

template<typename Fun>
void Dataframe::apply(const std::string& c, Fun l) {
    auto col_it = std::find(colnames.begin(), colnames.end(), c);

    if (col_it == colnames.end()) {
        throw Invalid();
    }

    size_t col_index = std::distance(colnames.begin(), col_it);

    for (size_t i = 0; i < nrows(); ++i) {
        l(get_type_<first_argument_t<Fun>>(data[col_index][i]));
    }
}
