#pragma once

#ifndef PDF_DRAWPDFSTRING_H_INCLUDED_
#define PDF_DRAWPDFSTRING_H_INCLUDED_

#include "PDFPage.h"
#include "PDFTextDefine.h"
#include <vector>

namespace PDF{

class DrawPDFString
{
public:
	DrawPDFString(const wchar_t* pString, const Rect& rect);
	virtual ~DrawPDFString(void);
	
	bool Draw(PDFPage* page);

	void setString(const wchar_t* pString)
	{
		myString = pString;
		addEscapeString(myString);
	}
	
	void setRect(const Rect& rect)
	{
		myRect = rect;
	}

	void setBold(const bool& bBold)
	{
		if(false != bBold){
			myFontType |=  EnumPDFFontType_Bold;
		}
		else{
			myFontType &= (~EnumPDFFontType_Bold);
		}
	}

	void setOblique(const bool& bOblique)
	{
		if(false != bOblique){
			myFontType |=  EnumPDFFontType_Oblique;
		}
		else{
			myFontType &= (~EnumPDFFontType_Oblique);
		}
	}

	void setValign(const EnumPDFTextAlign& eValign)
	{
		myeVAlign = eValign;
	}

	void setHalign(const EnumPDFTextAlign& eHalign)
	{
		myeHAlign = eHalign;
	}

	void setFontSize(const float& nSize)
	{
		myFontSize = nSize;
	}

	void setUnitfactor(const float& fFactor)
	{
		myfUnitFactor = fFactor;
		myRect.increment(myfUnitFactor);
	}

	void setRUSEncoding(const bool& bBold)
	{
		if(false != bBold){
			myFontType |=  EnumPDFFontType_RUS;
		}
		else{
			myFontType &= (~EnumPDFFontType_RUS);
		}
	}

private:
	float	getStringWidth(wchar_t* pString, const float& fWantWidht, int& nRetTrimming);
	void	addEscapeString(std::wstring& szString);
	int		(*getWCharWidth)(unsigned short);
	float	getWordWidth(wchar_t* pString);

	//int DrawPDFString::getWCharWidthNone_(unsigned short nUnicode);
	//int DrawPDFString::getWCharWidthBold_(unsigned short nUnicode);
	//int DrawPDFString::getWCharWidthOblique_(unsigned short nUnicode);
	//int DrawPDFString::getWCharWidthBoldOblique_(unsigned short nUnicode);
	//	void writeString_(const wchar_t* szStream, const wchar_t* szLine,const float& fWidth,const unsigned int& nLine);

private: 

	std::wstring			myString;
	std::wstring			myFontName;
	float					myfUnitFactor;
	float					myFontSize;
	EnumPDFTextAlign		myeVAlign;
	EnumPDFTextAlign		myeHAlign;
	Rect					myRect;
	unsigned long 			myFontType;

	std::vector<std::pair<std::wstring,float>>	myLinebyString;

};


}

#endif