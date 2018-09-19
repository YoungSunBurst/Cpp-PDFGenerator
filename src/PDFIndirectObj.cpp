#include "stdafx.h"
#include "PDFIndirectObj.h"

namespace PDF{

PDFIndirectObj::PDFIndirectObj(const unsigned int& nObjNum)
: PDFObj(nObjNum,0,0,EnumPDFInUseEntry_n,EnumPDFObjType_Boolean)
{
}

PDFIndirectObj::~PDFIndirectObj(void)
{
}

void PDFIndirectObj::setValue(PDFObj *pObj)
{
	myValue = pObj;
}

int PDFIndirectObj::WriteObj(FILE *pFile)
{
	int nRet(0);	
	if(NULL != pFile)
	{
		if(NULL != myValue)
		{
			nRet += fprintf_s(pFile,"%d %d R",myValue->getObjNum(),myValue->getGenNum());
		}
	}
	return nRet;
}



}