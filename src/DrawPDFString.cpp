#include "stdafx.h"
#include "DrawPDFString.h"

namespace PDF{

#define INDENT_VALUE 3.f
#define MAX_STEAM_SIZE 2048

DrawPDFString::DrawPDFString(const wchar_t* pString, const Rect& rect):
myString(pString), myRect(rect), myFontType(EnumPDFFontType_None)
,myeVAlign(EnumPDFTextAlign_Center), myeHAlign(EnumPDFTextAlign_Near)
,myFontSize(10.f)
{
	addEscapeString(myString);
}

DrawPDFString::~DrawPDFString(void)
{
}

bool DrawPDFString::Draw(PDF::PDFPage *page)
{
	wchar_t szStream[MAX_STEAM_SIZE];
	page->setFont(EnumPDFFontType(myFontType));
	swprintf_s(szStream,L"/F%d %f Tf\n", myFontType, myFontSize);
	Point startPt(0,0);
	wchar_t szData[MAX_STEAM_SIZE] ={0,};
	wchar_t szLine[MAX_STEAM_SIZE] ={0,};
	wcscpy_s(szData,_countof(szData), myString.c_str());
	float fWidth(0);
	int nLine(0);
	int nMaxLine =(int)(myRect.height/myFontSize);

	switch(myFontType) {
		case EnumPDFFontType_None :
		case EnumPDFFontType_RUS :
			{
				getWCharWidth = getWCharWidthNone_;
			}
			break;
		case EnumPDFFontType_Bold:
		case EnumPDFFontType_RUSBold:
			{
				getWCharWidth = getWCharWidthBold_;
			}
			break;
		case EnumPDFFontType_Oblique:
		case EnumPDFFontType_RUSOblique:
			{
				getWCharWidth = getWCharWidthOblique_;
			}
		case EnumPDFFontType_BoldOblique:
		case EnumPDFFontType_RUSBoldOblique:
			{
				getWCharWidth = getWCharWidthBoldOblique_;
			}
			break;
	}
	int iofl=0;
	float ftempwidth (0.f);

	for(int i=0; i <(int)wcslen(szData) && nLine < nMaxLine; i++)
	{
		ftempwidth = fWidth + ((3.f*278.f + (float)getWCharWidth(szData[i]))* myFontSize / 1000.f);
		if(  ftempwidth> myRect.width - INDENT_VALUE) //한줄을 다 썻을 때
		{
			if(nLine+1 == nMaxLine) //  마지막 줄 
			{
				szLine[iofl] = L'.';szLine[iofl+1] = L'.';szLine[iofl+2] = L'.';
				myLinebyString.push_back(std::pair<std::wstring,float>(szLine,fWidth));
				break;
			}
			else  // 쓰고 다음줄
			{
				myLinebyString.push_back(std::pair<std::wstring,float>(szLine,fWidth));
				if(L'\n' != szData[i] ) 
				{
					i--;
				}
				ZeroMemory(szLine,MAX_STEAM_SIZE);
				iofl=0;
				fWidth=0;
				nLine ++;
			}
		}
		else // 아직 공간이 있을 때 
		{
			if(L'\n' == szData[i] ) // 다음줄
			{
				if(NULL != szData[i+1] && nLine+1 == nMaxLine) //  마지막 줄 
				{
					szLine[iofl-1] = L'.';szLine[iofl] = L'.';szLine[iofl+1] = L'.';
				}
				myLinebyString.push_back(std::pair<std::wstring,float>(szLine,fWidth));
				ZeroMemory(szLine, MAX_STEAM_SIZE);
				iofl=0;
				fWidth=0;
				nLine ++;
			}
			else if(L' ' == szData[i] ) 
			{
				ftempwidth =  fWidth + ((3.f*278.f + (float)getWCharWidth(L' '))* myFontSize / 1000.f)+ getWordWidth(&szData[i+1])/ 1000.f;
				if( ftempwidth < myRect.width - INDENT_VALUE)
				{
					szLine[iofl++] = szData[i];
					fWidth += (float)getWCharWidth(szData[i]) * (float)myFontSize / 1000.f;
				}
				else // 다음 단어가 남은 공간에 다 들어가지 않으면 다음 줄
				{
					if(NULL != szData[i+1] && nLine+1 == nMaxLine) //  마지막 줄 
					{
						szLine[iofl-1] = L'.';szLine[iofl] = L'.';szLine[iofl+1] = L'.';
					}
					myLinebyString.push_back(std::pair<std::wstring,float>(szLine,fWidth));
					ZeroMemory(szLine,2048);
					iofl=0;
					fWidth=0;
					nLine ++;
				}
			}
			else		
			{
				szLine[iofl++] = szData[i];
				fWidth += (float)getWCharWidth(szData[i]) * myFontSize / 1000.f;
			}
		}
		if(i+1 == (int)wcslen(szData))
		{
			myLinebyString.push_back(std::pair<std::wstring,float>(szLine,fWidth));
			break;
		}
	}

	unsigned int realLine = myLinebyString.size();
	switch(myeVAlign) {
	case EnumPDFTextAlign_Near:
		{
			startPt.y = myRect.y;
		}
		break;
	case EnumPDFTextAlign_Center:
		{
			float fRemain = (myRect.height - myFontSize * realLine) / 2; 
			startPt.y = myRect.y + fRemain;
		}
		break;
	case EnumPDFTextAlign_Far:
		{
			float fRemain = (myRect.height - myFontSize * realLine); 
			startPt.y = myRect.y + fRemain;
		}
		break;
	}

	for(unsigned int i=0 ; i < realLine ; i++)
	{
		switch(myeHAlign) {
			case EnumPDFTextAlign_Near:
				{
					startPt.x = myRect.x+INDENT_VALUE;
				}
				break;
			case EnumPDFTextAlign_Center:
				{
					float fRemain = (myRect.width - myLinebyString[i].second) / 2; 
					startPt.x = myRect.x + fRemain;
				}
				break;
			case EnumPDFTextAlign_Far:
				{
					float fRemain = (myRect.width - myLinebyString[i].second); 
					startPt.x = myRect.x + fRemain - INDENT_VALUE;
				}
				break;
		}
		swprintf_s(szStream, L"%sBT\n%.1f %.1f Td\n", szStream, startPt.x, (page->getPageHeight() - (startPt.y) - myFontSize + 2));  //+2는 보정치 실제 좌표보다 올려줘야 그럴듯하게 보인다.
		swprintf_s(szStream, L"%s(%s ) Tj\nET\n", szStream, myLinebyString[i].first.c_str());

		startPt.y += myFontSize;
		nLine++;
	}
	page->writeTextStream(szStream);

	return true;
}




float DrawPDFString::getStringWidth(wchar_t* pString, const float& fWantWidht, int& nRetTrimming)
{
	nRetTrimming = 0;
	wchar_t* pWchar = pString;
	float fWidth(0.f);
	int (*getWCharWidth)(unsigned short) = NULL;

	switch(myFontType) {
		case EnumPDFFontType_None:
			{
				getWCharWidth = getWCharWidthNone_;
			}
			break;
		case EnumPDFFontType_Bold:
			{
				getWCharWidth = getWCharWidthBold_;
			}
			break;
		case EnumPDFFontType_Oblique:
			{
				getWCharWidth = getWCharWidthOblique_;
			}
		case EnumPDFFontType_BoldOblique:
			{
				getWCharWidth = getWCharWidthBoldOblique_;
			}
			break;
	}

	for(int i=0; i <(int)wcslen(pString) ; i++)
	{
		fWidth += (float)getWCharWidth(*pWchar) * myFontSize / 1000.f;
		pWchar++;
		if(fWidth + 3.f*278.f/1000.f/*getWCharWidth(L'.')*/ > fWantWidht)
		{
			nRetTrimming = i-1;
			break;
		}
	}
	return (nRetTrimming > 0) ? fWantWidht : fWidth;
}

void DrawPDFString::addEscapeString(std::wstring& szString)
{
	std::wstring::iterator iter= szString.begin();
	while(iter != szString.end())
	{
		if((*iter) == L'\\')
		{
			iter = szString.insert(iter, L'\\') + 1;
		}
		else if((*iter) == L'(')
		{
			iter = szString.insert(iter, L'\\') + 1;
		}
		else if((*iter) == L')')
		{
			iter = szString.insert(iter, L'\\') + 1;
		}
		iter++;
	}

}


float DrawPDFString::getWordWidth(wchar_t* pString)
{
	wchar_t* pWchar = pString;
	float fWidth(0.f);

	for(int i=0; i <(int)wcslen(pString) ; i++)
	{
		if( L'\n' == pWchar[i] || L' ' == pWchar[i] )
		{
			break;		
		}
		else
		{
			fWidth += (float)getWCharWidth(*pWchar) * myFontSize / 1000.f;
		}
		pWchar++;
	}
	return fWidth;
}



}