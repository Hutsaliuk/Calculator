#ifndef CHECKS_H
#define CHECKS_H

#include "ErrorProcessing.h"
#include <string>

namespace Checks
{
    Error Chars(std::string const &str);
    Error brackets(std::string const &str);
    bool addition(double const &arg1, double const &arg2);
    bool subtraction(double const &arg1, double const &arg2);
    bool multiplication(double const &arg1, double const &arg2);
    bool division(double const &arg1, double const &arg2);
    bool exponentiation(double const &arg1, double const &arg2);
};
#endif // CHECKS_H
