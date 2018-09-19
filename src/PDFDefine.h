
#ifndef PDF_PDFDEFINE_H_INCLUDED_
#define PDF_PDFDEFINE_H_INCLUDED_
#include <vector>
#include <stdarg.h>
namespace PDF{


static const char* PDFversionString[6] = {
              "%%PDF-1.2\012%%\267\276\255\252\012",
              "%%PDF-1.3\012%%\267\276\255\252\012",
              "%%PDF-1.4\012%%\267\276\255\252\012",
              "%%PDF-1.5\012%%\267\276\255\252\012",
              "%%PDF-1.6\012%%\267\276\255\252\012",
              "%%PDF-1.7\012%%\267\276\255\252\012"
};

typedef enum EnumPDFInUseEntry{
	EnumPDFInUseEntry_f =0,			//Free Entry
	EnumPDFInUseEntry_n	=1			//In Use Entry
};

static const wchar_t PDFInUseEntryString[2] = { L'f', L'n'};

#define	PDF_MAX_GENERATION_NUM        65535

typedef enum EnumPDFObjType{
	EnumPDFObjType_Boolean,
	EnumPDFObjType_Numeric,
	EnumPDFObjType_String,
	EnumPDFObjType_Name,
	EnumPDFObjType_Array,
	EnumPDFObjType_Dictionary,
	EnumPDFObjType_Stream,
	EnumPDFObjType_NULL,
	EnumPDFObjType_Indirect
};

typedef struct _Rect{
	_Rect(const float& nX, const float& nY, const float& nWidth,const float& nHeight)
		: x(nX), y(nY), width(nWidth), height(nHeight)
	{}
	float x;
	float y;
	float width;
	float height;
	_Rect(const _Rect& rect)
		: x(rect.x), y(rect.y), width(rect.width), height(rect.height)
	{}
	void increment(float f)
	{
		x *= f;
		y *= f;
		width *= f;
		height *= f;
	}
} Rect;

typedef struct _Point{
	_Point(const float& nX, const float& nY)
		: x(nX),y(nY)
	{}
	float x;
	float y;
	_Point(const _Point& pt)
		: x(pt.x),y(pt.y)
	{}
} Point;


static int wcPrintf(FILE* pfile, const wchar_t* format, ...)
{
	int nRet(0);

	va_list vl;
	va_start(vl, format);
#pragma warning(disable:4996)
	size_t length = _vsnwprintf(NULL, 0, format, vl);
#pragma warning(default:4996)
	va_end(vl);
	va_start(vl, format);
	unsigned char* cString = new unsigned char[length+1];
	wchar_t* wcString= new wchar_t[length+1];
	vswprintf_s(wcString, length+1, format, vl);
	ZeroMemory(cString, length+1);
	va_end(vl);
	//size_t getVal=0;
	//wchar_t sz[20000];
	//wsprintf(sz,L"PDF Length %d, len %d data: %s",length,wcslen(wcString),wcString);
	//OutputDebugString(sz);
	//WideCharToMultiByte(CP_ACP, 0, wcString, -1, cString, length+1, NULL, NULL);
	for(unsigned int i=0; i <  length ; i++)
	{
		if(L' ' == wcString[i])
		{
			wchar_t sz[256];
			wsprintf(sz, L"zero %d", wcString[i]);
			OutputDebugString(sz);
		}
		if(0xFF >  wcString[i])
		{
			cString[i] = (char)wcString[i];
		}
		else if( 0x0410 <= wcString[i] && 0x044F >= wcString[i] )
		{
			cString[i] = (char)(wcString[i] - 0x0350);
		}
		else
		{
			cString[i]=' ';
		}
	}
	/*std::string strMulti = CW2A(wcString);*/
	/*wcstombs_s(&getVal,cString,wcslen(wcString)+1,wcString,_TRUNCATE);*/
	nRet = fprintf_s(pfile, "%s", cString);
	//nRet = fwrite(cString,sizeof(unsigned char),length,pfile);
	/*nRet = fprintf_s(pfile,"%s",strMulti.c_str());*/
	delete []cString;
	delete []wcString;
	return nRet;
}

typedef enum EnumPDFFontEncode{
	EnumPDFFontEncode_Ansi = 0x0,
	EnumPDFFontEncode_RUS = 0x1,
};

typedef enum EnumPDFFontType{
	EnumPDFFontType_None = 0x0,				//00
	EnumPDFFontType_Bold = 0x1,				//01
	EnumPDFFontType_Oblique = 0x2,			//10
	EnumPDFFontType_BoldOblique = 0x3,		//11
	EnumPDFFontType_RUS = 0x4,				//100 , 101,110,111
	EnumPDFFontType_RUSBold = 0x5,				//01
	EnumPDFFontType_RUSOblique = 0x6,			//10
	EnumPDFFontType_RUSBoldOblique = 0x7,	
	EnumPDFFontType_Count = 0x8
};

static const wchar_t* PDFFontTypeString[EnumPDFFontType_Count] = 
{L"Helvetica", L"Helvetica-Bold", L"Helvetica-Oblique", L"Helvetica-BoldOblique", L"Helvetica", L"Helvetica-Bold", L"Helvetica-Oblique", L"Helvetica-BoldOblique"};

typedef enum EnumPDFImgDecodeType{
	EnumPDFImgDecodeType_Raw = -1,
	EnumPDFImgDecodeType_FlateDecode = 0,
	EnumPDFImgDecodeType_DCTDecode ,
	EnumPDFImgDecodeType_CCITTFaxDecode,
	EnumPDFImgDecodeType_Count
};

static const wchar_t* PDFImgDecodeTypeString[EnumPDFImgDecodeType_Count] = 
{L"FlateDecode", L"DCTDecode", L"CCITTFaxDecode"};

}
#endif

