#include "stdafx.h"
#include "PDFDictObj.h"
//#include "PDFArrayObj.h"

namespace PDF{

PDFDictObj::PDFDictObj(const unsigned int& nObjNum) 
:PDFObj(nObjNum,0,0,EnumPDFInUseEntry_n,EnumPDFObjType_Dictionary)
{
}

PDFDictObj::~PDFDictObj(void)
{
	for(unsigned int i=0;i < myValuesList.size();i++)
	{
		if(NULL != myValuesList[i])
		{
			delete myValuesList[i];
		}
	}
}

void PDFDictObj::addValue(const wchar_t* pKey, PDFObj* pValue, const EnumPDFObjType& eType)
{

	//switch(eType)
	//{
	//case EnumPDFObjType_Array:
	//	{
	//		bool bExist(false);
	//		for(unsigned int i=0; i < myValuesList.size() ; i++)
	//		{
	//			if(0 == wcscmp(pKey,myValuesList[i]->myKey.c_str()))
	//			{
	//				PDFArrayObj* pList=(PDFArrayObj*)myValuesList[i]->mypValue;
	//				pList->addValue(pValue);
	//				bExist = true;
	//				break;
	//			}
	//		}
	//		if(false == bExist)
	//		{
	//			PDFArrayObj* pNewList = new PDFArrayObj;
	//			if(NULL != pValue)
	//			{
	//				pNewList->addValue((PDFObj*)pValue);
	//			}
	//			DictObjValue* TempValue = new DictObjValue(pKey,pNewList,eType);
	//		}
	//		break;
	//	}
	//default:
	DictObjValue* pDictValue = new DictObjValue(pKey, pValue, eType);
	myValuesList.push_back(pDictValue);

//		break;
	//}
}

PDFObj* PDFDictObj::getValue(const wchar_t* pKey /*, EnumPDFObjType& eRetType*/ )
{
	PDFObj* pRet(NULL);
	for(unsigned int i=0 ; i < myValuesList.size() ; i++)
	{
		if(0==wcscmp(myValuesList[i]->myKey.c_str(), pKey))
		{
			pRet = myValuesList[i]->mypValue;
			break;
		}
	}
	return pRet;
}

int PDFDictObj::WriteObj(FILE *pFile)
{
	int nRet(0);
	nRet += fprintf_s(pFile,"<<\012");
	for(unsigned int i=0; i < myValuesList.size() ; i++)
	{
		nRet += wcPrintf(pFile,L"/%s ",myValuesList[i]->myKey.c_str());
		nRet += myValuesList[i]->mypValue->WriteObj(pFile);
		nRet += fprintf_s(pFile,"\012");
	}
	nRet += fprintf_s(pFile,">>");
	return nRet;

}







} 