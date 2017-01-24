#ifndef WDF_H
#define WDF_H 
// #include <string>
// #include <vector>
#include <map>
// #include <iostream>
#include <fstream>
#include "WAS.h"
#include "Sprite2.h"

// #include "Sprite.h"
using namespace std;
namespace NetEase {
	class WDF
	{
		struct Header
		{
			uint32 flag; // 包裹的标签
			uint32 number; // 包裹中的文件数量
			uint32 offset; // 包裹中的文件列表偏移位置
		};

		struct Index
		{
			uint32 hash; // 文件的名字散列
			uint32 offset; // 文件的偏移
			uint32 size; // 文件的大小
			uint32 spaces; // 文件的空间
		};

	public:
		WDF();
		WDF(std::string filename) :mFilename(filename) { Init(); }
		void DataHandler(char *pData, uint32* pBmpStart, int pixelOffset, int pixelLen);
		void Init();
		// Sprite LoadSprite(int id);
		WAS GetWAS(int id);
		Sprite2 LoadSprite(int id);
		~WDF();

	public:
		// std::string mFilename;
		Header mHeader;
		Index* mIndencies;
		map<int, int> mIdToPos;
		fstream mFile;
		uint16 palette16[256];
		string mFilename;
		uint32 m_Palette32[256];

	};
}
#endif
