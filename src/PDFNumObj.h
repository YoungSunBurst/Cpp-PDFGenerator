#pragma once

#ifndef PDF_PDFNUMOBJ_H_INCLUDED_
#define PDF_PDFNUMOBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFNumObj :	public PDFObj
{

public:
	PDFNumObj(const unsigned int& nObjNum);
	virtual ~PDFNumObj(void);

	void setValue(const int& nInt);
	void addValue(const int& nInt);
	void setValue(const float& fFloat);

	virtual int WriteObj(FILE* pFile);

	int PDFNumObj::getValue() const 
	{
		return mynValue;
	}

private:
	float	myfValue;
	int		mynValue;
	bool	mybIsfloat;

};

}
#endif