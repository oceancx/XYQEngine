#include "Texture2D.h"

#include "../Helpers/Helpers.h"
#include <SOIL.h>
#include "../Graphics/XYQ/WDF.h"
namespace star
{
	const tstring Texture2D::LIBSOIL_LOG_TAG = _T("LIBSOIL");

	Texture2D::Texture2D(const tstring & pPath)
			: mTextureId(0)
			, mFormat(0)
			, mWidth(0)
			, mHeight(0)
			, mPath(pPath)
	{
		Load();
	}

	Texture2D::Texture2D(const tstring & pPath,int width, int height, uint8* src)
		: mTextureId(0)
		, mFormat(0)
		, mWidth(0)
		, mHeight(0)
		, mPath(pPath)
	{

		Load(width,height,src);
	}
	

	Texture2D::~Texture2D()
	{
		if(mTextureId != 0)
		{
			glDeleteTextures(1, &mTextureId);
			mTextureId = 0;
		}
		mWidth = 0;
		mHeight = 0;
		mFormat = 0;
	}
	
	uint8* Texture2D::ReadImage()
	{
		FILE *fp;
		tfopen(&fp, mPath.c_str(), _T("rb"));

		if (fp == NULL)
		{
			LOG(LogLevel::Error,
				_T("Texture2D::ReadSOIL: the image \"") +
				mPath +
				_T("\" could not be loaded"), LIBSOIL_LOG_TAG
			);
			return NULL;
		}
		mFormat = GL_RGB;
		return	SOIL_load_image(mPath.c_str(), &mWidth,&mHeight, 0, SOIL_LOAD_RGB);
	}

	uint8* Texture2D::ReadTGA()
	{
		FILE *fp;
		tfopen(&fp, mPath.c_str(), _T("rb"));
		if (fp == NULL)
		{
			LOG(LogLevel::Error,
				_T("Texture2D::ReadSOIL: the image \"") +
				mPath +
				_T("\" could not be loaded"), LIBSOIL_LOG_TAG
			);
			return NULL;
		}
		TGA_FILE_HEADER header;
		fread((char*)&header, sizeof(header), 1, fp);
		mWidth = header.ImageWidth;
		mHeight = header.ImageHeight;
		uint8* data = new uint8[mWidth*mHeight * 4];
		fread((char*)data, mWidth*mHeight * 4, 1, fp);
		mFormat = GL_RGBA;
		return	data;
	}

	void Texture2D::Load(int width,int height,uint8* src)
	{
		uint8* lImageBuffer;
		mWidth = width;
		mHeight = height;
		lImageBuffer = src;
		//mFormat = buffer.format;
		mFormat = GL_RGBA;
		if(lImageBuffer == NULL)
		{
			LOG(LogLevel::Error, 
				_T("PNG : ReadSOIL FAILED - NO IMAGE BUFFER"), LIBSOIL_LOG_TAG);
			return;
		}

		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, lImageBuffer);
		delete[] lImageBuffer;
	}


	void Texture2D::Load()
	{
		uint8* lImageBuffer;
		
		tstring suffix = mPath.substr(mPath.find_last_of('.'), mPath.length());
		if (suffix.compare(".tga") == 0)
		{
			lImageBuffer = ReadTGA();
		}
		else
		{
			lImageBuffer = ReadImage();
		}
		
		if (lImageBuffer == NULL)
		{
			LOG(LogLevel::Error,
				_T("PNG : ReadSOIL FAILED - NO IMAGE BUFFER"), LIBSOIL_LOG_TAG);
			return;
		}

		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		/*	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, lImageBuffer);
		//glGenerateMipmap(GL_TEXTURE_2D);
		delete[] lImageBuffer;
	}

	const tstring & Texture2D::GetPath() const
	{
		return mPath;
	}

	int32 Texture2D::GetHeight() const
	{
		return mHeight;
	}

	int32 Texture2D::GetWidth() const
	{
		return mWidth;
	}

	GLuint Texture2D::GetTextureID() const
	{
		return mTextureId;
	}
}
