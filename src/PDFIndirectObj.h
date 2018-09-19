#pragma once

#ifndef PDF_PDFINDIRECTOBJ_H_INCLUDED_
#define PDF_PDFINDIRECTOBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFIndirectObj :	public PDFObj
{
public:
	PDFIndirectObj(const unsigned int& nObjNum);
	virtual ~PDFIndirectObj(void);

	void setValue(PDFObj* pObj);

	virtual int WriteObj(FILE* pFile);

private:
	PDFObj* myValue;

};

}
#endif