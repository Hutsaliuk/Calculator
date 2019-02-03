#include "ErrorProcessing.h"
#include <iostream>

using std::cout;
using std::endl;

void ErrorProcessing::showError(std::string const & error)
{
	unsigned short errorCode = std::stoi(error.substr(0, 2)); // 2 first digits - error code, other - error position
	size_t errorPosition;

	if (error.length()>2) // check, if there is additon information about error position
	{
		errorPosition = std::stoi(error.substr(2, error.length()));
	}

	switch (errorCode)
	{
	case eInvalidCharacter:
		cout << "Error! Invalid character in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case eTooMuchOpenBrackets:
		cout << "Error! Close bracket(s) missing! \n\n";
		break;
	case eTooMuchCloseBrackets:
		cout << "Error! Open bracket(s) missing! \n\n";
		break;
	case eTooBigResoult:
		cout << "Error! Resoult is too BIG! \n\n";
		break;
	case eIncorrectSyntax:
		cout << "Error! Incorrect syntax in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case eUnknownOperation:
		cout << "Error! Unknown operation! \n\n";
		break;
	case eFormingNumber:
		cout << "Error! Some error while forming number in \"" << errorPosition << "\" position of expression!\n\n";
		break;
	case eWrongBrackets:
		cout << "Error! Incorrect brackets! \n\n";
		break;
	case eOperationMissing:
		cout << "Error! Operation missing between \"" << errorPosition << "\" and \""<< errorPosition + 1 << "\" position of expression!\n\n";
		break;
	default:
		cout << "Error! Unknown error! \n\n";
		break;
	}
}
