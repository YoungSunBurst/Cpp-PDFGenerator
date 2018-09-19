#include "stdafx.h"
#include "PDFStreamObj.h"

namespace PDF{

PDFStreamObj::PDFStreamObj(const unsigned int& nObjNum)
: PDFObj(nObjNum,0,0,EnumPDFInUseEntry_n,EnumPDFObjType_Boolean)
,myDictObj(NULL), myStream(L""), mypBufferStream(NULL), mynBufferSize(0)
{
	myDictObj = new PDFDictObj(0);
}

PDFStreamObj::~PDFStreamObj(void)
{
	delete myDictObj;
}


int PDFStreamObj::WriteObj(FILE *pFile)
{
	int nRet(false);
	//if(NULL != myDictObj)
	//{
		/*wchar_t sz[32];
		wsprintf(sz,L"<<\012/Length %d %d R\012>>\012",myLengthObj->getObjNum(),myLengthObj->getGenNum());
		fwrite(sz,sizeof(wchar_t),wcslen(sz)+1,pFile);*/
		//nRet += fprintf_s(pFile,"<<\012/Length %d %d R\012>>\012stream\015\012",myLengthObj->getObjNum(),myLengthObj->getGenNum());
		if(NULL != myDictObj)
		{	
			nRet += myDictObj->WriteObj(pFile);
		}
		nRet += fprintf_s(pFile, "\012stream\015\012");
		if(NULL != mypBufferStream)
		{
			nRet += fwrite(mypBufferStream, sizeof(unsigned char), mynBufferSize, pFile);
			nRet += fprintf_s(pFile, "\012");
		}
		else if(0 != wcscmp(L"", myStream.c_str()))
		{
			nRet += wcPrintf(pFile, L"%s", myStream.c_str());
		}
		nRet += fprintf_s(pFile, "endstream");
//	}
	return nRet;

}


}