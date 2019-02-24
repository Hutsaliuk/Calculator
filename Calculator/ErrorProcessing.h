#ifndef ERRORPROCESSING_H
#define ERRORPROCESSING_H

struct Error
{
	Error();

	const enum class Errors
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