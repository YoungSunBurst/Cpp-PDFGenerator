#include "stdafx.h"
#include "PDFFile.h"

namespace PDF {

PDFFile::PDFFile()
//: myFileName(pFileName)
{
	//_wfopen_s(&mypFile, pFileName,L"wb");
	init_();	
}

PDFFile::~PDFFile(void)
{
	delete mypXref;
	for(unsigned int i=0;i < myPageList.size();i++)
	{
		if(NULL != myPageList[i])
		{
			delete myPageList[i];
		}
	}
}

void PDFFile::init_()
{
	mypXref = new PDFXref(0);
	// To do ?? font??
}

bool PDFFile::save(const wchar_t* pFileName)
{
	FILE* pFile;
	if(0 != _wfopen_s(&pFile, pFileName, L"wb"))
	{
		wprintf_s(L"error");
	}
	else
	{
		if(NULL != pFile)
		{
			mypXref->writeAllObj(pFile);
			fclose(pFile);
		}
	}
	return true;
}

PDFPage* PDFFile::addPage(const int& nWidth, const int& nHeight)
{
	PDFPage* pPage = new PDFPage(mypXref,nWidth,nHeight);
	myPageList.push_back(pPage);
	return pPage;
}


















}