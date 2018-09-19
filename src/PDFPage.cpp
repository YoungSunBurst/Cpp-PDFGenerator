#include "stdafx.h"
#include "PDFPage.h"

namespace PDF{

PDFPage::PDFPage(PDFXref* pXref, const int& nWidth, const int& nHeight):
mypPXref(pXref), mynPageWidth(nWidth), mynPageHeight(nHeight), mypFontListObj(NULL), mypImageListObj(NULL)
{
	for(int i =0 ; i < EnumPDFFontType_Count ; i++)
	{
		mypFontObj[i] =NULL;	
	}
	init_();
}

PDFPage::~PDFPage(void)
{
	if( NULL != mypResourceObj)
	{
		delete mypResourceObj;
	}
	//if( NULL != mypPageFontObj)
	//{
	//	delete mypPageFontObj;
	//}
	if( NULL != mypFontListObj)
	{
		delete mypFontListObj;
	}
	if( NULL != mypImageListObj)
	{
		delete mypImageListObj;
	}
}
void PDFPage::init_()
{
	mypPageObj = new PDFDictObj(mypPXref->getObjCount());
	mypPXref->addPage(mypPageObj);
	mypPageObj->addValue(L"Type", myObjMaker.makeNameObj(L"Page"), EnumPDFObjType_Name);
	PDFArrayObj* pRectArr = myObjMaker.makeArrayObj();
	pRectArr->addValue(myObjMaker.makeNumObj(0));
	pRectArr->addValue(myObjMaker.makeNumObj(0));
	pRectArr->addValue(myObjMaker.makeNumObj(mynPageWidth));
	pRectArr->addValue(myObjMaker.makeNumObj(mynPageHeight));
	mypPageObj->addValue(L"MediaBox", pRectArr, EnumPDFObjType_Array);
	
	mypContentsObj = new PDFStreamObj(mypPXref->getObjCount());
	mypPXref->addObj(mypContentsObj);

	mypPageObj->addValue(L"Contents", myObjMaker.makeIndirectgObj(mypContentsObj), EnumPDFObjType_Indirect);

	mypResourceObj = new PDFDictObj(mypPXref->getObjCount());
	mypPageObj->addValue(L"Resources", mypResourceObj, EnumPDFObjType_Dictionary);
	PDFArrayObj* pProcsetArr = myObjMaker.makeArrayObj();
	pProcsetArr->addValue(myObjMaker.makeNameObj(L"PDF"));
	pProcsetArr->addValue(myObjMaker.makeNameObj(L"Text"));
	pProcsetArr->addValue(myObjMaker.makeNameObj(L"ImageB"));
	pProcsetArr->addValue(myObjMaker.makeNameObj(L"ImageC"));
	pProcsetArr->addValue(myObjMaker.makeNameObj(L"ImageI"));
	mypResourceObj->addValue(L"ProcSet", pProcsetArr, EnumPDFObjType_Array);
	
	mypPageObj->addValue(L"Parent", myObjMaker.makeIndirectgObj(mypPXref->getRootPageObj()), EnumPDFObjType_Indirect);

	mypLengthObj = new PDFNumObj(mypPXref->getObjCount());
	mypPXref->addObj(mypLengthObj);
	mypContentsObj->AddDictValue(L"Length", myObjMaker.makeIndirectgObj(mypLengthObj), EnumPDFObjType_Indirect);

}

void PDFPage::writeTextStream(const wchar_t *pStream)
{
	if(NULL != mypContentsObj && NULL != pStream){
		mypContentsObj->addStream(pStream);
		int length = wcslen(pStream);
		mypLengthObj->addValue(length);
	}
	
}

void PDFPage::setFont(const EnumPDFFontType& eType)
{
	if(NULL == mypFontObj[eType])
	{
		mypFontObj[eType] = new PDFDictObj(mypPXref->getObjCount());
		mypPXref->addObj(mypFontObj[eType]);
		mypFontObj[eType]->addValue(L"Type", myObjMaker.makeNameObj(L"Font"), EnumPDFObjType_Name);
		mypFontObj[eType]->addValue(L"BaseFont", myObjMaker.makeNameObj(PDFFontTypeString[eType]), EnumPDFObjType_Name);
		mypFontObj[eType]->addValue(L"Subtype", myObjMaker.makeNameObj(L"Type1"), EnumPDFObjType_Name);
		if(eType < EnumPDFFontType_RUS)
		{
			mypFontObj[eType]->addValue(L"Encoding", myObjMaker.makeNameObj(L"WinAnsiEncoding"), EnumPDFObjType_Name);
		}
		else if(eType >= EnumPDFFontType_RUS && eType < EnumPDFFontType_Count)
		{
			mypFontObj[eType]->addValue(L"Encoding", myObjMaker.makeStrObj(L"<</Type /Encoding /BaseEncoding /WinAnsiEncoding /Differences [192 /afii10017 193 /afii10018 194 /afii10019 195 /afii10020 196 /afii10021 197 /afii10022 198 /afii10024 199 /afii10025 200 /afii10026 201 /afii10027 202 /afii10028 203 /afii10029 204 /afii10030 205 /afii10031 206 /afii10032 207 /afii10033 208 /afii10034 209 /afii10035 210 /afii10036 211 /afii10037 212 /afii10038 213 /afii10039 214 /afii10040 215 /afii10041 216 /afii10042 217 /afii10043 218 /afii10044 219 /afii10045 220 /afii10046 221 /afii10047 222 /afii10048 223 /afii10049 224 /afii10065 225 /afii10066 226 /afii10067 227 /afii10068 228 /afii10069 229 /afii10070 230 /afii10072 231 /afii10073 232 /afii10074 233 /afii10075 234 /afii10076 235 /afii10077 236 /afii10078 237 /afii10079 238 /afii10080 239 /afii10081 240 /afii10082 241 /afii10083 242 /afii10084 243 /afii10085 244 /afii10086 245 /afii10087 246 /afii10088 247 /afii10089 248 /afii10090 249 /afii10091 250 /afii10092 251 /afii10093 252 /afii10094 253 /afii10095 254 /afii10096 255 /afii10097 ]>>", false), EnumPDFObjType_String);
			mypFontObj[eType]->addValue(L"FirstChar", myObjMaker.makeNumObj(32), EnumPDFObjType_Numeric);
			mypFontObj[eType]->addValue(L"LastChar", myObjMaker.makeNumObj(255), EnumPDFObjType_Numeric);
			if(eType == EnumPDFFontType_RUS)
			{
				mypFontObj[eType]->addValue(L"Widths", myObjMaker.makeStrObj(L"[278 278 355 556 556 889 667 191 333 333 389 584 278 333 278 278 556 556 556 556 556 556 556 556 556 556 278 278 584 584 584 556 1015 667 667 722 722 667 611 778 722 278 500 667 556 833 722 778 667 778 722 667 611 722 667 944 667 667 611 278 278 278 469 556 333 556 556 500 556 556 278 556 556 222 222 500 222 833 556 556 556 556 333 500 278 556 500 722 500 500 500 334 260 334 584 750 750 750 222 556 333 1000 556 556 333 1000 667 333 1000 750 750 750 750 222 222 333 333 350 556 1000 333 1000 500 333 944 750 750 667 278 333 556 556 556 556 260 556 333 737 370 556 584 333 737 552 400 549 333 333 333 576 537 278 333 333 365 556 834 834 834 611 667 656 667 542 677 667 923 604 719 719 583 656 833 722 778 719 667 722 611 635 760 667 740 667 917 938 792 885 656 719 101 722 556 573 531 365 583 556 669 458 559 559 438 583 688 552 556 542 556 500 458 500 823 500 573 521 802 823 625 719 521 510 750 542]",false), EnumPDFObjType_String);
			}
			else if(eType == EnumPDFFontType_RUSBold)
			{
				mypFontObj[eType]->addValue(L"Widths", myObjMaker.makeStrObj(L"[278 333 474 556 556 889 722 238 333 333 389 584 278 333 278 278 556 556 556 556 556 556 556 556 556 556 333 333 584 584 584 611 975 722 722 722 722 667 611 778 722 278 556 722 611 833 722 778 667 778 722 667 611 722 667 944 667 667 611 333 278 333 584 556 333 556 611 556 611 556 333 611 611 278 278 556 278 889 611 611 611 611 389 556 333 611 556 778 556 556 500 389 280 389 584 750 750 750 278 556 500 1000 556 556 333 1000 667 333 1000 750 750 750 750 278 278 500 500 350 556 1000 333 1000 556 333 944 750 750 667 278 333 556 556 556 556 280 556 333 737 370 556 584 333 737 552 400 549 333 333 333 576 556 278 333 333 365 556 834 834 834 611 722 719 722 567 712 667 904 626 719 719 610 702 833 722 778 719 667 722 611 622 854 667 730 703 1005 1019 870 979 719 711 1031 719 556 618 615 417 635 556 709 497 615 615 500 635 740 604 611 604 611 556 490 556 875 556 615 581 833 844 729 854 615 552 854 583]",false), EnumPDFObjType_String);
			}
			else if(eType == EnumPDFFontType_RUSBoldOblique)
			{
				mypFontObj[eType]->addValue(L"Widths", myObjMaker.makeStrObj(L"[278 333 474 556 556 889 722 238 333 333 389 584 278 333 278 278 556 556 556 556 556 556 556 556 556 556 333 333 584 584 584 611 975 722 722 722 722 667 611 778 722 278 556 722 611 833 722 778 667 778 722 667 611 722 667 944 667 667 611 333 278 333 584 556 333 556 611 556 611 556 333 611 611 278 278 556 278 889 611 611 611 611 389 556 333 611 556 778 556 556 500 389 280 389 584 750 750 750 278 556 500 1000 556 556 333 1000 667 333 1000 750 750 750 750 278 278 500 500 350 556 1000 333 1000 556 333 944 750 750 667 278 333 556 556 556 556 280 556 333 737 370 556 584 333 737 552 400 549 333 333 333 576 556 278 333 333 365 556 834 834 834 611 722 708 722 614 722 667 927 643 719 719 615 687 833 722 778 719 667 722 611 677 781 667 729 708 979 989 854 1000 708 719 1042 729 556 619 604 534 618 556 736 510 611 611 507 622 740 604 611 611 611 556 889 556 885 556 646 583 889 935 707 854 594 552 865 589]",false), EnumPDFObjType_String);
			}
			else if(eType == EnumPDFFontType_RUSOblique)
			{
				mypFontObj[eType]->addValue(L"Widths", myObjMaker.makeStrObj(L"[278 278 355 556 556 889 667 191 333 333 389 584 278 333 278 278 556 556 556 556 556 556 556 556 556 556 278 278 584 584 584 556 1015 667 667 722 722 667 611 778 722 278 500 667 556 833 722 778 667 778 722 667 611 722 667 944 667 667 611 278 278 278 469 556 333 556 556 500 556 556 278 556 556 222 222 500 222 833 556 556 556 556 333 500 278 556 500 722 500 500 500 334 260 334 584 750 750 750 222 556 333 1000 556 556 333 1000 667 333 1000 750 750 750 750 222 222 333 333 350 556 1000 333 1000 500 333 944 750 750 667 278 333 556 556 556 556 260 556 333 737 370 556 584 333 737 552 400 549 333 333 333 576 537 278 333 333 365 556 834 834 834 611 667 651 667 544 704 667 917 614 715 715 589 686 833 722 778 725 667 722 611 639 795 667 727 673 920 923 805 886 651 694 1022 682 556 563 522 493 553 556 688 465 556 556 472 564 686 550 556 550 556 500 833 500 835 500 572 518 830 851 621 736 526 492 752 534]",false), EnumPDFObjType_String);
			}
		}
		
		wchar_t szTemp[8];
		if( NULL != mypFontListObj)
		{
			swprintf_s(szTemp, L"F%d", eType);
			mypFontListObj->addValue(szTemp, myObjMaker.makeIndirectgObj(mypFontObj[eType]), EnumPDFObjType_Indirect);
		}
		else
		{
			/*mypPageFontObj = new PDFDictObj(0);*/
			mypFontListObj = new PDFDictObj(0);
			mypResourceObj->addValue(L"Font", mypFontListObj, EnumPDFObjType_Dictionary);
			swprintf_s(szTemp, L"F%d", eType);
			mypFontListObj->addValue(szTemp, myObjMaker.makeIndirectgObj(mypFontObj[eType]), EnumPDFObjType_Indirect);
		}
	}

}

void PDFPage::addImageObj(unsigned char* pBuffer, const unsigned int& nSize, const int& width, const int& height, const Rect& rect, const int& nBPC, const EnumPDFImgDecodeType& eDecType, const enumPDFRotate& eRotate)
{
	mypImageObj.push_back(new PDFStreamObj(mypPXref->getObjCount()));
	mypPXref->addObj(mypImageObj[mypImageObj.size()-1]);
	PDFNumObj* pLengthObj = new PDFNumObj(mypPXref->getObjCount());
	mypPXref->addObj(pLengthObj);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Length", myObjMaker.makeIndirectgObj(pLengthObj), EnumPDFObjType_Indirect);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Type", myObjMaker.makeNameObj(L"XObject"), EnumPDFObjType_Name);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Subtype", myObjMaker.makeNameObj(L"Image"), EnumPDFObjType_Name);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Height", myObjMaker.makeNumObj(height), EnumPDFObjType_Numeric);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Width", myObjMaker.makeNumObj(width), EnumPDFObjType_Numeric);
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"ColorSpace", myObjMaker.makeNameObj(L"DeviceRGB"), EnumPDFObjType_Name); // To do
	mypImageObj[mypImageObj.size()-1]->AddDictValue(L"BitsPerComponent", myObjMaker.makeNumObj(nBPC), EnumPDFObjType_Numeric);
	if(eDecType > EnumPDFImgDecodeType_Raw)
	{ 
		PDFArrayObj* pArrayobj = myObjMaker.makeArrayObj();
		pArrayobj->addValue(myObjMaker.makeNameObj(PDFImgDecodeTypeString[eDecType]));
		mypImageObj[mypImageObj.size()-1]->AddDictValue(L"Filter", pArrayobj, EnumPDFObjType_Array);
	}
	mypImageObj[mypImageObj.size()-1]->setStream(pBuffer, nSize);

	
	if(2 > mypImageObj.size())
	{
		mypImageListObj = new PDFDictObj(0);
		mypResourceObj->addValue(L"XObject", mypImageListObj, EnumPDFObjType_Dictionary);
	}
	wchar_t szTemp[8];
	swprintf_s(szTemp, L"X%d", mypImageObj.size());
	mypImageListObj->addValue(szTemp, myObjMaker.makeIndirectgObj(mypImageObj[mypImageObj.size()-1]), EnumPDFObjType_Indirect);

	wchar_t szStream[256];
	switch(eRotate)
	{
	case enumPDFRotate_0:
		swprintf_s(szStream, L"q\n%.1f 0 0 %.1f %.1f %.1f cm\n/X%d Do\nQ\n", rect.width, rect.height, rect.x, mynPageHeight - rect.y - rect.height, mypImageObj.size());
		break;
	case enumPDFRotate_90:
		swprintf_s(szStream, L"q\n%.1f 0 0 %.1f %.1f %.1f cm\n0 1 -1 0 0 0 cm\n/X%d Do\nQ\n", rect.width, rect.height, rect.x + rect.width ,mynPageHeight - rect.y - rect.height, mypImageObj.size());
		break;
	case enumPDFRotate_180:
		swprintf_s(szStream, L"q\n%.1f 0 0 %.1f %.1f %.1f cm\n1 0 0 -1 0 0 cm\n/X%d Do\nQ\n", rect.width, rect.height, rect.x, mynPageHeight - rect.y, mypImageObj.size());
		break;
	case enumPDFRotate_270:
		swprintf_s(szStream, L"q\n%.1f 0 0 %.1f %.1f %.1f cm\n0 -1 1 0 0 0 cm\n/X%d Do\nQ\n", rect.width, rect.height, rect.x,mynPageHeight - rect.y, mypImageObj.size());
		break;
	default:
		swprintf_s(szStream, L"q\n%.1f 0 0 %.1f %.1f %.1f cm\n/X%d Do\nQ\n", rect.width, rect.height, rect.x, mynPageHeight - rect.y - rect.height, mypImageObj.size());
		break;
	}
	mypContentsObj->addStream(szStream);
	int length = wcslen(szStream);
	mypLengthObj->addValue(length);

	pLengthObj->setValue((int)nSize);
}


}


