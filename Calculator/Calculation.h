#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <string>

namespace Calculation
{
	double openBrackets(std::string &e, int &sub_expr_count, std::string &error);
	double breakApart(std::string const &e, std::string &error); 
	double calculate(std::vector<int> &oper, std::vector<double> &num, int &oper_count, int &num_count, std::string &error);
	double doOperation(double const &arg1, double const &arg2, int const &oper, std::string &error);
	double formNumber(std::string const &e, size_t &i, std::string &error);
	int countExpressionsInBrackets(std::string const &str);
};
#endif // CALCULATION_H