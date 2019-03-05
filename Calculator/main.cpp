#include "Calculation.h"
#include "Checks.h"
#include "ErrorProcessing.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{

	cout << "Enter an expression for calculation!" << endl;
	cout << "Enter \"e\" for close programm." << endl << endl;
	
	while (true)
	{
		string expr; //user input expression

		getline(cin, expr);

        expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

		if ((expr != "E") && (expr != "e"))
		{
            Error error = Checks::Chars(expr);

            if (!error)
			{
                error = Checks::brackets(expr);

                if (!error)
				{
                    long subExprCount = count(expr.begin(), expr.end(), '('); //Calculation::countExpressionsInBrackets(expr);
					double tmpAnswer = Calculation::openBrackets(expr, subExprCount, error); //Start calculating 
                    if (!error)
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
    return 0;
}
