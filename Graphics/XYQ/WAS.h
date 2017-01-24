#ifndef WAS_H
#define WAS_H 
#include "../../defines.h"
#include <string>
#include <fstream>
#include <memory.h>
using namespace std;



#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为4字节对齐
// TGA 文件头
struct TGA_FILE_HEADER
{
	uint8 IdLength;             // 图像信息字段(默认:0)
	uint8 ColorMapType;         // 颜色标的类型(默认0)
	uint8 ImageType;            // 图像类型码(支持2或10)
	uint16 ColorMapFirstIndex;  // 颜色表的引索(默认:0)
	uint16 ColorMapLength;      // 颜色表的长度(默认:0)
	uint8 ColorMapEntrySize;    // 颜色表表项的为数(默认:0，支持16/24/32)
	uint16 XOrigin;             // 图像X坐标的起始位置(默认:0)
	uint16 YOrigin;             // 图像Y坐标的起始位置(默认:0)
	uint16 ImageWidth;          // 图像的宽度
	uint16 ImageHeight;         // 图像的高度
	uint8 PixelDepth;           // 图像每像素存储占用位数
	uint8 ImageDescruptor;      // 图像描述字符字节(默认:0，不支持16bit 565格式)
};
#pragma pack(pop)//恢复对齐状态
class WAS
{
public:

	// 精灵动画的文件头
	struct Header
	{
		uint16 flag;		// 精灵文件标志 SP 0x5053
		uint16 len;		// 文件头的长度 默认为 12
		uint16 group;		// 精灵图片的组数，即方向数
		uint16 frame;		// 每组的图片数，即帧数
		uint16 width;		// 精灵动画的宽度，单位像素
		uint16 height;		// 精灵动画的高度，单位像素
		uint16 key_x;		// 精灵动画的关键位X
		uint16 key_y;		// 精灵动画的关键位Y
	};

	// 帧的文件头
	struct FrameHeader
	{
		int key_x;			// 图片的关键位X
		int key_y;			// 图片的关键位Y
		int width;			// 图片的宽度，单位像素
		int height;			// 图片的高度，单位像素
	};


	WAS(std::string filename, int offset, int size);
	WAS(fstream &infile, int offset, int size);
	static uint32 RGB565to888(uint16 color, uint8 alpha); // 565转888
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