#pragma once

#ifndef PDF_PDFSTROBJ_H_INCLUDED_
#define PDF_PDFSTROBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFStrObj :	public PDFObj
{
public:
	PDFStrObj(const unsigned int& nObjNum);
	PDFStrObj(const unsigned int& nObjNum, const bool& bBracket);
	virtual ~PDFStrObj(void);

	void setValue(const wchar_t* pStr);

	virtual int WriteObj(FILE* pFile);




private:
	std::wstring		myszValue;
	bool				mybBracket;





};
}
#endif