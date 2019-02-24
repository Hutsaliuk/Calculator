#include "ErrorProcessing.h"
#include <iostream>

using namespace std;

Error::Error() : errorCode(Errors::eNoError)
{
}

void Error::showError()
{
	switch (errorCode)
	{
	case Error::Errors::eInvalidCharacter:
		cout << "Error! Invalid character in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case Error::Errors::eTooMuchOpenBrackets:
		cout << "Error! Close bracket(s) missing! \n\n";
		break;
	case Error::Errors::eTooMuchCloseBrackets:
		cout << "Error! Open bracket(s) missing! \n\n";
		break;
	case Error::Errors::eTooBigResoult:
		cout << "Error! Resoult is too BIG! \n\n";
		break;
	case Error::Errors::eIncorrectSyntax:
		cout << "Error! Incorrect syntax in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case Error::Errors::eUnknownOperation:
		cout << "Error! Unknown operation! \n\n";
		break;
	case Error::Errors::eFormingNumber:
		cout << "Error! Some error while forming number in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case Error::Errors::eWrongBrackets:
		cout << "Error! Incorrect brackets! \n\n";
		break;
	case Error::Errors::eOperationMissing:
		cout << "Error! Operation missing between \"" << errorPosition << "\" and \""<< errorPosition + 1 << "\" position of expression!\n\n";
		break;
	default:
		cout << "Error! Unknown error! \n\n";
		break;
	}
}
