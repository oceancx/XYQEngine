#ifndef MAP_H
#define MAP_H 
#include "../../defines.h"

#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::ifstream;
using std::fstream;

namespace NetEase {
	// 地图的文件头(梦幻、大话2)
	struct MapHeader
	{
		//public:
		// 文件头结构共12字节
		uint32		Flag;		//文件标志
		uint32		Width;		//地图宽
		uint32		Height;		//地图高	
	};

	// 地图的单元头
	struct MapUnitHeader
	{
		//public:
		uint32		Flag;		// 单元标志
		uint32		Size;		// 单元大小
	};

	// 地图的数据
	struct MapData
	{
		//public:
		uint32		Size;		// 数据大小
		uint8		*Data;		// 数据内容
	};

	struct MaskHeader
	{
		uint32	Flag;
		uint32	Size;
	};

	struct BaseMaskInfo
	{
		int	StartX;
		int	StartY;
		uint32	Width;
		uint32	Height;
		uint32	Size;	// mask数据大小

	};

	struct MaskInfo : BaseMaskInfo
	{
		uint32* Data;
	};

	struct UnKnown
	{
		uint32 Offset;
		uint32 *Data;			//n字节 未知用途，大小为：第一个单元引索值减去文件头大小。
	};

	struct MapUnit
	{
		uint8  Cell[192];
		uint8* BitmapRGB24;
		uint32 Index;
		bool bHasLoad = false;
	};

	class MAP
	{
	public:
		MAP(string filename);
		~MAP();
		void ReadUnit(int index);
		void ReadUnit(int row, int col) { ReadUnit(row*m_ColCount + col); };
		void ReadMask(int index);
		uint8* MapHandler(uint8* jpegData, uint32 inSize, uint32* outSize);
		bool ReadJPEG(ifstream &file, uint32 size, uint32 index);
		bool ReadCELL(ifstream &file, uint32 size, uint32 index);
		bool ReadBRIG(ifstream &file, uint32 size, uint32 index);
		void PrintCellMap();
		void SaveImageFile(char* filename, int width, int height, int pixelDepth, char* data);
		ifstream m_FileStream;
		string m_FileName;
		int m_Width;
		int m_Height;
		int m_MapWidth;
		int m_MapHeight;
		float m_BlockWidth;
		float m_BlockHeight;
		uint32 m_RowCount;
		uint32 m_ColCount;
		uint32 m_Pixcels;
		MapHeader m_Header;
		uint32* m_UnitIndecies;	//4*n字节  地图单元的引索 n=地图的宽度/640*2 * 地图高度/480*2
		uint32 m_UnitSize;

		MaskHeader m_MaskHeader;
		uint32* m_MaskIndecies;
		uint32 m_MaskSize;
		std::vector<MapUnit> m_MapUnits;
		std::vector<MaskInfo> m_MaskInfos;
		uint8* m_MapPixelsRGB24;
		//uint8* m_Cur_MapPixelsRGB24;


	};
}

#endif