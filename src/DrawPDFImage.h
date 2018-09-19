#pragma once

#ifndef PDF_DRAWPDFIMAGE_H_INCLUDED_
#define PDF_DRAWPDFIMAGE_H_INCLUDED_

#include "PDFPage.h"

namespace PDF{

class DrawPDFImage
{
public:

	DrawPDFImage(const wchar_t* pImagePath);
	DrawPDFImage(unsigned char* pBuffer, const unsigned int & nSize, const int& nWidth, const int& nHeight,const bool& bBGR=false);
	virtual ~DrawPDFImage(void);
		
	bool Draw(PDFPage* page, const Rect& rect);

	//mm -> pixel 0.3779 단위를 변경한다.
	//float fpixel2mm = 0.3779f;
	void setUnitfactor(const float& fFactor)
	{
		myfUnitFactor = fFactor;
	}

	void setRotate(const enumPDFRotate& eRotate)
	{
		myeRotate = eRotate;
	}

private:
	bool getImageSize(FILE* pFile);

private: 
	unsigned char*		 mypBuffer;
	unsigned int		 mynBufferSize;
	unsigned int		 mynImgWidth;
	unsigned int		 mynImgHeight;
	unsigned int		 mynImgColorSpace;
	unsigned int		 mynImgBPC;
	EnumPDFImgDecodeType myeDecType;
	float				 myfUnitFactor;
	enumPDFRotate		 myeRotate;

};

}

#endif