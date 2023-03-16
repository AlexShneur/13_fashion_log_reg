#ifndef MODEL_H
#define MODEL_H
#include "global.h"
#include <sstream>

bool read_model(std::istream& stream, model_coeffs_t& model_coeffs)
{
    std::string line;
    std::getline(stream, line);

    std::istringstream linestream{ line };
    float value;
    model_coeffs.reserve(MODEL_COEFFS_COUNT);
    while (linestream, linestream >> value)
    {
        model_coeffs.emplace_back(value);
    }
    return stream.good();
}

bool read_models(const std::string& filename, std::vector<model_coeffs_t>& coeffs)
{
    std::ifstream istream{ filename };         //коэффициенты логистической регрессии. В каждой строке - одна модель
    coeffs.reserve(MODELS_COUNT);
    for (int i = 0; i < MODELS_COUNT; i++)
    {
        model_coeffs_t model_coeffs;
        if (read_model(istream, model_coeffs))
            coeffs.emplace_back(std::move(model_coeffs));
        else
            return false;
    }
    istream.close();
    return true;
}

bool read_features(std::istream& stream, features_t& features)
{
    std::string                line;
    std::getline(stream, line);

    std::stringstream          lineStream(line);
    std::string                cell;

    features.reserve(MODEL_COEFFS_COUNT);
    while (std::getline(lineStream, cell, ','))
    {
        if (!cell.empty())
            features.emplace_back(std::stof(cell));
    }
    return stream.good();
}

#endif
