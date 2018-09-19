#include "stdafx.h"
#include "PDFObjMaker.h"

namespace PDF{

PDFObjMaker::PDFObjMaker(void)
{
	myObjList.clear();
}

PDFObjMaker::~PDFObjMaker(void)
{
	for(unsigned int i=0 ; i < myObjList.size() ; i++ )
	{
		if(NULL != myObjList[i])
		{
			delete myObjList[i];
		}
	}
}

}