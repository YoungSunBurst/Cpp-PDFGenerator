#pragma once

#ifndef PDF_DRAWPDFRECT_H_INCLUDED_
#define PDF_DRAWPDFRECT_H_INCLUDED_

#include "PDFPage.h"

namespace PDF{

typedef enum EnumPDFDrawType
{
	EnumPDFDrawType_None = 0x00,
	EnumPDFDrawType_Stroke = 0x01, // 01
	EnumPDFDrawType_Fill   = 0x02,	// 10 
	EnumPDFDrawType_StrokeFille = 0x03, //11
	/*EnumPDFDrawType_Path = 0x04,*/
};

const wchar_t PDFDrawTypeString[4] = {L'n',L'S',L'F',L'B'};

class DrawPDFRect
{
public:
	DrawPDFRect(const Rect& rect);
	virtual ~DrawPDFRect(void);
	
	bool Draw(PDFPage* page);

	void setStrokeWidth(const float& fWidth)
	{
		myStrokeWidth = fWidth;
	}

	void setUnitfactor(const float& fFactor)
	{
		myfUnitFactor = fFactor;
	}

	void setStrokeColor(const COLORREF& color)
	{
		myStrokeColor = color;
	}

	void setFillColor(const COLORREF& color)
	{
		myFillColor = color;
	}

	void setDrawType(const EnumPDFDrawType& eType)
	{
		myeDrawType = eType;
	}

private: 
	float				myStrokeWidth;
	Rect				myRect;
	float				myfUnitFactor;
	EnumPDFDrawType		myeDrawType;
	COLORREF			myStrokeColor;
	COLORREF			myFillColor;

};


}
#endif 