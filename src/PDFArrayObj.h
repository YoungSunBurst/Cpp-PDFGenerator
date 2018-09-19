#pragma once

#ifndef PDF_PDFARRAYOBJ_H_INCLUDED_
#define PDF_PDFARRAYOBJ_H_INCLUDED_
#include "PDFObj.h"

namespace PDF{

class PDFArrayObj :	public PDFObj
{
public:
	PDFArrayObj(const unsigned int& nObjNum);
	virtual ~PDFArrayObj(void);

	void		addValue(PDFObj* pObj);
	virtual int WriteObj(FILE* pFile);

private:
	std::vector<PDFObj*> myValueList;
};

}
#endif