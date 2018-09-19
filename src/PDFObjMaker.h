#pragma once

#ifndef PDF_PDFOBJMAKER_H_INCLUDED_
#define PDF_PDFOBJMAKER_H_INCLUDED_

#include "PDFBoolObj.h"
#include "PDFDictObj.h"
#include "PDFNumObj.h"
#include "PDFStrObj.h"
#include "PDFNameObj.h"
#include "PDFArrayObj.h"
#include "PDFStreamObj.h"
#include "PDFIndirectObj.h"

namespace PDF{

class PDFObjMaker
{
public:
	PDFObjMaker(void);
	virtual ~PDFObjMaker(void);

	/*PDFBoolObj* makeBoolObj(bool */
	PDFNumObj* makeNumObj(const int& nInt)
	{
		PDFNumObj* pTemp = new PDFNumObj(0);
		myObjList.push_back(pTemp);
		pTemp->setValue(nInt);
		return pTemp;
	}
	PDFStrObj* makeStrObj(const wchar_t* pStr)
	{
		PDFStrObj* pTemp = new PDFStrObj(0);
		myObjList.push_back(pTemp);
		pTemp->setValue(pStr);
		return pTemp;
	}
	PDFStrObj* makeStrObj(const wchar_t* pStr, const bool& bBracket)
	{
		PDFStrObj* pTemp = new PDFStrObj(0,bBracket);
		myObjList.push_back(pTemp);
		pTemp->setValue(pStr);
		return pTemp;
	}
	PDFNameObj* makeNameObj(const wchar_t* pStr)
	{
		PDFNameObj* pTemp = new PDFNameObj(0);
		myObjList.push_back(pTemp);
		pTemp->setValue(pStr);
		return pTemp;
	}
	PDFDictObj* makeDictObj()
	{
		PDFDictObj* pTemp = new PDFDictObj(0);
		myObjList.push_back(pTemp);
		return pTemp;
	}
	PDFArrayObj* makeArrayObj()
	{
		PDFArrayObj* pTemp = new PDFArrayObj(0);
		myObjList.push_back(pTemp);
		return pTemp;
	}
	PDFIndirectObj* makeIndirectgObj(PDFObj* pObj)
	{
		PDFIndirectObj* pTemp = new PDFIndirectObj(0);
		myObjList.push_back(pTemp);
		pTemp->setValue(pObj);
		return pTemp;
	}

private:
	std::vector<PDFObj*> myObjList;
};

}

#endif