#pragma once

#include "../defines.h"
#include "../Helpers/FilePath.h"
#include "../Helpers/Helpers.h"
#include <map>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace star
{
#define FONT_DPI 96
#define FONT_TEXTURES 128

	struct CharacterInfo
	{
		CharacterInfo()
			: vertexDimensions()
			, uvDimensions()
			, letterDimensions() 
			//, textureId(0)
		{}
		vec2    vertexDimensions,
				uvDimensions;
		ivec2	letterDimensions;
		GLuint  textureId;
	};

	class Font
	{
	public:
		Font();
		~Font();

		bool Init(const tstring& path, uint32 size, FT_Library& library);
		void DeleteFont();

		const tstring & GetFontPath() const;

		GLuint* GetTextures() const;
		uint32  GetFontSize() const;
		
		const std::map<swchar, CharacterInfo> & GetCharacterInfoMap() const;
		CharacterInfo GetCharacterInfo(swchar character)  ;
		int32 GetMaxLetterHeight() const;
		int32 GetMinLetterHeight() const;
		uint32 GetStringLength(const std::wstring& string) ;
		

	private:
		CharacterInfo Make_D_List( swchar ch);
		int32 NextPowerOfTwo(int32 number) const;

		tstring m_FontPath;
		FT_Face mFace;
		GLuint* mTextures;
		int32	mMaxLetterHeight,
				mMinLetterHeight;

		std::map<swchar, CharacterInfo> mCharacterInfoMap;
		uint32 mSize;
	};
}
