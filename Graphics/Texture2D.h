#pragma once

#include "../defines.h"
#include "../definesTypes.h"
#include "../Logger.h"
#include "../Graphics/XYQ/Sprite2.h"
#include <GL\glew.h>




namespace star
{
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


