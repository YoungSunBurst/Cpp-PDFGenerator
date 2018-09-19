#pragma once

#ifndef PDF_PDFXREF_H_INCLUDED_
#define PDF_PDFXREF_H_INCLUDED_

//#include "PDFObj.h"
#include "PDFObjMaker.h"

namespace PDF{

class PDFXref
{
public:
	PDFXref(const int& nOffset);
	virtual ~PDFXref(void);

	void 	addPage(PDFObj* pObj);
	void 	addObj(PDFObj* pObj);

	bool 	writeAllObj(FILE* pFile);

	PDFObj* getObj(const int& nObj) const 
	{
		PDFObj* pRet(NULL);
		if(nObj > (int)myObjList.size() && NULL != myObjList[nObj])
		{
			pRet = myObjList[nObj];
		}
		return pRet;
	}
	PDFObj* getRootPageObj() const 
	{
		return myRootPageObj;
	}

	unsigned int getObjCount() const
	{
		return myObjList.size();
	}

private:
	void	init_();
	int		writeHeader_(FILE* pFile);
	int		writeCrossReftable_(FILE* pFile);
	void	makeItoA_(char* pDesString, const int& nSource, const int& nArrayNum);
	
private: 
	PDFObjMaker					myObjMaker;
	std::vector<PDFObj*>		myObjList;	
	int							mynOffset;
	PDFDictObj*					myCatalogObj;
	PDFDictObj*					myRootPageObj;
	PDFArrayObj*				myPageArrObj;
	PDFDictObj*					myInfoObj;
	PDFDictObj*					myTrailer;
	PDFNumObj*					mypPageCountObj;
};

}

#endif