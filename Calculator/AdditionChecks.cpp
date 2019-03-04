#include "AdditionChecks.h"
#include "ErrorProcessing.h"

#include <cfloat>

using namespace std;

Error AdditionChecks::checkChars(string const &str) //checking for unrestricted characters
{
	Error error;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && (str[i] != '+') && (str[i] != '-') &&
			(str[i] != '*') && (str[i] != '/') && (str[i] != '(') &&
			(str[i] != ')') && (str[i] != '^') && (str[i] != '.') && (str[i] != 'e'))
		{
			error.errorCode = Error::Errors::eInvalidCharacter;
			error.errorPosition = (i + 1);
			break;
		}
	}

	return error;
}

Error AdditionChecks::checkBrackets(string const &str)  //checking for unpair brackets
{
	Error error;

	int brackets = 0;

	for (char c : str)
	{
		if (c == '(')
		{
			brackets++;
		}

		if (c == ')')
		{
			brackets--;
		}
	}

	if (brackets > 0)
	{
		error.errorCode = Error::Errors::eTooMuchOpenBrackets;
		return error;
	}
	else if (brackets < 0)
	{
		error.errorCode = Error::Errors::eTooMuchCloseBrackets;
		return error;
	}

	return error;
}

//check, if the resoult will be too big for type 'double' show error message
bool AdditionChecks::checkAdition(double const &arg1, double const &arg2)
{
	if (arg1 >= 0)
	{
		return (arg2 < (DBL_MAX - arg1)) ? true : false;
	}
	else
	{
		return (arg2 > (-DBL_MAX - arg1)) ? true : false;
	}
}

bool AdditionChecks::checkSubtraction(double const &arg1, double const &arg2)
{
	if (arg1 >= 0)
	{
		return (arg2 > (-DBL_MAX + arg1)) ? true : false;
	}
	else
	{
		return (arg2 < (DBL_MAX + arg1)) ? true : false;
	}
}

bool AdditionChecks::checkMultiplication(double const &arg1, double const &arg2)
{
	return (abs(arg2) < (DBL_MAX / abs(arg1))) ? true : false;
}

bool AdditionChecks::checkDivision(double const &arg1, double const &arg2)
{
	return true; // temporary
}

bool AdditionChecks::checkExponentiation(double const &arg1, double const &arg2)
{
	return true; //temporary
}

