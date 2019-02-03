#include "Calculation.h"
#include "AdditionChecks.h"
#include "ErrorProcessing.h"
#include <iostream>

using std::cout;
using std::endl;

void main()
{
	std::string expr; //user input expression
	double tmpAnswer = 0;
	int subExprCount = 0; // amount of expressions in brackets
	std::string error;
	bool e = false; //exit flag
	cout << "Enter an expression for calculation!" << endl;
	cout << "Enter \"e\" for close programm." << endl << endl;
	
	while (!e)
	{
		error = "";
		std::cin >> expr;
		if ((expr != "E") && (expr != "e"))
		{
			if (AdditionChecks::checkChars(expr, error) && AdditionChecks::checkBrackets(expr, error))
			{
				subExprCount = Calculation::countExpressionsInBrackets(expr);
				tmpAnswer = Calculation::openBrackets(expr, subExprCount, error); //Start calculating 
				if (error.empty())
				{
					cout << "Answer: " << tmpAnswer << endl << endl; //if there is no errors - show answer
				}
				else
				{
					ErrorProcessing::showError(error);
				}
			}
			else
			{
				ErrorProcessing::showError(error);
			}
		}
		else
		{
			e = true;
		}
	}
}
