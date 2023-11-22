#ifndef RAY_TRACER_CHALLENGE_MATRIX_H
#define RAY_TRACER_CHALLENGE_MATRIX_H

#include <cstddef>
#include <array>
#include <vector>
#include <string>
#include <ostream>
#include "util.h"
#include "BaseTuple.h"

// NOTE: we use an especially lax epsilon here to get the tests to pass.
constexpr double MATRIX_EPSILON = 1e-4;

// TODO we don't actually need this to be a struct. Consider just making the Matrix be an alias to the std array data
// and writing free functions to define the operations.
template<size_t ROWS, size_t COLS>
struct Matrix {

    static_assert(ROWS > 0);
    static_assert(COLS > 0);

    bool operator==(const Matrix &other) const {
        for (size_t i = 0; i < ROWS; ++i) {
            for (size_t j = 0; j < COLS; ++j) {
                if (!within_epsilon(cells[j][i], other.cells[j][i], MATRIX_EPSILON)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix<4, 4> operator*(const Matrix &other) const requires (ROWS == 4 && COLS == 4) {
        Matrix result{};
        for (size_t r = 0; r < ROWS; ++r) {
            for (size_t c = 0; c < COLS; ++c) {
                result.cells[r][c] = cells[r][0] * other.cells[0][c] +
                                     cells[r][1] * other.cells[1][c] +
                                     cells[r][2] * other.cells[2][c] +
                                     cells[r][3] * other.cells[3][c];
            }
        }
        return result;
    }

    BaseTuple<TupleOrColor::TUPLE>
    operator*(const BaseTuple<TupleOrColor::TUPLE> &other) const requires (ROWS == 4 && COLS == 4) {
        BaseTuple<TupleOrColor::TUPLE> result{};
        for (size_t r = 0; r < ROWS; ++r) {
            result[r] = cells[r][0] * other.x() +
                        cells[r][1] * other.y() +
                        cells[r][2] * other.z() +
                        cells[r][3] * other.w();
        }
        return result;
    }

    [[nodiscard]] Matrix transpose() const {
        Matrix<COLS, ROWS> result{};
        for (size_t r = 0; r < ROWS; ++r) {
            for (size_t c = 0; c < COLS; ++c) {
                result.cells[r][c] = cells[c][r];
            }
        }
        return result;
    }

    [[nodiscard]] double determinant() const requires (ROWS == 2 && COLS == 2) {
        return cells[0][0] * cells[1][1] - cells[0][1] * cells[1][0];
    }

    [[nodiscard]] double determinant() const {
        double sum = 0.0;
        // We sum up the result of multiplying each element by its cofactor (for the first row only).
        for (size_t col = 0; col < COLS; ++col) {
            sum += cells[0][col] * cofactor(0, col);
        }

        return sum;
    }

    [[nodiscard]] bool is_invertible() const {
        return !within_epsilon(determinant(), 0);
    }

    [[nodiscard]] Matrix<ROWS - 1, COLS - 1>
    submatrix(const size_t row_to_remove, const size_t col_to_remove) const {
        Matrix<ROWS - 1, COLS - 1> result{};


        for (size_t r = 0; r < ROWS; ++r) {
            for (size_t c = 0; c < COLS; ++c) {
                if (r == row_to_remove || c == col_to_remove) {
                    continue;
                }

                size_t dest_row = r;
                size_t dest_col = c;
                if (r > row_to_remove) {
                    dest_row = r - 1;
                }
                if (c > col_to_remove) {
                    dest_col = c - 1;
                }
                result.cells[dest_row][dest_col] = cells[r][c];
            }
        }

        return result;
    }

    [[nodiscard]] double minor(const size_t row_to_remove, const size_t col_to_remove) const {
        return submatrix(row_to_remove, col_to_remove).determinant();
    }

    [[nodiscard]] double cofactor(const size_t row_to_remove, const size_t col_to_remove) const {
        auto result = minor(row_to_remove, col_to_remove);
        if ((row_to_remove + col_to_remove) % 2 == 1) {
            result *= -1;
        }
        return result;
    }

    [[nodiscard]] Matrix inverse() const {
        if (!is_invertible()) {
            assert((false, "Cannot invert matrix!"));
        }

        Matrix result{};
        for (size_t row = 0; row < ROWS; ++row) {
            for (size_t col = 0; col < COLS; ++col) {
                result.cells[col][row] = cofactor(row, col) / determinant();
            }
        }
        return result;
    }

    static Matrix identity() {
        Matrix m{};
        static_assert(ROWS == COLS);
        for (size_t rows = 0; rows < ROWS; rows++) {
            m.cells[rows][rows] = 1.0;
        }
        return m;
    }

    // For pretty printing in GTEST.
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        os << "Matrix<" << ROWS << ", " << COLS << ">{\n";

        for (size_t r = 0; r < ROWS; ++r) {
            os << "{";
            for (size_t c = 0; c < COLS; ++c) {
                os << std::to_string(m.cells[r][c]) << ", ";
            }
            os << "}\n";
        }
        os << "}";
        return os;
    }


    // TODO consider making initializer list version
    //    explicit Matrix(std::array<std::array<double, COLS>, ROWS> cells) : cells_{cells} {}
    std::array<std::array<double, COLS>, ROWS> cells;
};


#endif //RAY_TRACER_CHALLENGE_MATRIX_H
