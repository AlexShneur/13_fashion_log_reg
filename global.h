#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include <fstream>
#include <vector>

constexpr int MODEL_COEFFS_COUNT = 785;
constexpr int MODELS_COUNT = 10;

using image_classes_t = std::vector<int>;
using features_t = std::vector<float>;
using model_coeffs_t = std::vector<float>;

#endif
