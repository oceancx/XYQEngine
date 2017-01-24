#include "SpriteArrayComponent.h"
#include "../../Objects/Object.h"
#include "../../Graphics/SpriteBatch.h"
#include "../../Graphics/TextureManager.h"
//#include "SpriteSheetComponent.h"
//#include "TextComponent.h"
#include "../../Graphics/XYQ/WDF.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Helpers/AARect.h"
//#include "../../Graphics/Color.h"
#include <SOIL.h>

namespace star
{
	SpriteArrayComponent::SpriteArrayComponent(
		const tstring& filepath,
		const tstring& spriteName,
		uint32 widthSegments,
		uint32 heightSegments
	)
		: BaseComponent()
		, m_WidthSegments(widthSegments)
		, m_HeightSegments(heightSegments)
		, m_CurrentWidthSegment(0)
		, m_CurrentHeightSegment(0)
		, m_FilePath(filepath)
		, m_SpriteName(spriteName)
		, m_SpriteInfo(nullptr)
	{
		m_SpriteInfo = new SpriteInfo();
	}

	void SpriteArrayComponent::InitializeComponent()
	{
		/*if(m_pParentObject->HasComponent<SpriteSheetComponent>(this)
		|| m_pParentObject->HasComponent<TextComponent>(this))
		{
		ASSERT_LOG(false,
		_T("Object '") + m_pParentObject->GetName() +
		_T("': Can't add a SpriteArrayComponent when already \
		having a SpriteSheet- or TextComponent."), STARENGINE_LOG_TAG);
		m_pParentObject->RemoveComponent(this);
		}
		else
		{*/
		/*读取人物Sprite*/
		NetEase::WDF wdf("E:\\梦幻西游\\shape.wdf");
		Sprite2 sprite = wdf.LoadSprite(0x3EAE6B97);
		for (int i = 0; i<sprite.mFrameSize*sprite.mGroupSize; i++) {
			int gpos = i / sprite.mFrameSize;
			int cpos = i%sprite.mFrameSize;
			tstring path = m_FilePath.GetFullPath();
			path.append(std::to_string(i));
			tstring name = m_SpriteName;
			name.append(std::to_string(i));
			TextureManager::GetInstance()
				->LoadTexture(path,name,sprite.mWidth,sprite.mHeight,(uint8*)sprite.mFrames[gpos][cpos].src);
		}
		
		m_Dimensions.x = sprite.mWidth;
		m_Dimensions.y = sprite.mHeight;
		GetTransform()->SetDimensionsSafe(m_Dimensions);


		m_IsPlaying = true;
		m_CurrentFrame = 0;
		m_CurrentRepeats = 0;
		m_Repeat = 1;
		m_Speed = 10;
		
		m_Count = sprite.mFrameSize*sprite.mGroupSize;
		m_Dir = 0;

		CreateUVCoords();
		FillSpriteInfo();
		//}
	}

	void SpriteArrayComponent::FillSpriteInfo()
	{
	
		for (int i = 0; i < m_Count; i++)
		{
			auto name = m_SpriteName;
			name.append(std::to_string(i));
			auto id = TextureManager::GetInstance()->GetTextureID(name);
			m_TextureIds.push_back(id);
		}
		/*m_SpriteInfo->textureID =
			TextureManager::GetInstance()->GetTextureID(m_SpriteName);*/
		m_SpriteInfo->vertices = vec2(m_Dimensions.x, m_Dimensions.y);
	}

	SpriteArrayComponent::~SpriteArrayComponent()
	{
		delete m_SpriteInfo;
	}

	void SpriteArrayComponent::CreateUVCoords()
	{
		float32 startX =
			float32(m_CurrentWidthSegment) /
			float32(m_WidthSegments);
		float32 endX = 1.0f / m_WidthSegments;
		float32 startY =
			float32(m_CurrentHeightSegment) /
			float32(m_HeightSegments);
		float32 endY = 1.0f / m_HeightSegments;
		SetUVCoords(vec4(startX, startY, endX, endY));
	}

	void SpriteArrayComponent::SetUVCoords(const vec4& coords)
	{
		m_SpriteInfo->uvCoords = coords;
	}

