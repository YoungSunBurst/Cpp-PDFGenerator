#pragma once

#ifndef PDF_PDFPAGE_H_INCLUDED_
#define PDF_PDFPAGE_H_INCLUDED_
#include "PDFXref.h"
#include <map>

namespace PDF {
	
typedef enum enumPDFRotate
{
	enumPDFRotate_0		=0,
	enumPDFRotate_90	=1,
	enumPDFRotate_180	=2,
	enumPDFRotate_270	=3,
	enumPDFRotate_count =4
};

class PDFPage
{
public:
	PDFPage(PDFXref* pXref, const int& nWidth, const int& nHeight);
	virtual ~PDFPage(void);

	void writeTextStream(const wchar_t* pStream);

	int getPageHeight() const 
	{
		return mynPageHeight;
	}

	void setFont(const EnumPDFFontType& eType);

	void addImageObj(unsigned char* pBuffer, const unsigned int& nSize, const int& width, const int& height, const Rect& rect, const int& nBPC, const EnumPDFImgDecodeType& eDecType, const enumPDFRotate& eRotate);

private:
	void init_();

private:
	PDFObjMaker					myObjMaker;
	PDFXref*					mypPXref;
	PDFDictObj*					mypPageObj;
	PDFStreamObj*				mypContentsObj;
	PDFNumObj*					mypLengthObj;	
	PDFDictObj*					mypResourceObj;
	//PDFDictObj*					mypPageFontObj;
	PDFDictObj*					mypFontListObj;
	PDFDictObj*					mypImageListObj;
	PDFDictObj*					mypFontObj[EnumPDFFontType_Count];
	int							mynPageWidth;
	int							mynPageHeight;
	std::vector<PDFStreamObj*>	mypImageObj;
	/*std::map<EnumPDFFontType,PDFDictObj*> myFontTypeMap;*/
};

}


#endif
