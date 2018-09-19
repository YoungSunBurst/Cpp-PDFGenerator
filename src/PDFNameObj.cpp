#include "stdafx.h"
#include "PDFNameObj.h"

namespace PDF{

PDFNameObj::PDFNameObj(const unsigned int& nObjNum)
: PDFObj(nObjNum,0,0,EnumPDFInUseEntry_n,EnumPDFObjType_Boolean)
{
}

PDFNameObj::~PDFNameObj(void)
{
}

void PDFNameObj::setValue(const wchar_t *pStr)
{
	myszValue = pStr;
}

int PDFNameObj::WriteObj(FILE *pFile)
{
	int nRet(0);
	if(NULL != pFile)
	{
		nRet += wcPrintf(pFile,L"/%s",myszValue.c_str());
	}
	return nRet;
}

}