	void SpriteArrayComponent::Draw()
	{
		std::cout << "m_CurrentFrame:" << m_CurrentFrame << std::endl;
		std::cout << "textureID:" << m_TextureIds[m_CurrentFrame] << std::endl;
		m_SpriteInfo->transformPtr = GetTransform();
		m_SpriteInfo->textureID = m_TextureIds[m_CurrentFrame];
		
		int x = GetTransform()->GetLocalPosition().x;
		int y = GetTransform()->GetLocalPosition().y;
		int w = GetTransform()->GetDimensions().x;
		int h = GetTransform()->GetDimensions().y;
		AARect r = AARect(x, y, w, h);
		Color c = Color::Orange;
	
		SpriteBatch::GetInstance()->AddSpriteToQueue(m_SpriteInfo);
		DebugDraw::GetInstance()->DrawRect(r, c);
	}

	void SpriteArrayComponent::Update(const Context & context)
	{
		//[COMMENT] Temp hotfix!
#ifdef ANDROID
		FillSpriteInfo();
#endif
		if (m_IsPlaying)
		{
			m_CurrentFrame += context.dt * m_Speed;
			std::cout << "time:" << context.dt << std::endl;
				//float32(context.time->DeltaTime().GetSeconds() * m_Speed);
			float32 size = float32(m_TextureIds.size());
			bool readyToGo(false);
			if (m_CurrentFrame >= size)
			{
				m_CurrentFrame = 0;
				readyToGo = true;
			}
			else if (m_CurrentFrame < 0)
			{
				m_CurrentFrame = size - 1;
				readyToGo = true;
			}
			if (readyToGo && m_Repeat != -1)
			{
				++m_CurrentRepeats;
				if (m_CurrentRepeats > m_Repeat)
				{
					m_CurrentRepeats = 0;
					m_CurrentFrame = size - 1;
					m_IsPlaying = false;
					/*if (m_Callback != nullptr)
					{
						m_Callback();
					}
					if (m_UserCallback != nullptr)
					{
						m_UserCallback();
					}*/
				}
			}
		}
		
	}

	bool SpriteArrayComponent::CheckCulling(
		float left,
		float right,
		float top,
		float bottom
	) const
	{
		//Always draw hudObjects
		if (m_SpriteInfo->bIsHud)
		{
			return true;
		}

		float32 spriteWidth, spriteHeight;

		pos objectPos = GetTransform()->GetWorldPosition();

		if (m_SpriteInfo->bIsHud)
		{
			objectPos.x += left;
			objectPos.y += bottom;
		}

		spriteWidth = float32(GetWidth()) * GetTransform()->GetWorldScale().x;
		spriteHeight = float32(GetHeight()) * GetTransform()->GetWorldScale().y;
		float32 objRight = objectPos.x + spriteWidth;
		float32 objTop = objectPos.y + spriteHeight;

		return
			(objectPos.x <= right && objRight >= left)
			&&
			(objectPos.y <= top && objTop >= bottom);
	}

	const tstring& SpriteArrayComponent::GetFilePath() const
	{
		return m_FilePath.GetPath();
	}

	const tstring& SpriteArrayComponent::GetName() const
	{
		return m_SpriteName;
	}

	void SpriteArrayComponent::SetCurrentSegment(uint32 widthSegment, uint32 heightSegment)
	{
		m_CurrentWidthSegment = widthSegment;
		m_CurrentHeightSegment = m_HeightSegments - heightSegment - 1;
		CreateUVCoords();
	}

	void SpriteArrayComponent::SetColorMultiplier(const Color & color)
	{
		m_SpriteInfo->colorMultiplier = color;
	}

	void SpriteArrayComponent::SetHUDOptionEnabled(bool enabled)
	{
		m_SpriteInfo->bIsHud = enabled;
	}

	bool SpriteArrayComponent::IsHUDOptionEnabled() const
	{
		return m_SpriteInfo->bIsHud;
	}

	void SpriteArrayComponent::SetTexture(
		const tstring& filepath,
		const tstring& spriteName,
		uint32 widthSegments,
		uint32 heightSegments
	)
	{
		m_Dimensions.x = 0;
		m_WidthSegments = widthSegments;
		m_CurrentWidthSegment = 0;
		m_Dimensions.y = 0;
		m_HeightSegments = heightSegments;
		m_CurrentHeightSegment = 0;
		m_FilePath = FilePath(filepath);
		m_SpriteName = spriteName;

		TextureManager::GetInstance()->LoadTexture(m_FilePath.GetFullPath(), m_SpriteName);
		m_Dimensions.x = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x / m_WidthSegments;
		m_Dimensions.y = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y / m_HeightSegments;

		GetTransform()->SetDimensionsSafe(m_Dimensions);

		CreateUVCoords();
		FillSpriteInfo();
	}

}
