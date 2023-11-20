#ifndef RAY_TRACER_CHALLENGE_MATRIX_H
#define RAY_TRACER_CHALLENGE_MATRIX_H

#include <cstddef>
#include <array>
#include <vector>
#include <string>
#include <ostream>
#include "util.h"
#include "BaseTuple.h"

// TODO we don't actually need this to be a struct. Consider just making the Matrix be an alias to the std array data
// and writing free functions to define the operations.
template<size_t ROWS, size_t COLS>
struct Matrix {

    bool operator==(const Matrix &other) const {
        for (size_t i = 0; i < ROWS; ++i) {
            for (size_t j = 0; j < COLS; ++j) {
                if (!within_epsilon(cells[j][i], other.cells[j][i])) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix<4, 4> operator*(const Matrix &other) const {
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

    BaseTuple<TupleOrColor::TUPLE> operator*(const BaseTuple<TupleOrColor::TUPLE> &other) const {
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
        Matrix<COLS, ROWS> result;
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

    [[nodiscard]] Matrix<ROWS - 1, COLS - 1> submatrix(const size_t row_to_remove, const size_t col_to_remove) const {
        Matrix<ROWS - 1, COLS - 1> result;


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

    static Matrix identity() {
        Matrix m;
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
