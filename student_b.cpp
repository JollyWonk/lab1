#include "shared_types.h"
#include <cmath>
#include <utility>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    const auto& original = data->matrix;
    const std::size_t n = original.size();

    if (n == 0) {
        return std::make_unique<Result>(Result{ 1.0, 0 });
    }

    for (const auto& row : original) {
        if (row.size() != n) {
            return std::make_unique<Result>(Result{ 0.0, 0 });
        }
    }

    auto matrix = original;

    double determinantSign = 1.0;
    long long operations = 0;

    for (std::size_t i = 0; i < n; ++i) {
        if (std::abs(matrix[i][i]) < 1e-12) {
            std::size_t swapRow = i + 1;

            while (swapRow < n &&
                std::abs(matrix[swapRow][i]) < 1e-12) {
                ++swapRow;
            }

            if (swapRow == n) {
                return std::make_unique<Result>(
                    Result{ 0.0, operations }
                );
            }

            std::swap(matrix[i], matrix[swapRow]);
            determinantSign *= -1.0;
            ++operations;
        }

        for (std::size_t j = i + 1; j < n; ++j) {
            const double factor = matrix[j][i] / matrix[i][i];
            ++operations;

            for (std::size_t k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
                ++operations;
            }
        }
    }

    double determinant = determinantSign;

    for (std::size_t i = 0; i < n; ++i) {
        determinant *= matrix[i][i];
        ++operations;
    }

    return std::make_unique<Result>(
        Result{ determinant, operations }
    );
}