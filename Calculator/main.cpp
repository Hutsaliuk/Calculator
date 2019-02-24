#include "Calculation.h"
#include "AdditionChecks.h"
#include "ErrorProcessing.h"
#include <iostream>

using namespace std;

void main()
{

	cout << "Enter an expression for calculation!" << endl;
	cout << "Enter \"e\" for close programm." << endl << endl;
	
	while (true)
	{
		string expr; //user input expression

		getline(cin, expr);

		Calculation::removeSpaces(expr);

		if ((expr != "E") && (expr != "e"))
		{
			Error error = AdditionChecks::checkChars(expr);

			if (!(int)error.errorCode)
			{
				error = AdditionChecks::checkBrackets(expr);

				if (!(int)error.errorCode)
				{
					int subExprCount = Calculation::countExpressionsInBrackets(expr); 
					double tmpAnswer = Calculation::openBrackets(expr, subExprCount, error); //Start calculating 
					if (!(int)error.errorCode)
					{
						cout << "Answer: " << tmpAnswer << endl << endl; //if there is no errors - show answer
					}
					else
					{
						error.showError();
					}
				}
				else
				{
					error.showError();
				}
			}
			else
			{
				error.showError();
			}
		}
		else
		{
			break;
		}
	}
}
