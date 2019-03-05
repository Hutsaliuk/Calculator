#include "Calculation.h"
#include "Checks.h"
#include "ErrorProcessing.h"
#include <cmath>

using namespace std;

double Calculation::openBrackets(string &expr, long &subExprCount, Error &error) //Getting expression in brackets and replace them by number
{
    double tmpAnsw = 0.0;

	do
	{
        size_t openPos = 0u;
        size_t closePos = 0u;
		bool found = false;

        for (size_t i = 0u; i < expr.length(); i++)
		{
            if (expr[i] == '(')
			{
                if ((i == 0u) || !isdigit(expr[i-1u])) //check if there is some operation before brackets
				{
					openPos = i;
					found = true;
				}
				else
				{
                    error.code = Error::Codes::eMissingOperation;
					error.position = (i);
					break;
				}
			}
            else if (expr[i] == ')' && found)
			{
                if ((i == expr.length() - 1u) || (!isdigit(expr[i+1u]))) //check if there is some operation after brackets
				{
					closePos = i;
                    string tmpstr = expr.substr(openPos + 1u, (i - openPos) - 1u); //Get expression in brackets
					tmpAnsw = breakApart(tmpstr, error); //Calculating part of expression
                    expr = expr.substr(0, openPos) + std::to_string(tmpAnsw) + expr.substr(closePos + 1u, (expr.length() - closePos)); //raplace extension in brackets by number
                    subExprCount--;
					break;
				}
				else
				{
                    error.code = Error::Codes::eMissingOperation;
                    error.position = i + 1u;
					break;
				}
			}
		}

		if (openPos > closePos)
		{
            error.code = Error::Codes::eWrongBrackets;
		}

        if (error)
		{
			break;
		}

    } while (subExprCount > 0);

    if (!error)
	{
        tmpAnsw = breakApart(expr, error);
	}

    if (!error)
	{
		return tmpAnsw;
	}

    return 0.0;
}

double Calculation::breakApart(string const &expr, Error &error)
{
    vector<Operation> operations; //vector of operations
    vector<double> numbers; //vector of numbers

    for (size_t i = 0u; i < expr.length(); i++)
	{
        if (isdigit(expr[i]))
        {
            numbers.push_back(Calculation::formNumber(expr, i, error));
        }

        bool smallCheck = ((i > 0) && (i < expr.length()-1)); //small check to avoid repetitions

        if ((expr[i] == '+') && smallCheck && (isdigit(expr[i - 1u])))	operations.push_back(Operation::addition);
        else if ((expr[i] == '-') && smallCheck && (isdigit(expr[i - 1u])))	operations.push_back(Operation::subtraction);
        else if ((expr[i] == '-') && smallCheck && (isdigit(expr[i + 1u]))) {}//additional check, to avoid error if there is two '-' (one is the subtraction operation, second - negative number		}
        else if ((expr[i] == '*') && smallCheck && (isdigit(expr[i - 1u])))	operations.push_back(Operation::multiplication);
        else if ((expr[i] == '/') && smallCheck && (isdigit(expr[i - 1u]))) operations.push_back(Operation::division);
        else if ((expr[i] == '^') && smallCheck && (isdigit(expr[i - 1u])))	operations.push_back(Operation::exponentiation);
        else if ((expr[i] == '-') && (i == 0) && (expr.length()>1) && (isdigit(expr[i + 1u]))) {}//additional check, if '-' is at the beginning of the expression
        else if (i < expr.length())
		{
            error.code = Error::Codes::eIncorrectSyntax;
            error.position = i + 1u;
			break;
		}
	}

    if (!error) //if there is no errors continue calculating
	{
        size_t operationCount = operations.size();
        size_t numberCount = numbers.size();
        return calculate(operations, numbers, operationCount, numberCount, error);
	}

    return 0.0;
}

