#pragma once

#ifndef PDF_PDFSTREAMOBJ_H_INCLUDED_
#define PDF_PDFSTREAMOBJ_H_INCLUDED_
//#include "PDFObj.h"
#include "PDFDictObj.h"

namespace PDF{

class PDFStreamObj :	public PDFObj
{
public:
	PDFStreamObj(const unsigned int& nObjNum);
	virtual ~PDFStreamObj(void);

	void setDictObj(PDFDictObj* pObj)
	{
		myDictObj = pObj;
	}

	void AddDictValue(const wchar_t* pKey, PDFObj* pValue, const EnumPDFObjType& eType)
	{
		myDictObj->addValue(pKey, pValue, eType);
	}

	void setStream(const wchar_t* pValue)
	{
		myStream = pValue;
	}
	
	void setStream(unsigned char* pBuffer,const unsigned int& size)
	{
		mynBufferSize = size;
		mypBufferStream = new unsigned char[mynBufferSize];
		memcpy(mypBufferStream, pBuffer, mynBufferSize);
	}

	void addStream(const wchar_t* pValue)
	{
		myStream += pValue;
	}

	virtual int WriteObj(FILE* pFile);

private:
	PDFDictObj*			myDictObj;
	std::wstring		myStream;
	unsigned char*		mypBufferStream;
	unsigned int		mynBufferSize;

};

}

#endif