#include "Font.h"
#include "../Logger.h"


namespace star
{
	Font::Font():
		m_FontPath(EMPTY_STRING),
		mFace(0),
		mTextures(nullptr),
		mMaxLetterHeight(),
		mMinLetterHeight(),
		mCharacterInfoMap(),
		mSize(0)
	{
	}

	Font::~Font()
	{
		mCharacterInfoMap.clear();
	}

	bool Font::Init(const tstring& path, uint32 size, FT_Library& library)
	{
		mSize = size;
	//	mTextures = new GLuint[FONT_TEXTURES];
		m_FontPath = path;

		//Convert from wstring to const schar* trough sstring
		sstring font_path = string_cast<sstring>(path);
		FT_Error error = FT_New_Face(library,font_path.c_str(),0,&mFace);

		if(error == FT_Err_Unknown_File_Format)
		{
			LOG(star::LogLevel::Error,
				_T("Font Manager : Font : ") + path +
				_T(" ,could be opened but it's in an unsupported format"),
				STARENGINE_LOG_TAG);
			return (false);
		}
		else if(error)
		{
			LOG(star::LogLevel::Error,
				_T("Font Manager : Font : ") + path +
				_T(" ,is invalid and can't be opened or read."),
				STARENGINE_LOG_TAG);
			return (false);
		}
		LOG(star::LogLevel::Info,
			_T("Font Manager : Font : ") + path + 
			_T(" ,loaded and ready for use"),
			STARENGINE_LOG_TAG);

		int32 iSize = int32(size);
		FT_Set_Char_Size(mFace, iSize << 6, iSize << 6, FONT_DPI, FONT_DPI);
		
		// Disable byte-alignment restriction
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//glGenTextures(FONT_TEXTURES, mTextures);
		/*for(suchar i = 0; i < FONT_TEXTURES; ++i)
		{
			mCharacterInfoMap.insert(std::make_pair(i, CharacterInfo()));
			Make_D_List(mFace, i, mTextures);
		}*/
		//FT_Done_Face(mFace);
		return true;
	}

	void Font::DeleteFont()
	{
		//glDeleteTextures(FONT_TEXTURES,mTextures);
		//delete[] mTextures;
	/*	auto map_it = mCharacterInfoMap.cbegin();
		while (map_it != mCharacterInfoMap.cend())
		{
			glDeleteTextures(1,&(map_it->second).textureId);
			++map_it;
		}
		mCharacterInfoMap.clear();
		FT_Done_Face(mFace);
		*/
	}

	CharacterInfo Font::Make_D_List(swchar ch)
	{
		CharacterInfo charInfo = CharacterInfo();
		auto error = FT_Load_Char(mFace, ch, FT_LOAD_DEFAULT);
		if(error)
		{
			LOG(star::LogLevel::Error, 
				_T("Font : could not load glyph"), STARENGINE_LOG_TAG);
			return charInfo;
		}

		error = FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);
		if(error)
		{
			LOG(star::LogLevel::Error,
				_T("Font : could not load glyph"), STARENGINE_LOG_TAG);
			return charInfo;
		}

		FT_Bitmap& bitmap = mFace->glyph->bitmap;

		int32 width = NextPowerOfTwo(bitmap.width);
		int32 height = NextPowerOfTwo(bitmap.rows);

		GLubyte* expanded_data = new GLubyte[2 * width * height];

		for(int32 j = 0; j < height; ++j) 
		{
			for(int32 i = 0; i < width; ++i) 
			{
				expanded_data[2 * (i + j * width)] = 255;
				expanded_data[2 * (i + j * width) + 1] = 
					(i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			}
		}
		//mCharacterInfoMap[ch] = *new CharacterInfo();
		glGenTextures(GL_TEXTURE_2D, &(charInfo.textureId));
		glBindTexture(GL_TEXTURE_2D, charInfo.textureId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, expanded_data);

		//OPENGL_LOG();
		if (expanded_data != NULL) {
			delete[] expanded_data;
		}
		//uvs
		float32 x = static_cast<float32>(bitmap.width) / static_cast<float32>(width);
		float32 y = static_cast<float32>(bitmap.rows) / static_cast<float32>(height);
		//letter height
		int32 dimX = (mFace->glyph->metrics.horiAdvance / 64);
		int32 dimY = ((mFace->glyph->metrics.horiBearingY) - (mFace->glyph->metrics.height)) / 64;
		if(mMaxLetterHeight < mFace->glyph->bitmap_top)
		{
			mMaxLetterHeight = mFace->glyph->bitmap_top;
		}
		if(mMinLetterHeight > dimY)
		{
			mMinLetterHeight = dimY;
		}
		charInfo.letterDimensions = ivec2(dimX, dimY);
		charInfo.vertexDimensions = vec2(bitmap.width, bitmap.rows);
		charInfo.uvDimensions = vec2(x, y);
		return charInfo;
	}

	const tstring & Font::GetFontPath() const
	{
		return m_FontPath;
	}

	GLuint* Font::GetTextures() const
	{
		return mTextures;
	}

	uint32 Font::GetFontSize() const 
	{
		return mSize;
	}

	int32 Font::NextPowerOfTwo(int32 number) const
	{
		int32 rval = 1;
		while(rval < number)
		{
			rval <<= 1;
		}
		return rval;
	}

	const  std::map<wchar_t, CharacterInfo> & Font::GetCharacterInfoMap() const
	{
		return mCharacterInfoMap;
	}

	CharacterInfo Font::GetCharacterInfo(swchar character)
	{
		/*[COMMENT] Performing a good check here 0
		with std::find will only slow things down
		If the map.at has an unknown value, it will throw an exception anyway*/
		if (mCharacterInfoMap.find(character) == mCharacterInfoMap.end())
		{
			mCharacterInfoMap[character] = Make_D_List(character);
			//mCharacterInfoMap[(std::make_pair(character, Make_D_List(character)));
			
		}
		return mCharacterInfoMap[character];
	}

	int32 Font::GetMaxLetterHeight() const 
	{
		return mMaxLetterHeight;
	}

	int32 Font::GetMinLetterHeight() const 
	{
		return mMinLetterHeight;
	}

	uint32 Font::GetStringLength(const std::wstring& wstr) 
	{
		int32 length = 0;
		
		for(uint32 i = 0; i< wstr.size(); ++i)
		{
			CharacterInfo info = GetCharacterInfo(wstr[i]);
			length += info.letterDimensions.x;
		}
		return length;
	}
}
