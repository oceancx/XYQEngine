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
	// ��ͼ���ļ�ͷ(�λá���2)
	struct MapHeader
	{
		//public:
		// �ļ�ͷ�ṹ��12�ֽ�
		uint32		Flag;		//�ļ���־
		uint32		Width;		//��ͼ��
		uint32		Height;		//��ͼ��	
	};

	// ��ͼ�ĵ�Ԫͷ
	struct MapUnitHeader
	{
		//public:
		uint32		Flag;		// ��Ԫ��־
		uint32		Size;		// ��Ԫ��С
	};

	// ��ͼ������
	struct MapData
	{
		//public:
		uint32		Size;		// ���ݴ�С
		uint8		*Data;		// ��������
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
		uint32	Size;	// mask���ݴ�С

	};

	struct MaskInfo : BaseMaskInfo
	{
		uint32* Data;
	};

	struct UnKnown
	{
		uint32 Offset;
		uint32 *Data;			//n�ֽ� δ֪��;����СΪ����һ����Ԫ����ֵ��ȥ�ļ�ͷ��С��
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
		uint32* m_UnitIndecies;	//4*n�ֽ�  ��ͼ��Ԫ������ n=��ͼ�Ŀ��/640*2 * ��ͼ�߶�/480*2
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