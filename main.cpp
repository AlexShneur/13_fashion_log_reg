#include "result.h"

int main(int argc, char* argv[])
{
    if (argc < 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <test_data file (.csv)> " << " <model_coeffs_file (.txt)> " << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::vector<model_coeffs_t> coeffs;
        if (read_models(argv[2], coeffs))
        {
            std::vector<int> expected_classes, predicted_classes;
            expected_classes.reserve(MODEL_COEFFS_COUNT);
            predicted_classes.reserve(MODEL_COEFFS_COUNT);

            if (get_results(argv[1], expected_classes, predicted_classes, coeffs))
            {
                print_accuracy(expected_classes, predicted_classes);
            }
        }
        else
            return EXIT_FAILURE;
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
