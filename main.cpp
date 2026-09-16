#include <iostream>
#include <memory>
#include "shared_types.h"

int main() {
    auto data = std::make_shared<const InputData>(InputData{
        {
            {2.0, 1.0, 1.0},
            {1.0, 3.0, 2.0},
            {1.0, 0.0, 0.0}
        }
        });

    auto resultA = calculateA(data);
    auto [detA, opsA] = *resultA;
    std::cout << "[Student A - Laplace result] Det: " << detA << ", Operations: " << opsA << std::endl;

    return 0;
}