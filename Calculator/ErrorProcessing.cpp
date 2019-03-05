#include "ErrorProcessing.h"
#include <iostream>

using namespace std;

Error::Error() : code(Codes::eOK), position(0u)
{
}

void Error::showError()
{
	switch (code)
	{
	case Error::Codes::eInvalidCharacter:
		cout << "Error! Invalid character in \"" << position << "\" position of expression!\n\n";
		break;
    case Error::Codes::eTooMuchOpeningBrackets:
		cout << "Error! Close bracket(s) missing! \n\n";
		break;
    case Error::Codes::eTooMuchClosingBrackets:
		cout << "Error! Open bracket(s) missing! \n\n";
		break;
    case Error::Codes::eTooBigResult:
		cout << "Error! Resoult is too BIG! \n\n";
		break;
	case Error::Codes::eIncorrectSyntax:
		cout << "Error! Incorrect syntax in \"" << position << "\" position of expression!\n\n";
		break;
	case Error::Codes::eUnknownOperation:
		cout << "Error! Unknown operation! \n\n";
		break;
	case Error::Codes::eFormingNumber:
		cout << "Error! Some error while forming number in \"" << position << "\" position of expression!\n\n";
		break;
	case Error::Codes::eWrongBrackets:
		cout << "Error! Incorrect brackets! \n\n";
		break;
    case Error::Codes::eMissingOperation:
		cout << "Error! Operation missing between \"" << position << "\" and \""<< position + 1 << "\" position of expression!\n\n";
		break;
	default:
		cout << "Error! Unknown error! \n\n";
		break;
    }
}

Error::operator bool() const
{
    if (code == Codes::eOK){
        return false;
    }
    else {
        return true;
    }

}
