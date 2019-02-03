#ifndef ERRORPROCESSING_H
#define ERRORPROCESSING_H

#include <string>

namespace ErrorProcessing
{
	enum errors
	{
		eInvalidCharacter = 10,
		eTooMuchOpenBrackets,
		eTooMuchCloseBrackets,
		eTooBigResoult,
		eIncorrectSyntax,
		eUnknownOperation,
		eFormingNumber,
		eWrongBrackets,
		eOperationMissing
	};
	void showError(std::string const &error);
};

#endif // ERRORPROCESSING_H