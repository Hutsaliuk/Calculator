#ifndef ADDITIONCHECKS_H
#define ADDITIONCHECKS_H

#include "ErrorProcessing.h"
#include <string>

namespace AdditionChecks
{
	Error checkChars(std::string const &str);
	Error checkBrackets(std::string const &str);
	bool checkAdition(double const &arg1, double const &arg2);
	bool checkSubtraction(double const &arg1, double const &arg2);
	bool checkMultiplication(double const &arg1, double const &arg2);
	bool checkDivision(double const &arg1, double const &arg2);
	bool checkExponentiation(double const &arg1, double const &arg2);
};
#endif // ADDITIONCHECKS_H