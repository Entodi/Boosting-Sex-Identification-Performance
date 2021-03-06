#include "configuration.h"

#include <iostream>
#include <sstream>

template<class T> bool readParameter(const char* text, T& variable)
{
    std::stringstream stream(text);
    stream >> variable;
    if (stream.fail())
        return false;
    return true;
}

template<> bool readParameter(const char* text, std::string& variable)
{
    variable = text;
    return true;
}

template<class T> bool param(char *argv[], int k,
    const std::string& code, T& variable)
{
    if (std::string(argv[k]) == code) {
        if (readParameter(argv[k + 1], variable) == false)
            return false;
    }
    return true;
}

bool Configuration::load(int argc, char *argv[])
{
    std::cout << "Reading configurations params...\n";
    for (int k = 1; k < argc; k += 2)
    {
        if (!(param(argv, k, "--train", train_flag_)
            && param(argv, k, "--data_filename", data_filename_)
            && param(argv, k, "--model_filename", model_filename_)
            && param(argv, k, "--percent_trainset", percent_trainset_)
            && param(argv, k, "--percent_classifiers", percent_classifiers_)
            && param(argv, k, "--num_classifiers", num_classifiers_)
            && param(argv, k, "--save_period", save_period_)
            && param(argv, k, "--balanced", balanced_flag_)))
            return false;
    }

    if (validateParameters() == false)
        return false;

    showParams();
    return true;
}

bool Configuration::validateParameters()
{
    if ((train_flag_ != 1) && (train_flag_ != 0))
    {
        std::cout << "Train flag should be 0 or 1";
        return false;
    }

    if (data_filename_.empty())
    {
        std::cout << "Filename of data is not specified.\n";
        return false;
    }

    if (!train_flag_ && model_filename_.empty())
    {
        std::cout << "Filename of trained model to evaluate accuracy is not specified.\n";
        return false;
    }

    if (train_flag_ && ((percent_trainset_ > 1) || (percent_trainset_ < 0.5)))
    {
        std::cout << "Bad percent to split data for train. Should be from 0.5 to 1.\n";
        return false;
    }

    if (train_flag_ && ((percent_trainset_ > 1) || (percent_trainset_ < 0.01)))
    {
        std::cout << "Bad percent of classifiers to train. Should be from 0.01 to 1.\n";
        return false;
    }
    
    if (train_flag_ && ((num_classifiers_ <= 0) || (num_classifiers_ > 1000)))
    {
        std::cout << "Amount of classifiers should be at least 1 and not more than 1000.\n";
        return false;
    }

    if ((balanced_flag_ != 1) && (balanced_flag_ != 0))
    {
        std::cout << "Balanced flag should be 0 or 1";
        return false;
    }

    if (save_period_ < 10)
    {
        std::cout << "Save period should be at least 10 iterations.";
        return false;
    }

    return true;
}

void Configuration::showParams()
{
    std::cout << 
        "\t--train  " << train_flag_ << '\n' <<
        "\t--data_filename  " << data_filename_ << '\n' <<
        "\t--model_filename  " << model_filename_ << '\n' <<
        "\t--percent_trainset  " << percent_trainset_ << '\n' <<
        "\t--percent_classifiers  " << percent_classifiers_ << '\n' <<
        "\t--num_classifiers  " << num_classifiers_ << '\n' <<
        "\t--save_period  " << save_period_ << '\n' << 
        "\t--balanced  " << balanced_flag_ << '\n';
}

const std::string& Configuration::get_data_filename() const
{
    return data_filename_;
}

const std::string& Configuration::get_model_filename() const
{
    return model_filename_;
}

double Configuration::get_percent_trainset() const
{
    return percent_trainset_;
}

int Configuration::get_num_classifiers() const
{
    return num_classifiers_;
}

bool Configuration::get_balanced_flag() const
{
    return balanced_flag_;
}

bool Configuration::get_train_flag() const
{
    return train_flag_;
}

int Configuration::get_save_period() const
{
    return save_period_;
}

double Configuration::get_percent_classifiers() const
{
    return percent_classifiers_;
}