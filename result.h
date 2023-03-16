#ifndef RESULT_H
#define RESULT_H

#include "input_data.h"
#include "prediction.h"

bool get_results(const std::string& filename, image_classes_t& expected_classes, image_classes_t& predicted_classes, std::vector<model_coeffs_t>& coeffs)
{
    std::ifstream test_data{ filename };          //тестовые данные. В каждой строке первый байт - номер класса, остальные - байты изображения
    for (int j = 0; j < MODEL_COEFFS_COUNT; j++)
    {
        int expected_class = 0;
        test_data >> expected_class;
        expected_classes.emplace_back(std::move(expected_class));

        features_t m_features;
        if (!read_features(test_data, m_features)) {
            return false;
        }

        float max_y_pred = -1;
        int max_pred_num = 0;
        for (int i = 0; i < coeffs.size(); i++)
        {
            auto y_pred = predict_proba(m_features, coeffs[i]);
            if (y_pred > max_y_pred)
            {
                max_y_pred = y_pred;
                max_pred_num = i;
            }
        }

        predicted_classes.emplace_back(std::move(max_pred_num));
    }
    test_data.close();
    return true;
}

void print_accuracy(const image_classes_t& expected_classes, const image_classes_t& predicted_classes)
{
    int sum = 0;
    for (int i = 0; i < MODEL_COEFFS_COUNT; i++)
    {
        if (expected_classes[i] == predicted_classes[i])
            ++sum;
    }
    std::cout << "accuracy=" << sum / (double)MODEL_COEFFS_COUNT << std::endl;
}

#endif
