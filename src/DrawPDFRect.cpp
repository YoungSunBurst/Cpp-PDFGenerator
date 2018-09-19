#include "stdafx.h"
#include "DrawPDFRect.h"

namespace PDF{

DrawPDFRect::DrawPDFRect(const Rect& rect)
: myRect(rect), myStrokeWidth(1), myfUnitFactor(1), myeDrawType(EnumPDFDrawType_Stroke)
, myStrokeColor(RGB(0,0,0)), myFillColor(RGB(0,0,0))
{
}

DrawPDFRect::~DrawPDFRect(void)
{
}

bool DrawPDFRect::Draw(PDF::PDFPage *page)
{
	wchar_t szStream[2048];
	swprintf_s(szStream, L"%.1f w\n", myStrokeWidth);
	if( EnumPDFDrawType_Stroke == (EnumPDFDrawType_Stroke & myeDrawType))
	{
		swprintf_s(szStream, L"%s%.1f %.1f %.1f RG\n", szStream, float(GetBValue(myStrokeColor))/255.f, float(GetGValue(myStrokeColor))/255.f, float(GetBValue(myStrokeColor))/255.f);
	}
	if( EnumPDFDrawType_Fill == (EnumPDFDrawType_Fill & myeDrawType))
	{
		swprintf_s(szStream, L"%s%.1f %.1f %.1f rg\n", szStream, float(GetBValue(myFillColor))/255.f, float(GetGValue(myFillColor))/255.f, float(GetBValue(myFillColor))/255.f);
	}
	swprintf_s(szStream, L"%s%.1f %.1f %.1f %.1f re\n", szStream, myRect.x*myfUnitFactor, (page->getPageHeight()-myRect.y*myfUnitFactor-myRect.height*myfUnitFactor), myRect.width*myfUnitFactor, myRect.height*myfUnitFactor);
	swprintf_s(szStream, L"%s%c\n", szStream, PDFDrawTypeString[myeDrawType] );
	if( EnumPDFDrawType_Fill == (EnumPDFDrawType_Fill & myeDrawType))
	{
		swprintf_s(szStream, L"%s0 0 0 rg\n", szStream);
	}
	page->writeTextStream(szStream);
	return true;
}

}