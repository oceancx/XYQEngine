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
			cout << "文件打开失败:" << endl;//path<<endl;
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

		cout << "WDF文件加载成功！" << endl;
	}

	WDF::~WDF()
	{
		mFile.close();
	}

	/**
	返回Sprite2
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

		// 判断精灵文件头长度是否为12
		if (header.len != 12)
		{
			// 读取附加文件头数据
			int AddonHeadLen = header.len - 12;
			uint8* m_AddonHead = new uint8[AddonHeadLen]; // 分配附加文件头的空间
			mFile.read((char*)m_AddonHead, AddonHeadLen); // 读取附加文件头
		}


		// 读取调色板数据
		mFile.read((char*)&palette16[0], 256 * 2); // Palette[0]不使用

		for (int k = 0; k < 256; k++)
		{
			m_Palette32[k] = WAS::RGB565to888(palette16[k], 0xff); // 16to32调色板转换
		}

		int frameTotalSize = header.group * header.frame;
		uint32* frameIndexes = new uint32[frameTotalSize];
		mFile.read((char*)frameIndexes, frameTotalSize * 4);


		uint32 pixels = header.width*header.height;

		int frameHeadOffset = 2 + 2 + header.len;

		uint32* frameLine = new uint32[header.height]; // 分配行引索列表的空间
		uint8* lineData = new uint8[header.width * 4]; // 分配行数据的空间

		int x = 0; // 动作组号
		int z = 0; // 动作帧数


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

			// 读取帧数据块的引索
			mFile.read((char*)frameLine, tempFreamHeader.height * 4);

			uint32* pBmpStart = frame.src;//=frame.src+pixels*3;
			for (int j = 0; j< tempFreamHeader.height; j++)
			{
				pBmpStart = frame.src + sprite.mWidth*(j);
				int lineDataLen = 0;
				if (j < tempFreamHeader.height - 1)
				{
					lineDataLen = frameLine[j + 1] - frameLine[j]; // 得到行数据的大小
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

		while (*pData != 0) // {00000000} 表示像素行结束，如有剩余像素用透明色代替
		{
			uint8 style = 0;
			uint8 Level = 0; // Alpha层数
			uint8 Repeat = 0; // 重复次数
			style = (*pData & 0xc0) >> 6; // 取字节的前两个比特
			switch (style)
			{
			case 0: // {00******}
				if (*pData & 0x20) // {001*****} 表示带有Alpha通道的单个像素
				{
					// {001 +5bit Alpha}+{1Byte Index}, 表示带有Alpha通道的单个像素。
					// {001 +0~31层Alpha通道}+{1~255个调色板引索}
					Level = (*pData) & 0x1f; // 0x1f=(11111) 获得Alpha通道的值
					pData++; // 下一个字节
					if (Pixels < PixelLen)
					{
						AlphaPixel = WAS::Alpha565(palette16[(uint8)(*pData)], 0, Level); // 混合
						*pBmpStart++ = WAS::RGB565to888(AlphaPixel, Level * 8);
						Pixels++;
						pData++;
					}
				}
				else // {000*****} 表示重复n次带有Alpha通道的像素
				{
					// {000 +5bit Times}+{1Byte Alpha}+{1Byte Index}, 表示重复n次带有Alpha通道的像素。
					// {000 +重复1~31次}+{0~255层Alpha通道}+{1~255个调色板引索}
					// 注: 这里的{00000000} 保留给像素行结束使用，所以只可以重复1~31次。
					Repeat = (*pData) & 0x1f; // 获得重复的次数
					pData++;
					Level = *pData; // 获得Alpha通道值
					pData++;
					for (int i = 1; i <= Repeat; i++)
					{
						if (Pixels < PixelLen)
						{
							AlphaPixel = WAS::Alpha565(palette16[(uint8)*pData], 0, Level); // 混合
							*pBmpStart++ = WAS::RGB565to888(AlphaPixel, Level * 8);
							Pixels++;
						}
					}
					pData++;
				}
				break;
			case 1: // {01******} 表示不带Alpha通道不重复的n个像素组成的数据段
					// {01  +6bit Times}+{nByte Datas},表示不带Alpha通道不重复的n个像素组成的数据段。
					// {01  +1~63个长度}+{n个字节的数据},{01000000}保留。
				Repeat = (*pData) & 0x3f; // 获得数据组中的长度
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
			case 2: // {10******} 表示重复n次像素
					// {10  +6bit Times}+{1Byte Index}, 表示重复n次像素。
					// {10  +重复1~63次}+{0~255个调色板引索},{10000000}保留。
				Repeat = (*pData) & 0x3f; // 获得重复的次数
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
			case 3: // {11******} 表示跳过n个像素，跳过的像素用透明色代替
					// {11  +6bit Times}, 表示跳过n个像素，跳过的像素用透明色代替。
					// {11  +跳过1~63个像素},{11000000}保留。
				Repeat = (*pData) & 0x3f; // 获得重复次数
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
			default: // 一般不存在这种情况
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