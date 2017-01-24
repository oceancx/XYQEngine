#include "Sprite2.h"
#include <memory.h>
#include <fstream>
#include <iostream>
#include "WAS.h"
using namespace std;

Sprite2::Sprite2()
{

}

Sprite2::~Sprite2()
{

}


void Sprite2::SaveImage(int index)
{
	TGA_FILE_HEADER TgaHeader;
	memset(&TgaHeader, 0, 18);
	TgaHeader.IdLength = 0;			// ͼ����Ϣ�ֶ�(Ĭ��:0)
	TgaHeader.ColorMapType = 0;		// ��ɫ�������(Ĭ��0)
	TgaHeader.ImageType = 0x02;			// ͼ��������(֧��2��10)
	TgaHeader.ColorMapFirstIndex = 0;	// ��ɫ�������(Ĭ��:0)
	TgaHeader.ColorMapLength = 0;		// ��ɫ��ĳ���(Ĭ��:0)
	TgaHeader.ColorMapEntrySize = 0;	// ��ɫ������Ϊ��(Ĭ��:0��֧��16/24/32)
	TgaHeader.XOrigin = 0;				// ͼ��X�������ʼλ��(Ĭ��:0)
	TgaHeader.YOrigin = 0;				// ͼ��Y�������ʼλ��(Ĭ��:0)
	TgaHeader.ImageWidth = mWidth;			// ͼ��Ŀ��
	TgaHeader.ImageHeight = mHeight;			// ͼ��ĸ߶�
	TgaHeader.PixelDepth = 32;			// ͼ��ÿ���ش洢ռ��λ��
	TgaHeader.ImageDescruptor = 8;		// ͼ�������ַ��ֽ�(Ĭ��:0)

	char outfilename[50];
	int gpos = index / mFrameSize;
	int cpos = index%mFrameSize;
	
	sprintf_s(outfilename, "mhxy%d_%d.tga", gpos, cpos);
	printf("%s\n", outfilename);
	
	ofstream ofile;
	ofile.open(outfilename, ios::out | ios::trunc | ios::binary);
	//cout << "дTGAͼ���ļ�ͷ" << endl;
	ofile.write((char*)(&TgaHeader), sizeof(TGA_FILE_HEADER)); // дTGA���ļ�ͷ
	//char* data = (char*)mFrames[gpos][cpos].src;													   //cout << "ͼ���ļ�ͷд��ɣ���ʼдͼ�����ݡ�" << endl;
	//for (int i = 0; i < mHeight; i++)
	//{
	//	ofile.write((char*)&data[(mHeight -1- i)*mWidth*4], mWidth * 4);
	//}
	ofile.write((char*)mFrames[gpos][cpos].src, mWidth*mHeight * 4);
	cout << "��� " << outfilename << " ֡ͼƬ���~" << endl;
	ofile.close();
}