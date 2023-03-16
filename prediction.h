#ifndef PREDICTION_H
#define PREDICTION_H

#include "global.h"
#include <numeric>
#include <cmath>

template<typename T>
auto sigma(T x)
{
    return 1 / (1 + std::exp(-x));
}

float predict_proba(const features_t& feat, features_t& coef)
{
    if (feat.size() + 1 != coef.size())
    {
        throw std::runtime_error("predict_proba: feature vector size mismatch");
    }
    auto z = std::inner_product(feat.begin(), feat.end(), ++coef.begin(), coef.front());
    return sigma(z);
}

#endif
