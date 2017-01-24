#pragma once

#include "../defines.h"
#include "../definesTypes.h"
#include "../Logger.h"
#include "../Graphics/XYQ/Sprite2.h"
#include <GL\glew.h>




namespace star
{
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

	class Texture2D final
	{
	public:
		//[NOTE]	You're not supposed to make Textures yourself.
		//			Use the TextureManager to load your textures.
		//			This ensures a same texture is not loaded multiple times
		Texture2D(const tstring & pPath);
		Texture2D(const tstring & pPath,int width,int height, uint8 * src);
		~Texture2D();

		const tstring & GetPath() const;
		int32 GetHeight() const;
		int32 GetWidth() const;
		GLuint GetTextureID() const;

	private:
		//uint8* ReadPNG();
		uint8* ReadImage();
		uint8* ReadTGA();
		void Load();
		void Load(int width,int height,uint8* src);
		
		GLuint	mTextureId;	
		GLint	mFormat;
		int32 mWidth, mHeight;
		tstring mPath;

		static const tstring LIBSOIL_LOG_TAG;

		/*static void CustomErrorFunction(png_structp pngPtr, png_const_charp error);
		static void CustomWarningFunction(png_structp pngPtr, png_const_charp warning);*/
		Texture2D(const Texture2D& yRef);
		Texture2D(Texture2D&& yRef);
		Texture2D& operator=(const Texture2D& yRef);
		Texture2D& operator=(Texture2D&& yRef);
	};
}


