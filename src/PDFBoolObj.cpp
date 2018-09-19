#include "stdafx.h"
#include "PDFBoolObj.h"

namespace PDF{

PDFBoolObj::PDFBoolObj(const unsigned int& nObjNum)
: PDFObj(nObjNum, 0, 0, EnumPDFInUseEntry_n, EnumPDFObjType_Boolean)
{
}

PDFBoolObj::~PDFBoolObj(void)
{
}







}