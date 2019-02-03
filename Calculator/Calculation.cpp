#include "Calculation.h"
#include "AdditionChecks.h"
#include "ErrorProcessing.h"

using std::string;
using std::vector;
using std::to_string;

double Calculation::openBrackets(string &e, int &sub_expr_count, string &error) //Getting expression in brackets and replace them by number
{
	int openPos = 0;
	int closePos = 0;
	double tmpAnsw;
	string tmpstr; //substring that we can calculate
	bool found = false;

	do
	{
		for (size_t i = 0; i < e.length(); i++)
		{
			if (e[i] == '(')
			{
				if ((i == 0) || ((i > 0) && !isdigit(e[i-1]))) //check if there is some operation before brackets
				{
					openPos = i;
					found = true;
				}
				else
				{
					error = to_string(ErrorProcessing::eOperationMissing) + to_string(i);
					break;
				}
			}
			if (e[i] == ')' && found)
			{
				if ((i == e.length()) || ((i < e.length()) && (!isdigit(e[i+1])))) //check if there is some operation after brackets
				{
					closePos = i;
					tmpstr = e.substr(openPos + 1, (i - openPos) - 1); //Get expression in brackets
					tmpAnsw = breakApart(tmpstr, error); //Calculating part of expression
					e = e.substr(0, openPos) + std::to_string(tmpAnsw) + e.substr(closePos + 1, (e.length() - closePos)); //raplace extension in brackets by number
					sub_expr_count--;
					break;
				}
				else
				{
					error = to_string(ErrorProcessing::eOperationMissing) + to_string(i+1);
					break;
				}
			}
		}

		if (openPos > closePos)
		{
			error = to_string(ErrorProcessing::eWrongBrackets);
		}

		found = false;
		openPos = 0;
		closePos = 0;

		if (!error.empty())
		{
			break;
		}

	} while (sub_expr_count > 0);

	if (error.empty())
	{
		tmpAnsw = breakApart(e, error);
	}

	if (error.empty())
	{
		return tmpAnsw;
	}

	return 0;
}

enum operationSigns
{
	adition = 1, // +
	subtraction, // -
	multiplication, // *
	division, // /
	exponentiation // ^
};

double Calculation::breakApart(string const &e, std::string &error)
{
	vector<int> operations(e.length(), 0); //vector of operations
	vector<double> numbers(e.length(), 0); //vector of numbers
	int operationCount = 0; //amount of operation
	int numberCount = 0; //amount of numbers

	for (size_t i = 0; i < e.length(); i++)
	{
		if (isdigit(e[i]))	numbers[numberCount++] = Calculation::formNumber(e, i, error);

		if ((e[i] == '+') && (i > 0) && (i < e.length()) && (isdigit(e[i - 1])))	operations[operationCount++] = adition;
		else if ((e[i] == '-') && (i > 0) && (i < e.length()) && (isdigit(e[i - 1])))	operations[operationCount++] = subtraction;
		else if ((e[i] == '-') && (i > 0) && (i < e.length()) && (isdigit(e[i + 1]))) {}//additional check, to avoid error if there is two '-' (one is the subtraction operation, second - negative number		}
		else if ((e[i] == '*') && (i > 0) && (i < e.length()) && (isdigit(e[i - 1])))	operations[operationCount++] = multiplication;
		else if ((e[i] == '/') && (i > 0) && (i < e.length()) && (isdigit(e[i - 1]))) operations[operationCount++] = division;
		else if ((e[i] == '^') && (i > 0) && (i < e.length()) && (isdigit(e[i - 1])))	operations[operationCount++] = exponentiation;
		else if ((e[i] == '-') && (i == 0) && (isdigit(e[i + 1]))) {}//additional check, if '-' is at the beginning of the expression
		else if (i < e.length())
		{
			error = to_string(ErrorProcessing::eIncorrectSyntax) + to_string(i + 1);
			break;
		}
	}

	if (error.empty()) //if there is no errors continue calculating
	{
		return calculate(operations, numbers, operationCount, numberCount, error);
	}

	return 0;
}

double Calculation::calculate(vector<int> &oper, vector<double> &num, int & oper_count, int &num_count, std::string &error) //step by step calculation of expression, according to the priorities of operations
{
	int operationPriority; //operation, that will be counted next. If there is no more priority operation (*, /, ^), calculated the first
	bool hasExponentiation = true;

	while (num_count > 1)
	{
		operationPriority = 0;
		if (hasExponentiation)
		{
			for (size_t i = 0; i < oper_count; i++)
			{
				if (oper[i] > 4)
				{
					operationPriority = i;
					break;
				}
				else if (i == (oper_count - 1))
				{
					hasExponentiation = false;
				}
			}
		}
		if (!hasExponentiation)
		{
			for (size_t i = 0; i < oper_count; i++)
			{
				if (oper[i] > 2)
				{
					operationPriority = i;
					break;
				}
			}
		}
		num[operationPriority] = doOperation(num[operationPriority], num[operationPriority + 1], oper[operationPriority], error);

		for (size_t i = operationPriority + 1; i < num_count; i++) //move array of the numbers to the left
		{
			num[i] = num[i + 1];
		}
		for (size_t i = operationPriority; i < oper_count; i++) //move array of the operations to the left
		{
			oper[i] = oper[i + 1];
		}
		num_count--;
		oper_count--;
	}

	return num[0];
}

//count one operation
double Calculation::doOperation(double const &arg1, double const &arg2, int const &oper, std::string &error)
{
	switch (oper)
	{
	case adition:
	{
		if (AdditionChecks::checkAdition(arg1, arg2, error))
		{
			return (arg1 + arg2);
		}
		break;
	}
	case subtraction:
	{
		if (AdditionChecks::checkSubtraction(arg1, arg2, error))
		{
			return (arg1 - arg2);
		}
		break;
	}
	case multiplication:
	{
		if (AdditionChecks::checkMultiplication(arg1, arg2, error))
		{
			return (arg1 * arg2);
		}
		break;
	}
	case division:
	{
		if (AdditionChecks::checkDivision(arg1, arg2, error))
		{
			return (arg1 / arg2);
		}
		break;
	}
	case exponentiation:
	{
		if (AdditionChecks::checkExponentiation(arg1, arg2, error))
		{
			return pow(arg1, arg2);
		}
		break;
	}
	default:
	{
		error = to_string(ErrorProcessing::eUnknownOperation);
	}
	}
}

double Calculation::formNumber(string const &e, size_t &i, std::string &error)
{
	bool hasDot = false; //number already has dot
	bool hasE = false;
	string number = "";

	while (isdigit(e[i]) || (e[i] == '.') || (e[i] == 'e'))
	{
		if (isdigit(e[i]))
		{
			number += e[i];

			if (i > 0)	//additional check, to avoid error if there is first symbol of expression
			{
				if ((e[i - 1] == '-') && ((i < 2) || (!isdigit(e[i - 2])))) // ckeck and make negative number
				{
					number.insert(0, "-");
				}
			}
		}
		else if ((e[i] == '.') && !hasDot)
		{
			number += e[i];
			hasDot = true;
		}
		else if ((e[i] == 'e') && !hasE)
		{
			number += e[i];
			hasE = true;
			if (((i + 2) < e.length()) && (e[i + 1] == '-')) // if there is negative number after e
			{
				i++;
				number += e[i];
			}
		}
		else
		{
			error = to_string(ErrorProcessing::eFormingNumber) + to_string(i+1);
			break;
		}

		i++;
	}

	return stod(number);
}

int Calculation::countExpressionsInBrackets(std::string const & str) //calculate expressions in brackets
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
