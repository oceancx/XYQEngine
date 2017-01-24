#include "WDF.h"
// #include "WAS.h"

#include <iostream>

// 	#include <fstream>
// using namespace std;
namespace NetEase {
	WDF::WDF()
	{
		Init();
	}
	void WDF::Init()
	{
		mFile.open(mFilename, ios::in | ios::binary);
		std::cout << "InitWDF:" << mFilename << std::endl;

		if (!mFile) {
			cout << "�ļ���ʧ��:" << endl;//path<<endl;
			return;
		}
		mFile.read((char*)&mHeader, sizeof(Header));
		int number = mHeader.number;
		int offset = mHeader.offset;

		cout << "number:" << number << " offset:" << offset << endl;

		mIndencies = new Index[number]();
		memset(mIndencies, 0, sizeof(Index)*number);
		mFile.seekg(offset);
		mFile.read((char*)mIndencies, sizeof(Index)*number);
		// mFile.close();

		for (int i = 0; i<number; i++)
		{
			mIdToPos[mIndencies[i].hash] = i;
		}

		cout << "WDF�ļ����سɹ���" << endl;
	}

	WDF::~WDF()
	{
		mFile.close();
	}

	/**
	����Sprite2
	*/
	WAS WDF::GetWAS(int id)
	{
		Index index = mIndencies[mIdToPos[id]];
		return WAS(mFilename, index.offset, index.size);
	}


	Sprite2 WDF::LoadSprite(int id)
	{
		WAS::Header header;
		Sprite2 sprite;

		Index index = mIndencies[mIdToPos[id]];
		int wasOffset = index.offset;
		int wasSize = index.size;
		// mFile.seekg(wasOffset,ios::beg);
		// char* outfilec=new char[wasSize];
		// mFile.read(outfilec,wasSize);
		// fstream of("a.was",ios::binary|ios::out);
		// of.write(outfilec,wasSize);
		// of.close();

		mFile.seekg(wasOffset, ios::beg);
		mFile.read((char*)&header, sizeof(header));
		sprite.mGroupSize = header.group;
		sprite.mFrameSize = header.frame;
		sprite.mWidth = header.width;
		sprite.mHeight = header.height;
		sprite.mKeyX = header.key_x;
		sprite.mKeyY = header.key_y;
		sprite.mFrames = new Sprite2::Sequence*[header.group];
		for (int i = 0; i < header.group; i++)
		{
			sprite.mFrames[i] = new Sprite2::Sequence[header.frame];
		}

		if (header.flag != 0x5053)
		{
			cerr << "Sprite File Flag Error!" << endl;
			exit(EXIT_FAILURE);
		}

		// �жϾ����ļ�ͷ�����Ƿ�Ϊ12
		if (header.len != 12)
		{
			// ��ȡ�����ļ�ͷ����
			int AddonHeadLen = header.len - 12;
			uint8* m_AddonHead = new uint8[AddonHeadLen]; // ���丽���ļ�ͷ�Ŀռ�
			mFile.read((char*)m_AddonHead, AddonHeadLen); // ��ȡ�����ļ�ͷ
		}


		// ��ȡ��ɫ������
		mFile.read((char*)&palette16[0], 256 * 2); // Palette[0]��ʹ��

		for (int k = 0; k < 256; k++)
		{
			m_Palette32[k] = WAS::RGB565to888(palette16[k], 0xff); // 16to32��ɫ��ת��
		}

		int frameTotalSize = header.group * header.frame;
		uint32* frameIndexes = new uint32[frameTotalSize];
		mFile.read((char*)frameIndexes, frameTotalSize * 4);


		uint32 pixels = header.width*header.height;

		int frameHeadOffset = 2 + 2 + header.len;

		uint32* frameLine = new uint32[header.height]; // �����������б�Ŀռ�
		uint8* lineData = new uint8[header.width * 4]; // ���������ݵĿռ�

		int x = 0; // �������
		int z = 0; // ����֡��


		for (int i = 0; i<frameTotalSize; i++)
		{
			int gpos = i / (header.frame);
			int cpos = i % (header.frame);

			Sprite2::Sequence& frame = sprite.mFrames[gpos][cpos];

			WAS::FrameHeader tempFreamHeader;
			mFile.seekg(wasOffset + frameHeadOffset + frameIndexes[i], ios::beg);
			mFile.read((char*)&tempFreamHeader, sizeof(WAS::FrameHeader));

			frame.key_x = tempFreamHeader.key_x;
			frame.key_y = tempFreamHeader.key_y;
			frame.width = tempFreamHeader.width;
			frame.height = tempFreamHeader.height;
			frame.src = new uint32[pixels];
			memset(frame.src, 0, pixels * 4);

			// ��ȡ֡���ݿ������
			mFile.read((char*)frameLine, tempFreamHeader.height * 4);

			uint32* pBmpStart = frame.src;//=frame.src+pixels*3;
			for (int j = 0; j< tempFreamHeader.height; j++)
			{
				pBmpStart = frame.src + sprite.mWidth*(j);
				int lineDataLen = 0;
				if (j < tempFreamHeader.height - 1)
				{
					lineDataLen = frameLine[j + 1] - frameLine[j]; // �õ������ݵĴ�С
				}
				else
				{
					if (i<frameTotalSize - 1) {
						lineDataLen = frameIndexes[i + 1] - (frameIndexes[i] + frameLine[j]);
					}
					else {
						lineDataLen = wasSize - (frameIndexes[i] + frameLine[j]);
					}
				}
				// printf("lineLen:%d\n",lineDataLen);
				memset(lineData, 0, frame.width);
				mFile.seekg(wasOffset + frameIndexes[i] + frameHeadOffset + frameLine[j], ios::beg);
				mFile.read((char*)lineData, lineDataLen);
				// printf("before handler:  %x\n",  sprite.mFrames[gpos][cpos].src );
				int pixelOffset = (sprite.mKeyX - frame.key_x);
				int pixelLen = sprite.mWidth;
				// printf("pixelOffset: %d  pixelLen: %d\n",pixelOffset,pixelLen );
				pBmpStart += pixelOffset;
				pBmpStart += (sprite.mKeyY - frame.key_y)*sprite.mWidth;

				DataHandler((char*)lineData, pBmpStart, pixelOffset, pixelLen);

			}
		//	 sprite.SaveImage(i);
		}
		return sprite;
	}



