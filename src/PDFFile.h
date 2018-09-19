#pragma once

#include "PDFDefine.h"
#include "PDFPage.h"
#include "PDFXref.h"

#include <stdio.h>
#include <vector>

namespace PDF {

class PDFFile
{
public:
	PDFFile();
	virtual ~PDFFile(void);

	bool save(const wchar_t* pFileName);
	PDFPage* addPage(const int& nWidth, const int& nHeight);
	
	PDFXref* getXref() const
	{
		return mypXref;
	}
private:
	void init_();

private:
	std::wstring	myFileName;
	FILE*			mypFile;
	PDFXref*		mypXref;
	std::vector<PDFPage*> myPageList;


};
	
}