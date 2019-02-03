#ifndef ADDITIONCHECKS_H
#define ADDITIONCHECKS_H

#include <string>

namespace AdditionChecks
{
	bool checkChars(std::string const &str, std::string &error);
	bool checkBrackets(std::string const &str, std::string &error);
	bool checkAdition(double const &arg1, double const &arg2, std::string &error);
	bool checkSubtraction(double const &arg1, double const &arg2, std::string &error);
	bool checkMultiplication(double const &arg1, double const &arg2, std::string &error);
	bool checkDivision(double const &arg1, double const &arg2, std::string &error);
	bool checkExponentiation(double const &arg1, double const &arg2, std::string &error);
};
#endif // ADDITIONCHECKS_H