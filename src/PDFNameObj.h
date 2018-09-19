#pragma once

#ifndef PDF_PDFNAMEOBJ_H_INCLUDED_
#define PDF_PDFNAMEOBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFNameObj :	public PDFObj
{
public:
	PDFNameObj(const unsigned int& nObjNum);
	virtual ~PDFNameObj(void);

	void setValue(const wchar_t* pStr);

	virtual int WriteObj(FILE* pFile);

private:
	std::wstring myszValue;
};

}
#endif