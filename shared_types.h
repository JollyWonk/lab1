#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <vector>
#include <memory>

struct InputData {
    std::vector<std::vector<double>> matrix;
};

struct Result {
    double determinant;
    long long operations_count;
};

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

#endif