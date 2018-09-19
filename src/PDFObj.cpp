#include "stdafx.h"
#include "PDFObj.h"

namespace PDF{

PDFObj::PDFObj(const unsigned int& nObjNum, const int& nByteOffset, const int& nGenNum, const EnumPDFInUseEntry& eUseType, const EnumPDFObjType& eObjType)
:mynObjNum(nObjNum),mynByteOffset(nByteOffset),mynGenNum(nGenNum),myeUseType(eUseType),myeObjType(eObjType)
{
	init_();
}

PDFObj::~PDFObj(void)
{
}

void PDFObj::init_()
{

}

}