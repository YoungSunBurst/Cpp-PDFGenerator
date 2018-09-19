#pragma once

#ifndef PDF_PDFOBJ_H_INCLUDED_
#define PDF_PDFOBJ_H_INCLUDED_

#include "PDFDefine.h"

namespace PDF{

class PDFObj
{
public:
	PDFObj(const unsigned int& nObjNum, const int& nByteOffset, const int& nGenNum, const EnumPDFInUseEntry& eUseType, const EnumPDFObjType& eObjType);
	virtual ~PDFObj(void);

	unsigned int getObjNum()
	{
		return mynObjNum;
	}

	int getByteOffset()
	{
		return mynByteOffset;
	}

	int getGenNum()
	{
		return mynGenNum;
	}

	EnumPDFInUseEntry getInUseType()
	{
		return myeUseType;
	}

	void setByteOffset(const int& nByte)
	{
		mynByteOffset = nByte; 
	}

	virtual int WriteObj(FILE* /*pFile*/){return NULL;}

protected:
	virtual void init_();

protected:
	int					mynByteOffset;
	unsigned int		mynObjNum;				
	int					mynGenNum;
	EnumPDFInUseEntry	myeUseType;
	EnumPDFObjType		myeObjType;

};

}


#endif