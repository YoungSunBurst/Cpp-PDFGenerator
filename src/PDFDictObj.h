#pragma once


#ifndef PDF_PDFDICTOBJ_H_INCLUDED_
#define PDF_PDFDICTOBJ_H_INCLUDED_

#include "PDFObj.h"

namespace PDF{

typedef struct _DictObjValue{
	_DictObjValue(const wchar_t* pKey, PDFObj* pValue, EnumPDFObjType eType) : myKey(pKey),mypValue(pValue), myeType(eType){}
	~_DictObjValue()
	{
		//switch(myeType){
		//case EnumPDFObjType_Name:
		//case EnumPDFObjType_String:
		//case EnumPDFObjType_String:
		//	{
		//		if(NULL != mypValue)
		//		{
		//			delete [](wchar_t*)mypValue;
		//		}
		//		break;
		//	}
		//case EnumPDFObjType_Array:
		//	{
		//		if(NULL != mypValue)
		//		{
		//			delete (std::vector<PDFObj*>*)mypValue;
		//		}
		//		break;
		//	}
		//case EnumPDFObjType_Numeric:
		//	{
		//		if(NULL != mypValue)
		//		{
		//			delete (int*)mypValue;
		//		}
		//		break;
		//	}
		//case EnumPDFObjType_Array:
		//	{
		//		delete (Rect*)mypValue;
		//	}
		//case EnumPDFObjType_Dictionary:
		//	{
		//		delete (PDFObj*)mypValue;
		//	}

		//default:
		//break;
		//}
	}
	std::wstring		myKey;
	PDFObj*				mypValue;
	EnumPDFObjType		myeType;
} DictObjValue;

class PDFDictObj :	public PDFObj
{
public:
	PDFDictObj(const unsigned int& nObjNum);
	virtual ~PDFDictObj(void);

	void		addValue(const wchar_t* pKey, PDFObj* pValue,const EnumPDFObjType& eType);
	PDFObj*		getValue(const wchar_t* pKey /*, EnumPDFObjType& eRetType*/ );

	virtual int WriteObj(FILE* pFile);

private:
	std::vector<DictObjValue*> myValuesList;
};

}

#endif