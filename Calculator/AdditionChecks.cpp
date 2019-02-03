#include "AdditionChecks.h"
#include "ErrorProcessing.h"

using std::string;
using std::to_string;

bool AdditionChecks::checkChars(string const &str, string &error) //checking for unrestricted characters
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && (str[i] != '+') && (str[i] != '-') &&
			(str[i] != '*') && (str[i] != '/') && (str[i] != '(') &&
			(str[i] != ')') && (str[i] != '^') && (str[i] != '.') && (str[i] != 'e'))
		{
			error = to_string(ErrorProcessing::eInvalidCharacter) + to_string(i+1);
			//cout << "Invalid character: " << str[i] << endl << endl;
			return false;
		}
	}

	return true;
}

bool AdditionChecks::checkBrackets(string const & str, string &error)  //checking for unpair brackets
{
	int brackets = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			brackets++;
		}

		if (str[i] == ')')
		{
			brackets--;
		}
	}

	if (brackets > 0)
	{
		error = to_string(ErrorProcessing::eTooMuchOpenBrackets);
		//cout << "Error with brackets! \n\n";
		return false;
	}
	else if (brackets < 0)
	{
		error = to_string(ErrorProcessing::eTooMuchCloseBrackets);
		return false;
	}

	return true;
}

//check, if the resoult will be too big for type 'double' show error message
bool AdditionChecks::checkAdition(double const &arg1, double const &arg2, string &error)
{
	if ((((arg1 + arg2) > DBL_MIN) && ((arg1 + arg2) < DBL_MAX)) || 
		(((arg1 + arg2) > -DBL_MAX) && ((arg1 + arg2) < -DBL_MIN)) || ((arg1 + arg2) == 0))
	{
		return true;
	}
	else
	{
		error = to_string(ErrorProcessing::eTooBigResoult);
		return false;
	}
}

bool AdditionChecks::checkSubtraction(double const &arg1, double const &arg2, string &error)
{
	if ((((arg1 - arg2) > DBL_MIN) && ((arg1 - arg2) < DBL_MAX)) ||
		(((arg1 - arg2) > -DBL_MAX) && ((arg1 - arg2) < -DBL_MIN)) || ((arg1 + arg2) == 0))
	{
		return true;
	}
	else
	{
		error = to_string(ErrorProcessing::eTooBigResoult);
		return false;
	}
}

bool AdditionChecks::checkMultiplication(double const &arg1, double const &arg2, string &error)
{
	if ((((arg1 * arg2) > DBL_MIN) && ((arg1 * arg2) < DBL_MAX)) ||
		(((arg1 * arg2) > -DBL_MAX) && ((arg1 * arg2) < -DBL_MIN)) || ((arg1 + arg2) == 0))
	{
		return true;
	}
	else
	{
		error = to_string(ErrorProcessing::eTooBigResoult);
		return false;
	}
}

bool AdditionChecks::checkDivision(double const &arg1, double const &arg2, string &error)
{
	if ((((arg1 / arg2) > DBL_MIN) && ((arg1 / arg2) < DBL_MAX)) ||
		(((arg1 / arg2) > -DBL_MAX) && ((arg1 / arg2) < -DBL_MIN)) || ((arg1 + arg2) == 0))
	{
		return true;
	}
	else
	{
		error = to_string(ErrorProcessing::eTooBigResoult);
		return false;
	}
}

bool AdditionChecks::checkExponentiation(double const &arg1, double const &arg2, string &error)
{
	if (((pow(arg1, arg2) > DBL_MIN) && (pow(arg1, arg2) < DBL_MAX)) ||
		((pow(arg1, arg2) > -DBL_MAX) && (pow(arg1, arg2) < -DBL_MIN)) || ((arg1 + arg2) == 0))
	{
		return true;
	}
	else
	{
		error = to_string(ErrorProcessing::eTooBigResoult);
		return false;
	}
}