	void WDF::DataHandler(char *pData, uint32* pBmpStart, int pixelOffset, int pixelLen)
	{
		uint32 temp_pixel = 0;

		uint32 Pixels = pixelOffset;
		uint32 PixelLen = pixelLen;
		uint16 AlphaPixel = 0;

		while (*pData != 0) // {00000000} ��ʾ�����н���������ʣ��������͸��ɫ����
		{
			uint8 style = 0;
			uint8 Level = 0; // Alpha����
			uint8 Repeat = 0; // �ظ�����
			style = (*pData & 0xc0) >> 6; // ȡ�ֽڵ�ǰ��������
			switch (style)
			{
			case 0: // {00******}
				if (*pData & 0x20) // {001*****} ��ʾ����Alphaͨ���ĵ�������
				{
					// {001 +5bit Alpha}+{1Byte Index}, ��ʾ����Alphaͨ���ĵ������ء�
					// {001 +0~31��Alphaͨ��}+{1~255����ɫ������}
					Level = (*pData) & 0x1f; // 0x1f=(11111) ���Alphaͨ����ֵ
					pData++; // ��һ���ֽ�
					if (Pixels < PixelLen)
					{
						AlphaPixel = WAS::Alpha565(palette16[(uint8)(*pData)], 0, Level); // ���
						*pBmpStart++ = WAS::RGB565to888(AlphaPixel, Level * 8);
						Pixels++;
						pData++;
					}
				}
				else // {000*****} ��ʾ�ظ�n�δ���Alphaͨ��������
				{
					// {000 +5bit Times}+{1Byte Alpha}+{1Byte Index}, ��ʾ�ظ�n�δ���Alphaͨ�������ء�
					// {000 +�ظ�1~31��}+{0~255��Alphaͨ��}+{1~255����ɫ������}
					// ע: �����{00000000} �����������н���ʹ�ã�����ֻ�����ظ�1~31�Ρ�
					Repeat = (*pData) & 0x1f; // ����ظ��Ĵ���
					pData++;
					Level = *pData; // ���Alphaͨ��ֵ
					pData++;
					for (int i = 1; i <= Repeat; i++)
					{
						if (Pixels < PixelLen)
						{
							AlphaPixel = WAS::Alpha565(palette16[(uint8)*pData], 0, Level); // ���
							*pBmpStart++ = WAS::RGB565to888(AlphaPixel, Level * 8);
							Pixels++;
						}
					}
					pData++;
				}
				break;
			case 1: // {01******} ��ʾ����Alphaͨ�����ظ���n��������ɵ����ݶ�
					// {01  +6bit Times}+{nByte Datas},��ʾ����Alphaͨ�����ظ���n��������ɵ����ݶΡ�
					// {01  +1~63������}+{n���ֽڵ�����},{01000000}������
				Repeat = (*pData) & 0x3f; // ����������еĳ���
				pData++;
				for (int i = 1; i <= Repeat; i++)
				{
					if (Pixels < PixelLen)
					{
						*pBmpStart++ = m_Palette32[(uint8)*pData];
						Pixels++;
						pData++;
					}
				}
				break;
			case 2: // {10******} ��ʾ�ظ�n������
					// {10  +6bit Times}+{1Byte Index}, ��ʾ�ظ�n�����ء�
					// {10  +�ظ�1~63��}+{0~255����ɫ������},{10000000}������
				Repeat = (*pData) & 0x3f; // ����ظ��Ĵ���
				pData++;
				for (int i = 1; i <= Repeat; i++)
				{
					if (Pixels <PixelLen)
					{
						*pBmpStart++ = m_Palette32[(uint8)*pData];
						Pixels++;
					}
				}
				pData++;
				break;
			case 3: // {11******} ��ʾ����n�����أ�������������͸��ɫ����
					// {11  +6bit Times}, ��ʾ����n�����أ�������������͸��ɫ���档
					// {11  +����1~63������},{11000000}������
				Repeat = (*pData) & 0x3f; // ����ظ�����
				for (int i = 1; i <= Repeat; i++)
				{
					if (Pixels < PixelLen)
					{
						pBmpStart++;
						Pixels++;
					}
				}
				pData++;
				break;
			default: // һ�㲻�����������
				cerr << "Error!" << endl;
				exit(EXIT_FAILURE);
				break;
			}
		}
		if (*pData == 0)
		{
			uint8 Repeat = 0;
			Repeat = PixelLen - Pixels;
			for (int i = 0; i < Repeat; i++)
			{
				if (Pixels < PixelLen)
				{
					pBmpStart++;
					Pixels++;
				}
			}
		}
	}
}


// int main(int argc,char* argv[])
// {
// 	// shared_ptr<WDF> p = make_shared<WDF>("./data/shape.wdf");
// 	// cout<<p.use_count();
// 	WDF wdf("./data/shape.wdf");
// 	// wdf.GetWAS(0x00642F2B);
// 	wdf.LoadSprite(0x49386FCE);
// }