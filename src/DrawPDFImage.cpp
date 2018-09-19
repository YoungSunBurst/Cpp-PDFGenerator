#include "stdafx.h"
#include "DrawPDFImage.h"

namespace PDF{

DrawPDFImage::DrawPDFImage(const wchar_t* pImagePath)
: mypBuffer(NULL), mynBufferSize(0), myeDecType(EnumPDFImgDecodeType_FlateDecode), myfUnitFactor(1), myeRotate(enumPDFRotate_0)
{
	FILE* pImageFile;
	if(0 == _wfopen_s(&pImageFile, pImagePath, L"rb"))
	{
		if(NULL != pImageFile)
		{
			fseek (pImageFile, 0, SEEK_END);
			mynBufferSize = (unsigned int)ftell(pImageFile);
			rewind(pImageFile);
			if(mynBufferSize > 0)
			{
				mypBuffer = new unsigned char[mynBufferSize];
				fread(mypBuffer, sizeof(unsigned char), mynBufferSize, pImageFile);	
			}
			rewind(pImageFile);
			getImageSize(pImageFile);
		}
		fclose(pImageFile);
	}
}

DrawPDFImage::DrawPDFImage(unsigned char* pBuffer, const unsigned int& nSize, const int& nWidth, const int& nHeight, const bool& bBGR )
: mypBuffer(NULL), mynBufferSize(nSize), mynImgHeight(nHeight), mynImgWidth(nWidth), myfUnitFactor(1)
, myeDecType(EnumPDFImgDecodeType_Raw), mynImgBPC(8), myeRotate(enumPDFRotate_0)
{
	if((int)nSize > nWidth * nHeight)
	{
		int remain = mynImgWidth*3%4;
		int add = remain>0 ? 4-remain : 0 ;
		mynBufferSize = mynImgHeight*mynImgWidth*3;
		mypBuffer = new unsigned char[mynBufferSize];
		if(false != bBGR)
		{
			for(int i = 0 ; i < nHeight ; i++)
			{
				for(int j=0 ; j<nWidth*3 ; j=j+3)
				{
					mypBuffer[i*nWidth*3+j] = pBuffer[i*(nWidth*3+add)+j+2];
					mypBuffer[i*nWidth*3+j+1] = pBuffer[i*(nWidth*3+add)+j+1];
					mypBuffer[i*nWidth*3+j+2] = pBuffer[i*(nWidth*3+add)+j];
				}
			}
		}
		else
		{
			for(int i=0; i < nHeight ; i++)
			{
				memcpy(&mypBuffer[i*mynImgWidth*3],&pBuffer[i*(mynImgWidth*3+add)],mynImgWidth*3);			
			}
		}
	}
	else
	{
		mypBuffer = new unsigned char[mynBufferSize];
		if(bBGR != false)
		{
			for(int i=0; i < nHeight ; i++)
			{
				for(int j=0; j < nWidth*3 ;j=j+3)
				{
					mypBuffer[i*nWidth*3+j] = pBuffer[i*(nWidth*3)+j+2];
					mypBuffer[i*nWidth*3+j+1] = pBuffer[i*(nWidth*3)+j+1];
					mypBuffer[i*nWidth*3+j+2] = pBuffer[i*(nWidth*3)+j];
				}
			}
		}
		else
		{
			memcpy(mypBuffer, pBuffer, mynBufferSize);
		}
	}
}	


DrawPDFImage::~DrawPDFImage(void)
{
	if(mypBuffer != NULL){
		delete mypBuffer;
	}
}


bool DrawPDFImage::getImageSize(FILE* f)
{
    if (f==0){
		return false;
	}
	fseek(f,0,SEEK_END);
	long len=ftell(f);
	fseek(f,0,SEEK_SET);
	if (len<24) {
		fclose(f);
		return false;
	}
	// The below code's source : cplusplus.com 

	// Strategy:
	// reading GIF dimensions requires the first 10 bytes of the file
	// reading PNG dimensions requires the first 24 bytes of the file
	// reading JPEG dimensions requires scanning through jpeg chunks
	// In all formats, the file is at least 24 bytes big, so we'll read that always
	unsigned char buf[24]; 
	fread(buf,1,24,f);

	// For JPEGs, we need to read the first 12 bytes of each chunk.
	// We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
	if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
	{ 
		long pos=2;
		while (buf[2]==0xFF){
			if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB){
				break;
			}
			pos += 2+(buf[4]<<8)+buf[5];
			if (pos+12>len){
				break;
			}
			fseek(f,pos,SEEK_SET); 
			fread(buf+2,1,12,f);
		}
	}

	fclose(f);

	// JPEG: (first two bytes of buf are first two bytes ofz the jpeg file; rest of buf is the DCT frame
	if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF){
	  mynImgHeight = (buf[7]<<8) + buf[8];
	  mynImgWidth = (buf[9]<<8) + buf[10];
	  mynImgBPC = buf[6];
	  mynImgColorSpace = buf[11];
	  myeDecType = EnumPDFImgDecodeType_DCTDecode;
	  //cout << *x << endl;
	  return true;
  }

  // GIF: first three bytes say "GIF", next three give version number. Then dimensions
  if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F'){ 
	  mynImgHeight = buf[6] + (buf[7]<<8);
	  mynImgWidth = buf[8] + (buf[9]<<8);
	  return true;
  }

  // PNG: the first frame is by definition an IHDR frame, which gives dimensions
  if ( buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
	  && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
  {
	  mynImgHeight = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
	  mynImgWidth = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
	  return true;
  }

  return false;
}

bool DrawPDFImage::Draw(PDFPage* page, const Rect& rect)
{
	if(NULL != mypBuffer)
	{
		Rect nRect ( rect);
		nRect.increment(myfUnitFactor);
		page->addImageObj(mypBuffer,mynBufferSize,mynImgWidth,mynImgHeight,nRect,mynImgBPC,myeDecType,myeRotate);
		return true;
	}
	return false;
}







}