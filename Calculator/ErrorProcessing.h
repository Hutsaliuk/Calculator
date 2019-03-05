#ifndef ERRORPROCESSING_H
#define ERRORPROCESSING_H

#include <cstddef>

struct Error
{
    enum class Codes
	{
        eOK,
		eInvalidCharacter,
        eTooMuchOpeningBrackets,
        eTooMuchClosingBrackets,
        eWrongBrackets,
        eTooBigResult,
		eIncorrectSyntax,
		eUnknownOperation,
		eFormingNumber,
        eMissingOperation
	};

    Codes code;
    size_t position;

    Error();
	void showError();
    operator bool() const;
};

#endif // ERRORPROCESSING_H
