#include "shared_types.h"

namespace {
    std::vector<std::vector<double>> getSubmatrix(const std::vector<std::vector<double>>& matrix, size_t exclude_col) {
        size_t n = matrix.size();
        std::vector<std::vector<double>> sub(n - 1, std::vector<double>(n - 1));
        for (size_t i = 1; i < n; ++i) {
            size_t col_idx = 0;
            for (size_t j = 0; j < n; ++j) {
                if (j == exclude_col) continue;
                sub[i - 1][col_idx++] = matrix[i][j];
            }
        }
        return sub;
    }

    double laplaceDeterminant(const std::vector<std::vector<double>>& matrix, long long& ops) {
        size_t n = matrix.size();
        if (n == 0) return 0.0;
        if (n == 1) return matrix[0][0];
        if (n == 2) {
            ops += 3;
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        double det = 0.0;
        int sign = 1;
        for (size_t col = 0; col < n; ++col) {
            if (matrix[0][col] != 0.0) {
                auto sub = getSubmatrix(matrix, col);
                double sub_det = laplaceDeterminant(sub, ops);
                det += sign * matrix[0][col] * sub_det;
                ops += 2;
            }
            sign = -sign;
        }
        return det;
    }
}

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    long long operations = 0;
    double det = laplaceDeterminant(data->matrix, operations);
    return std::make_unique<Result>(Result{ det, operations });
}