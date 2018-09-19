#include "stdafx.h"
#include "PDFStrObj.h"


namespace PDF{

PDFStrObj::PDFStrObj(const unsigned int& nObjNum)
: PDFObj(nObjNum, 0, 0, EnumPDFInUseEntry_n, EnumPDFObjType_Boolean), mybBracket(true)
{
	myszValue.clear();
}

PDFStrObj::PDFStrObj(const unsigned int& nObjNum, const bool& bBracket)
: PDFObj(nObjNum, 0, 0, EnumPDFInUseEntry_n, EnumPDFObjType_Boolean), mybBracket(bBracket)
{
	myszValue.clear();
}

PDFStrObj::~PDFStrObj(void)
{
}

void PDFStrObj::setValue(const wchar_t *pStr)
{
	myszValue = pStr;
}

int PDFStrObj::WriteObj(FILE *pFile)
{
	int nRet(0);
	if(NULL != pFile)
	{
		if(NULL != myszValue.c_str())
		{
			if(false != mybBracket)
			{
				nRet += wcPrintf(pFile, L"(%s)", myszValue.c_str());
			 }
			else
			{
				nRet += wcPrintf(pFile, L"%s", myszValue.c_str());
			}
		}
	} 
	return nRet;
}








}