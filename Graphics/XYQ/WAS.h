#ifndef WAS_H
#define WAS_H 
#include "../../defines.h"
#include <string>
#include <fstream>
#include <memory.h>
using namespace std;



#pragma pack(push) //�������״̬
#pragma pack(1)//�趨Ϊ4�ֽڶ���
// TGA �ļ�ͷ
struct TGA_FILE_HEADER
{
	uint8 IdLength;             // ͼ����Ϣ�ֶ�(Ĭ��:0)
	uint8 ColorMapType;         // ��ɫ�������(Ĭ��0)
	uint8 ImageType;            // ͼ��������(֧��2��10)
	uint16 ColorMapFirstIndex;  // ��ɫ�������(Ĭ��:0)
	uint16 ColorMapLength;      // ��ɫ��ĳ���(Ĭ��:0)
	uint8 ColorMapEntrySize;    // ��ɫ������Ϊ��(Ĭ��:0��֧��16/24/32)
	uint16 XOrigin;             // ͼ��X�������ʼλ��(Ĭ��:0)
	uint16 YOrigin;             // ͼ��Y�������ʼλ��(Ĭ��:0)
	uint16 ImageWidth;          // ͼ��Ŀ��
	uint16 ImageHeight;         // ͼ��ĸ߶�
	uint8 PixelDepth;           // ͼ��ÿ���ش洢ռ��λ��
	uint8 ImageDescruptor;      // ͼ�������ַ��ֽ�(Ĭ��:0����֧��16bit 565��ʽ)
};
#pragma pack(pop)//�ָ�����״̬
class WAS
{
public:

	// ���鶯�����ļ�ͷ
	struct Header
	{
		uint16 flag;		// �����ļ���־ SP 0x5053
		uint16 len;		// �ļ�ͷ�ĳ��� Ĭ��Ϊ 12
		uint16 group;		// ����ͼƬ����������������
		uint16 frame;		// ÿ���ͼƬ������֡��
		uint16 width;		// ���鶯���Ŀ�ȣ���λ����
		uint16 height;		// ���鶯���ĸ߶ȣ���λ����
		uint16 key_x;		// ���鶯���Ĺؼ�λX
		uint16 key_y;		// ���鶯���Ĺؼ�λY
	};

	// ֡���ļ�ͷ
	struct FrameHeader
	{
		int key_x;			// ͼƬ�Ĺؼ�λX
		int key_y;			// ͼƬ�Ĺؼ�λY
		int width;			// ͼƬ�Ŀ�ȣ���λ����
		int height;			// ͼƬ�ĸ߶ȣ���λ����
	};


	WAS(std::string filename, int offset, int size);
	WAS(fstream &infile, int offset, int size);
	static uint32 RGB565to888(uint16 color, uint8 alpha); // 565ת888
	static uint16 Alpha565(uint16 src, uint16 des, uint8 alpha);
	static uint8 MixAlpha(uint8 color, uint8 alpha);
	~WAS();
	Header mHeader;
	uint32 mPalette32[256];
	uint32* mFrameIndecies;
	std::string mFileName;
	int mFileOffset;
	int mFileSize;

};
#endif