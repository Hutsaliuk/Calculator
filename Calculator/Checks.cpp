#include "Checks.h"
#include "ErrorProcessing.h"

#include <cmath>
#include <cfloat>

using namespace std;

Error Checks::Chars(string const &str) //checking for unrestricted characters
{
	Error error;

    for (size_t i = 0u; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && (str[i] != '+') && (str[i] != '-') &&
			(str[i] != '*') && (str[i] != '/') && (str[i] != '(') &&
			(str[i] != ')') && (str[i] != '^') && (str[i] != '.') && (str[i] != 'e'))
		{
			error.code = Error::Codes::eInvalidCharacter;
            error.position = (i + 1u);
			break;
		}
	}

	return error;
}

Error Checks::brackets(string const &str)  //checking for unpair brackets
{
	Error error;

	int brackets = 0;

    for (char c : str)
    {
        if (c == '(')
        {
			brackets++;
		}
        else if (c == ')')
        {
            brackets--;
        }
	}

	if (brackets > 0)
	{
        error.code = Error::Codes::eTooMuchOpeningBrackets;
	}
	else if (brackets < 0)
	{
        error.code = Error::Codes::eTooMuchClosingBrackets;
	}

	return error;
}

//check, if the resoult will be too big for type 'double' show error message
bool Checks::addition(double const &arg1, double const &arg2)
{
    if (arg1 >= 0.0)
	{
        return (arg2 < (DBL_MAX - arg1));
	}
	else
	{
        return (arg2 > (-DBL_MAX - arg1));
	}
}

bool Checks::subtraction(double const &arg1, double const &arg2)
{
    if (arg1 >= 0.0)
	{
        return (arg2 > (-DBL_MAX + arg1));
	}
	else
	{
        return (arg2 < (DBL_MAX + arg1));
	}
}

bool Checks::multiplication(double const &arg1, double const &arg2)
{
    return (abs(arg2) < (DBL_MAX / abs(arg1)));
}

bool Checks::division(double const &arg1, double const &arg2)
{
    return (abs(arg1) > (DBL_MIN * abs(arg2)));
}

bool Checks::exponentiation(double const &arg1, double const &arg2)
{
    if (arg2 > 0.0)
    {
        return (abs(arg1) < DBL_MAX / pow(arg1, arg2 - 1));
    }
    else
    {
        return (abs(arg1) > DBL_MIN / pow(arg1, arg2 -1));
    }
}

