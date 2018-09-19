#pragma once

#ifndef PDF_PDFBOOLOBJ_H_INCLUDED_
#define PDF_PDFBOOLOBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFBoolObj :	public PDFObj
{
public:
	PDFBoolObj(const unsigned int& nObjNum);
	virtual ~PDFBoolObj(void);

	virtual int WriteObj(FILE* /*pFile*/){return NULL;}

};

}
#endif