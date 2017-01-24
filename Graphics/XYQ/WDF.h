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
			uint32 flag; // �����ı�ǩ
			uint32 number; // �����е��ļ�����
			uint32 offset; // �����е��ļ��б�ƫ��λ��
		};

		struct Index
		{
			uint32 hash; // �ļ�������ɢ��
			uint32 offset; // �ļ���ƫ��
			uint32 size; // �ļ��Ĵ�С
			uint32 spaces; // �ļ��Ŀռ�
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
