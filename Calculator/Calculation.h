#ifndef CALCULATION_H
#define CALCULATION_H

#include "ErrorProcessing.h"
#include <vector>
#include <string>

namespace Calculation
{
	double openBrackets(std::string &e, int &sub_expr_count, Error &error);
	double breakApart(std::string const &e, Error &error); 
	double calculate(std::vector<int> &oper, std::vector<double> &num, int &oper_count, int &num_count, Error &error);
	double doOperation(double const &arg1, double const &arg2, int const &oper, Error &error);
	double formNumber(std::string const &e, size_t &i, Error &error);
	int countExpressionsInBrackets(std::string const &str);
	void removeSpaces(std::string &str);
};
#endif // CALCULATION_H