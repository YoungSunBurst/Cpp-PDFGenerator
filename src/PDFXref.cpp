#include "stdafx.h"
#include "PDFXref.h"

namespace PDF{

PDFXref::PDFXref(const int& nOffset):
mynOffset(nOffset)
{
	init_();
	
}

PDFXref::~PDFXref(void)
{
	for(unsigned int i=0;i < myObjList.size();i++)
	{
		if(NULL != myObjList[i])
		{
			delete myObjList[i];
		}
	}
	delete myTrailer;
}

void PDFXref::init_()
{
	PDFObj* newObj= new PDFObj(myObjList.size(),0,PDF_MAX_GENERATION_NUM,EnumPDFInUseEntry_f,EnumPDFObjType_NULL);
	myObjList.push_back(newObj);

	//TO do init trailer
	myTrailer = new PDFDictObj(0);

	// Catalog
	myCatalogObj = new PDFDictObj(myObjList.size());
	myObjList.push_back(myCatalogObj);
	myCatalogObj->addValue(L"Type", myObjMaker.makeNameObj(L"Catalog"), EnumPDFObjType_Name);
	
	myTrailer->addValue(L"Root", myObjMaker.makeIndirectgObj(myCatalogObj), EnumPDFObjType_Indirect);
	// Rootpage
	myRootPageObj = new PDFDictObj(myObjList.size());
	myObjList.push_back(myRootPageObj );
	myRootPageObj->addValue(L"Type", myObjMaker.makeNameObj(L"Pages"), EnumPDFObjType_Name);
	myPageArrObj = myObjMaker.makeArrayObj() ;
	myRootPageObj->addValue(L"Kids", myPageArrObj, EnumPDFObjType_Array);
	mypPageCountObj = myObjMaker.makeNumObj(0);
	myRootPageObj->addValue(L"Count", mypPageCountObj, EnumPDFObjType_Numeric);

	myCatalogObj->addValue(L"Pages", myObjMaker.makeIndirectgObj(myRootPageObj), EnumPDFObjType_Indirect);
	
	// Informatiom
	myInfoObj = new PDFDictObj(myObjList.size());
	myObjList.push_back(myInfoObj);
	myInfoObj->addValue(L"Producer", myObjMaker.makeStrObj(L"A l p inion"), EnumPDFObjType_String);
	myTrailer->addValue(L"Info", myObjMaker.makeIndirectgObj(myInfoObj), EnumPDFObjType_Indirect);
}

void PDFXref::addPage(PDFObj* pObj)
{
	if(NULL != pObj)
	{
		myObjList.push_back(pObj);
		myPageArrObj->addValue( myObjMaker.makeIndirectgObj(pObj) );
		int nPage = mypPageCountObj->getValue();
		mypPageCountObj->setValue(++nPage);
	}
}

void PDFXref::addObj(PDFObj* pObj)
{
	if(NULL != pObj)
	{
		myObjList.push_back(pObj);
	}
}


bool PDFXref::writeAllObj(FILE *pFile)
{
	int nByte(0);
	nByte += writeHeader_(pFile);
	if(NULL != pFile)
	{
		for(unsigned int nObj=1; nObj < myObjList.size() ; nObj++)
		{
			if( NULL != myObjList[nObj])
			{
				myObjList[nObj]->setByteOffset(nByte);
				nByte +=fprintf_s(pFile, "%d %d obj\012", myObjList[nObj]->getObjNum(), myObjList[nObj]->getGenNum());
				nByte +=myObjList[nObj]->WriteObj(pFile);
				nByte +=fprintf_s(pFile, "\012endobj\012");
			}
		}
	}
	writeCrossReftable_(pFile);
	fprintf_s(pFile, "trailer\012");
	myTrailer->addValue(L"Size", myObjMaker.makeNumObj(myObjList.size()), EnumPDFObjType_Numeric);
	myTrailer->WriteObj(pFile);
	fprintf_s(pFile, "\012startxref\012");
	fprintf_s(pFile, "%d\012", nByte);
	fprintf_s(pFile, "%%%%EOF\012", nByte);
	return true;
}

int PDFXref::writeHeader_(FILE *pFile)
{
	int nRet(0);
	nRet = fprintf_s(pFile,PDFversionString[1]);
	return nRet;

}

int PDFXref::writeCrossReftable_(FILE *pFile)
{
	int nByte(0);
	nByte += fprintf_s(pFile,"xref\012");
	nByte += fprintf_s(pFile,"0 %d\012",myObjList.size() );
	char szByteNum[11],szGenNum[6];
	for(unsigned int nObj=0; nObj < myObjList.size() ; nObj++)
	{
		makeItoA_(szByteNum,myObjList[nObj]->getByteOffset(),10);
		makeItoA_(szGenNum,myObjList[nObj]->getGenNum(),5);
		nByte += fprintf_s(pFile,"%s %s %c\015\012",szByteNum, szGenNum, PDFInUseEntryString[myObjList[nObj]->getInUseType()]);
	}
	return nByte;
		
}

void PDFXref::makeItoA_(char* pDesString, const int& nSource, const int& nArrayNum)
{
	int nInt = nSource, nArr = nArrayNum;
	char* pDes = pDesString;
	pDes[nArr--]=0;
	while(nArr >= 0 )
	{
		pDes[nArr] = '0' + nInt%10;
		nInt /= 10 ;
		--nArr;
	}
	
}

}