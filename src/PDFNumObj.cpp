#include "stdafx.h"
#include "PDFNumObj.h"

namespace PDF{

PDFNumObj::PDFNumObj(const unsigned int& nObjNum)
: PDFObj(nObjNum,0,0,EnumPDFInUseEntry_n,EnumPDFObjType_Boolean)
, mynValue(0), myfValue(0.f), mybIsfloat(false)
{
}

PDFNumObj::~PDFNumObj(void)
{
}

void PDFNumObj::setValue(const int& nInt)
{
	mynValue=nInt;
	mybIsfloat = false;
}

void PDFNumObj::addValue(const int& nInt)
{
	mynValue+=nInt;
	mybIsfloat = false;
}

void PDFNumObj::setValue(const float& fFloat)
{
	myfValue=fFloat;
	mybIsfloat = true;
}


int PDFNumObj::WriteObj(FILE* pFile)
{
	int nRet(0);
	if(false != mybIsfloat)
	{
		nRet += fprintf_s(pFile,"%f",myfValue);
	}
	else
	{
		nRet += fprintf_s(pFile,"%d",mynValue);
	}
	return nRet;
}

}