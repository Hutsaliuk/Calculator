#ifndef CALCULATION_H
#define CALCULATION_H

#include "ErrorProcessing.h"
#include <vector>
#include <string>

namespace Calculation
{
    enum class Operation
    {
        addition = 1, // +
        subtraction, // -
        multiplication, // *
        division, // /
        exponentiation // ^
    };

    double openBrackets(std::string &expr, long &subExprCount, Error &error);
    double breakApart(std::string const &expr, Error &error);
    double calculate(std::vector<Operation> &oper, std::vector<double> &num, size_t &operCount, size_t &numCount, Error &error);
    double doOperation(double const &arg1, double const &arg2, Operation const &oper, Error &error);
    double formNumber(std::string const &expr, size_t &i, Error &error);
    //int countExpressionsInBrackets(std::string const &str);
    //void removeSpaces(std::string &str);
};
#endif // CALCULATION_H
