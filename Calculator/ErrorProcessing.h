#ifndef ERRORPROCESSING_H
#define ERRORPROCESSING_H

#include <cstddef>

struct Error
{
	Error();

    enum class Errors
	{
		eNoError,
		eInvalidCharacter,
		eTooMuchOpenBrackets,
		eTooMuchCloseBrackets,
		eTooBigResoult,
		eIncorrectSyntax,
		eUnknownOperation,
		eFormingNumber,
		eWrongBrackets,
		eOperationMissing
	};

	Errors errorCode;
	size_t errorPosition;

	void showError();
};

#endif // ERRORPROCESSING_H
