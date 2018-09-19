#include "stdafx.h"
#include "PDFArrayObj.h"

namespace PDF{

PDFArrayObj::PDFArrayObj(const unsigned int& nObjNum)
: PDFObj(nObjNum, 0 , 0, EnumPDFInUseEntry_n, EnumPDFObjType_Boolean)
{
}

PDFArrayObj::~PDFArrayObj(void)
{
}

void PDFArrayObj::addValue(PDF::PDFObj *pObj)
{
	myValueList.push_back(pObj);
}

int PDFArrayObj::WriteObj(FILE *pFile)
{
	int nRet(0);
	if(NULL != pFile)
	{
		nRet += fprintf_s(pFile, "[ ");
		for(unsigned int i=0 ; i < myValueList.size() ; i++)
		{
			nRet += myValueList[i]->WriteObj(pFile);
			nRet += fprintf_s(pFile, " ");
		}
		nRet += fprintf_s(pFile, "]");
	}
	return nRet;
}

}