double Calculation::calculate(vector<Operation> &oper, vector<double> &num, size_t &operCount, size_t &numCount, Error &error) //step by step calculation of expression, according to the priorities of operations
{
	bool hasExponentiation = true;

    while (numCount > 1)
	{
        size_t operationPriority = 0u;  //operation, that will be counted next. If there is no more priority operation (*, /, ^), calculated the first

        if (hasExponentiation)
		{
            for (size_t i = 0u; i < operCount; i++)
			{
                if (oper[i] == Operation::exponentiation)
				{
					operationPriority = i;
					break;
				}
                else if (i == (operCount - 1u))
				{
					hasExponentiation = false;
				}
			}
		}
		if (!hasExponentiation)
		{
            for (size_t i = 0u; i < operCount; i++)
			{
                if ((oper[i] == Operation::multiplication) || (oper[i] == Operation::division))
				{
					operationPriority = i;
					break;
				}
			}
		}
		num[operationPriority] = doOperation(num[operationPriority], num[operationPriority + 1], oper[operationPriority], error);

        for (size_t i = operationPriority + 1u; i < numCount; i++) //move array of the numbers to the left
		{
            num[i] = num[i + 1u];
		}
        for (size_t i = operationPriority; i < operCount; i++) //move array of the operations to the left
		{
            oper[i] = oper[i + 1u];
		}
        numCount--;
        operCount--;
	}

	return num[0];
}

//count one operation
double Calculation::doOperation(double const &arg1, double const &arg2, Operation const &oper, Error &error)
{
	switch (oper)
	{
        case Operation::addition:
		{
            if (Checks::addition(arg1, arg2))
			{
				return (arg1 + arg2);
			}
			else
			{
                error.code = Error::Codes::eTooBigResult;
                return 0.0;
            }
		}
        case Operation::subtraction:
		{
			if (Checks::subtraction(arg1, arg2))
			{
				return (arg1 - arg2);
			}
			else
			{
                error.code = Error::Codes::eTooBigResult;
                return 0.0;
            }
		}
        case Operation::multiplication:
		{
			if (Checks::multiplication(arg1, arg2))
			{
				return (arg1 * arg2);
			}
			else
			{
                error.code = Error::Codes::eTooBigResult;
                return 0.0;
            }
		}
        case Operation::division:
		{
			if (Checks::division(arg1, arg2))
			{
				return (arg1 / arg2);
			}
			else
			{
                error.code = Error::Codes::eTooBigResult;
                return 0.0;
            }
		}
        case Operation::exponentiation:
		{
			if (Checks::exponentiation(arg1, arg2))
			{
				return pow(arg1, arg2);
			}
			else
			{
                error.code = Error::Codes::eTooBigResult;
                return 0.0;
            }
		}
		default:
		{
            error.code = Error::Codes::eUnknownOperation;
            return 0.0;
		}
	}
}

double Calculation::formNumber(string const &expr, size_t &i, Error &error)
{
	bool hasDot = false; //number already has dot
	bool hasE = false;
	string number = "";

    while ((i < expr.length()) && (isdigit(expr[i]) || (expr[i] == '.') || (expr[i] == 'e')))
	{
        if (isdigit(expr[i]))
		{
            number += expr[i];

			if (i > 0)	//additional check, to avoid error if there is first symbol of expression
			{
                if ((expr[i - 1] == '-') && ((i < 2) || (!isdigit(expr[i - 2])))) // ckeck and make negative number
				{
					number.insert(0, "-");
				}
			}
		}
        else if ((expr[i] == '.') && !hasDot)
		{
            number += expr[i];
			hasDot = true;
		}
        else if ((expr[i] == 'e') && !hasE)
		{
            number += expr[i];
			hasE = true;
            if (((i + 2) < expr.length()) && (expr[i + 1] == '-')) // if there is negative number after e
			{
				i++;
                number += expr[i];
			}
		}
		else
		{
            error.code = Error::Codes::eFormingNumber;
			error.position = i + 1;
			break;
		}

		i++;
	}

    return stod(number);
}

/*int Calculation::countExpressionsInBrackets(std::string const & str) //calculate expressions in brackets
{
	int count = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			count++;
		}
	}

	return count;
}

void Calculation::removeSpaces(std::string & str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str.erase(i, 1);
			i--;	//if there is spaces in the begining, 'i' became "negative", but in real thay have garbage instead negative number. Shoud I use "int" instead of "size_t" ??
		}
	}
}*/
