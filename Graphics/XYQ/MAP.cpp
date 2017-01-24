#include "MAP.h"
#include <iostream>
#include <math.h>
#include <memory.h>
#include <SOIL.h>
#include "WAS.h"
using std::cout;
using std::ios;
using std::endl;
namespace NetEase {

	MAP::MAP(string filename) :m_FileName(filename)
	{

		m_FileStream.open(m_FileName, ios::binary | ios::in);
		if (!m_FileStream)
		{
			cout << "Map�ļ���ʧ�ܣ�" << endl;
			return;
		}

		m_FileStream.read((char*)&m_Header, sizeof(MapHeader));
		if (m_Header.Flag != 0x4D312E30)
		{
			cout << "Map�ļ���ʽ����" << endl;
			return;
		}

		m_Width = m_Header.Width;
		m_Height = m_Header.Height;
		cout << "Width:" << m_Width << "\tHeight:" << m_Height << endl;



		m_BlockWidth = 320;
		m_BlockHeight = 240;

		m_ColCount = (uint32)ceil(m_Header.Width / m_BlockWidth);
		m_RowCount = (uint32)ceil(m_Header.Height / m_BlockHeight);
		cout << "Row:" << m_RowCount << " Col:" << m_ColCount << endl;

		m_UnitSize = m_RowCount*m_ColCount;
		m_UnitIndecies = new uint32[m_UnitSize];
		m_FileStream.read((char*)m_UnitIndecies, m_UnitSize * 4);

		// for(int i=0;i<m_UnitSize;i++)
		// {
		// 	printf("i:%d: %x\n",i, m_UnitIndecies[i] );
		// }
		// printf("%d\n", m_UnitSize);

		m_FileStream.read((char*)&m_MaskHeader, sizeof(MaskHeader));
		m_MaskSize = m_MaskHeader.Size;
		m_MaskIndecies = new uint32[m_MaskSize];
		m_FileStream.read((char*)m_MaskIndecies, m_MaskSize * 4);

		// for(int i=0;i<m_MaskSize;i++)
		// {
		// 	printf("i:%d: %x\n",i, m_MaskIndecies[i] );
		// }
		// printf("%d\n", m_MaskSize);		
		cout << "MAP�ļ���ʼ���ɹ���" << endl;
		m_MapUnits.resize(m_UnitSize);	//vector����size
		m_MaskInfos.resize(m_MaskSize);

		m_MapPixelsRGB24 = new uint8[m_RowCount*m_ColCount * 320 * 240 * 3];
		m_MapWidth = m_ColCount * 320;
		m_MapHeight = m_RowCount * 240;

		// printf("MapUnitSize:%d \t MaskSize:%d\n",m_UnitSize,m_MaskSize );
	}

	MAP::~MAP()
	{
		if (m_UnitIndecies != nullptr)
		{
			delete[] m_UnitIndecies;
		}
		if (m_MaskIndecies != nullptr)
		{
			delete[] m_MaskIndecies;
		}
		if (m_FileStream)
		{
			m_FileStream.close();
		}
	}

	void MAP::SaveImageFile(char* filename, int width, int height, int pixelDepth, char* data)
	{
		TGA_FILE_HEADER TgaHeader;
		memset(&TgaHeader, 0, 18);
		TgaHeader.IdLength = 0;			// ͼ����Ϣ�ֶ�(Ĭ��:0)
		TgaHeader.ColorMapType = 0;		// ��ɫ�������(Ĭ��0)
		TgaHeader.ImageType = 0x02;			// ͼ��������(֧��2��10)
		TgaHeader.ColorMapFirstIndex = 0;	// ��ɫ�������(Ĭ��:0)
		TgaHeader.ColorMapLength = 0;		// ��ɫ��ĳ���(Ĭ��:0)
		TgaHeader.ColorMapEntrySize = 0;	// ��ɫ������Ϊ��(Ĭ��:0��֧��16/24/32)
		TgaHeader.XOrigin = 0;				// ͼ��X�������ʼλ��(Ĭ��:0)
		TgaHeader.YOrigin = 0;				// ͼ��Y�������ʼλ��(Ĭ��:0)
		TgaHeader.ImageWidth = width;			// ͼ��Ŀ��
		TgaHeader.ImageHeight = height;			// ͼ��ĸ߶�
		TgaHeader.PixelDepth = pixelDepth;			// ͼ��ÿ���ش洢ռ��λ��
		TgaHeader.ImageDescruptor = 8;		// ͼ�������ַ��ֽ�(Ĭ��:0)

		fstream ofile;
		ofile.open(filename, ios::out | ios::trunc | ios::binary);
		//cout << "дTGAͼ���ļ�ͷ" << endl;
		ofile.write((char*)(&TgaHeader), sizeof(TGA_FILE_HEADER)); // дTGA���ļ�ͷ
																   //cout << "ͼ���ļ�ͷд��ɣ���ʼдͼ�����ݡ�" << endl;
		ofile.write((char*)data, width*height*pixelDepth / 8);
		cout << "��� " << filename << " ֡ͼƬ���~" << endl;
		ofile.close();
	}

	// 2�ֽڸߵ�λ����
	void ByteSwap(uint16& value)
	{
		uint16 tempvalue = value >> 8;
		value = (value << 8) | tempvalue;
	}

	int DecompressMask(void* in, void* out)
	{
		register BYTE *op;
		register  BYTE *ip;
		register unsigned t;
		register  BYTE *m_pos;

		op = (BYTE *)out;
		ip = (BYTE *)in;

		if (*ip > 17) {
			t = *ip++ - 17;
			if (t < 4)
				goto match_next;
			do *op++ = *ip++; while (--t > 0);
			goto first_literal_run;
		}

		while (1) {
			t = *ip++;
			if (t >= 16) goto match;
			if (t == 0) {
				while (*ip == 0) {
					t += 255;
					ip++;
				}
				t += 15 + *ip++;
			}

			*(unsigned *)op = *(unsigned *)ip;
			op += 4; ip += 4;
			if (--t > 0)
			{
				if (t >= 4)
				{
					do {
						*(unsigned *)op = *(unsigned *)ip;
						op += 4; ip += 4; t -= 4;
					} while (t >= 4);
					if (t > 0) do *op++ = *ip++; while (--t > 0);
				}
				else do *op++ = *ip++; while (--t > 0);
			}

		first_literal_run:

			t = *ip++;
			if (t >= 16)
				goto match;

			m_pos = op - 0x0801;
			m_pos -= t >> 2;
			m_pos -= *ip++ << 2;

			*op++ = *m_pos++; *op++ = *m_pos++; *op++ = *m_pos;

			goto match_done;

			while (1)
			{
			match:
				if (t >= 64)
				{

					m_pos = op - 1;
					m_pos -= (t >> 2) & 7;
					m_pos -= *ip++ << 3;
					t = (t >> 5) - 1;

					goto copy_match;

				}
				else if (t >= 32)
				{
					t &= 31;
					if (t == 0) {
						while (*ip == 0) {
							t += 255;
							ip++;
						}
						t += 31 + *ip++;
					}

					m_pos = op - 1;
					m_pos -= (*(unsigned short *)ip) >> 2;
					ip += 2;
				}
				else if (t >= 16) {
					m_pos = op;
					m_pos -= (t & 8) << 11;
					t &= 7;
					if (t == 0) {
						while (*ip == 0) {
							t += 255;
							ip++;
						}
						t += 7 + *ip++;
					}
					m_pos -= (*(unsigned short *)ip) >> 2;
					ip += 2;
					if (m_pos == op)
						goto eof_found;
					m_pos -= 0x4000;
				}
				else {
					m_pos = op - 1;
					m_pos -= t >> 2;
					m_pos -= *ip++ << 2;
					*op++ = *m_pos++; *op++ = *m_pos;
					goto match_done;
				}

				if (t >= 6 && (op - m_pos) >= 4) {
					*(unsigned *)op = *(unsigned *)m_pos;
					op += 4; m_pos += 4; t -= 2;
					do {
						*(unsigned *)op = *(unsigned *)m_pos;
						op += 4; m_pos += 4; t -= 4;
					} while (t >= 4);
					if (t > 0) do *op++ = *m_pos++; while (--t > 0);
				}
				else {
				copy_match:
					*op++ = *m_pos++; *op++ = *m_pos++;
					do *op++ = *m_pos++; while (--t > 0);
				}

			match_done:

				t = ip[-2] & 3;
				if (t == 0)	break;

			match_next:
				do *op++ = *ip++; while (--t > 0);
				t = *ip++;
			}
		}

	eof_found:
		//   if (ip != ip_end) return -1;
		return (op - (BYTE*)out);
	}
	// ��ͼ��JPEG���ݴ�����
	uint8* MAP::MapHandler(uint8* Buffer, uint32 inSize, uint32* outSize)
	{
		// JPEG���ݴ���ԭ��
		// 1������D8��D9�����ݵ���������
		// 2��ɾ����3��4���ֽ� FFA0
		// 3���޸�FFDA�ĳ���00 09 Ϊ 00 0C
		// 4����FFDA���ݵ�������00 3F 00
		// 5���滻FFDA��FF D9֮���FF����ΪFF 00

		uint32 TempNum = 0;						// ��ʱ��������ʾ�Ѷ�ȡ�ĳ���
		uint8* outBuffer;
		uint8* TempBuffer = new uint8[inSize * 2];		// ��ʱ��������ʾ����������
		memset((char*)TempBuffer, 0, inSize * 2);
		outBuffer = TempBuffer;					// �Ѵ������ݵĿ�ʼ��ַ
		uint16 TempTimes = 0;					// ��ʱ��������ʾѭ���Ĵ���
		uint32 Temp = 0;

		// ���Ѷ�ȡ���ݵĳ���С���ܳ���ʱ����
		while (TempNum < inSize && *Buffer++ == 0xFF)
		{
			*TempBuffer++ = 0xFF;
			TempNum++;
			switch (*Buffer)
			{
			case 0xD8:
				*TempBuffer++ = 0xD8;
				*Buffer++;
				TempNum++;
				break;
			case 0xA0:
				*Buffer++;
				TempBuffer--;
				TempNum++;
				break;
			case 0xC0:
				*TempBuffer++ = 0xC0;
				*Buffer++;
				TempNum++;

				memcpy(&TempTimes, Buffer, sizeof(uint16)); // ��ȡ����
				ByteSwap(TempTimes); // ������ת��ΪIntel˳��


				for (int i = 0; i< TempTimes; i++)
				{
					*TempBuffer++ = *Buffer++;
					TempNum++;
				}

				break;
			case 0xC4:
				*TempBuffer++ = 0xC4;
				*Buffer++;
				TempNum++;

				memcpy(&TempTimes, Buffer, sizeof(uint16)); // ��ȡ����
				ByteSwap(TempTimes); // ������ת��ΪIntel˳��

				for (int i = 0; i< TempTimes; i++)
				{
					*TempBuffer++ = *Buffer++;
					TempNum++;
				}
				break;
			case 0xDB:
				*TempBuffer++ = 0xDB;
				*Buffer++;
				TempNum++;

				memcpy(&TempTimes, Buffer, sizeof(uint16)); // ��ȡ����
				ByteSwap(TempTimes); // ������ת��ΪIntel˳��

				for (int i = 0; i< TempTimes; i++)
				{
					*TempBuffer++ = *Buffer++;
					TempNum++;
				}
				break;
			case 0xDA:
				*TempBuffer++ = 0xDA;
				*TempBuffer++ = 0x00;
				*TempBuffer++ = 0x0C;
				*Buffer++;
				TempNum++;

				memcpy(&TempTimes, Buffer, sizeof(uint16)); // ��ȡ����
				ByteSwap(TempTimes); // ������ת��ΪIntel˳��
				*Buffer++;
				TempNum++;
				*Buffer++;

				for (int i = 2; i< TempTimes; i++)
				{
					*TempBuffer++ = *Buffer++;
					TempNum++;
				}
				*TempBuffer++ = 0x00;
				*TempBuffer++ = 0x3F;
				*TempBuffer++ = 0x00;
				Temp += 1; // ����Ӧ����+3�ģ���Ϊǰ���0xFFA0û��-2����������ֻ+1��

						   // ѭ������0xFFDA��0xFFD9֮�����е�0xFF�滻Ϊ0xFF00
				for (; TempNum < inSize - 2;)
				{
					if (*Buffer == 0xFF)
					{
						*TempBuffer++ = 0xFF;
						*TempBuffer++ = 0x00;
						*Buffer++;
						TempNum++;
						Temp++;
					}
					else
					{
						*TempBuffer++ = *Buffer++;
						TempNum++;
					}
				}
				// ֱ��������д����0xFFD9����JpegͼƬ.
				Temp--; // �������һ���ֽڣ����Լ�ȥ��
				*TempBuffer--;
				*TempBuffer-- = 0xD9;
				break;
			case 0xD9:
				// �㷨���⣬���ﲻ�ᱻִ�У������һ����
				*TempBuffer++ = 0xD9;
				TempNum++;
				break;
			default:
				break;
			}
		}
		Temp += inSize;
		*outSize = Temp;
		return outBuffer;
	}



	bool MAP::ReadJPEG(ifstream &file, uint32 size, uint32 index)
	{
		// file.seekg(Size,ios::cur);
		uint8* jpegData = new uint8[size];
		file.read((char*)jpegData, size);

		uint32 tmpSize = 0;
		jpegData = MapHandler(jpegData, size, &tmpSize);

		// MapUnit& mapUnit = m_MapUnits[index];

		/*
		unsigned int width, height;
		struct jdec_private *jdec;
		jdec = tinyjpeg_init();
		tinyjpeg_parse_header(jdec, jpegData, tmpSize);
		//Get the size of the image 
		tinyjpeg_get_size(jdec, &width, &height);
		tinyjpeg_decode(jdec, TINYJPEG_FMT_RGB24);
		tinyjpeg_get_components(jdec, &m_MapUnits[index].BitmapRGB24);
		free(jdec);
		*/
		
		int width, height;
		m_MapUnits[index].BitmapRGB24 = SOIL_load_image_from_memory(jpegData,tmpSize, &width, &height, 0,
			SOIL_LOAD_RGB);
		
		int row = index / m_ColCount;
		int col = index%m_ColCount;
		uint8* pSrc = m_MapUnits[index].BitmapRGB24;
		uint8* pDes = m_MapPixelsRGB24;
		pDes += row * 240 * m_ColCount * 320 * 3 + col * 320 * 3;
		for (int h = 0; h<240; h++) {
			for (int w = 0; w<320 * 3; w++) {
				*(pDes + w) = *pSrc++;
			}
			pDes += m_ColCount * 320 * 3;
		}

		// sprintf(fname,"file2_%d.tga",index);
		// SaveImageFile(fname,width,height,24,(char*)(m_MapPixelsRGB24+(row*320+col*240)*3));
		//  		tinyjpeg_get_components(jdec, &(m_MapPixelsRGB24+(row*320+col*240)*3 ));
		
		delete[] jpegData;
		jpegData = nullptr;

		// 		printf("width: %d height: %d\n",width,height );
		// char name[50];
		// sprintf(name,"out%d.jpg",index);
		// 		SaveImageFile(name,width,height,24,(char*)m_MapUnits[index].BitmapRGB24);
		// 	printf("JPEG%d��ȡ��ɣ�\n",index);
		return true;
	}

	bool MAP::ReadCELL(ifstream &file, uint32 size, uint32 index)
	{
		file.read((char*)m_MapUnits[index].Cell, size);

		// for (int i = 0; i < 12; ++i)
		// {
		// 	for (int j = 0; j < 16; ++j)
		// 	{
		// 		printf("%2x ",m_MapUnits[index].Cell[i*16+j] );
		// 	}
		// 	printf("Cell size:%d\n",size);
		// }
		return true;
	}

	bool MAP::ReadBRIG(ifstream &file, uint32 size, uint32 index)
	{
		// file.seekg(Size,ios::cur);
		return false;
	}

	void MAP::ReadUnit(int index)
	{
		if (m_MapUnits[index].bHasLoad) {
			return;
		}
		m_FileStream.seekg(m_UnitIndecies[index]);

		uint32 eat_num;
		m_FileStream.read((char*)&eat_num, sizeof(uint32));
		m_FileStream.seekg(eat_num * 4, ios::cur);

		// cout<<"eat_num��" <<eat_num<<endl;
		// uint32 eat_data[eat_num];
		// m_FileStream.read((char*)eat_data,eat_num*4);

		//cout<<"m_FileStream tell1:" <<m_FileStream.tellg()<<endl;

		// for(int i= 0;i<eat_num;i++)
		// {
		// 	printf("eat num:%x\n", eat_data[i]);
		// }
		// printf("total eat_number: %d\n" ,eat_num );

		MapUnitHeader* pUnitHeader = new MapUnitHeader();
		memset(pUnitHeader, 0, sizeof(MapUnitHeader));

		bool loop = true;
		while (loop)
		{
			m_FileStream.read((char*)pUnitHeader, sizeof(MapUnitHeader));
			//printf("Flag: %x\n",pUnitHeader->Flag );
			switch (pUnitHeader->Flag)
			{
				// GEPJ "47 45 50 4A"
			case 0x4A504547: {
				ReadJPEG(m_FileStream, pUnitHeader->Size, index);
				// char tmp_filename[50];
				// sprintf(tmp_filename,"%d.tga",UnitNum);
				// SaveImageFile( tmp_filename,(char*)m_rgb);
				break;
			}
							 // LLEC "4C 4C 45 43"
			case 0x43454C4C:
				ReadCELL(m_FileStream, pUnitHeader->Size, index);

				break;
				// GIRB "47 49 52 42"
			case 0x42524947:
				ReadBRIG(m_FileStream, pUnitHeader->Size, index);
				break;
			default:
				// �����־
				// m_ErrorUnit.Flag=pUnitHeader->Flag;
				// m_ErrorUnit.Size=pUnitHeader->Size;
				loop = false;
				break;
			}
		}
		m_MapUnits[index].Index = index;
		m_MapUnits[index].bHasLoad = true;

	}

	void MAP::ReadMask(int index)
	{

		// printf("i:%d  offset:%x\n",index,m_MaskIndecies[index] );
		m_FileStream.seekg(m_MaskIndecies[index]);
		BaseMaskInfo baseMaskInfo;//& maskInfo = m_MaskInfos[index];
		m_FileStream.read((char*)&baseMaskInfo, sizeof(BaseMaskInfo));

		MaskInfo& maskInfo = m_MaskInfos[index];
		maskInfo.StartX = baseMaskInfo.StartX;
		maskInfo.StartY = baseMaskInfo.StartY;
		maskInfo.Width = baseMaskInfo.Width;
		maskInfo.Height = baseMaskInfo.Height;
		maskInfo.Size = baseMaskInfo.Size;

		char* pData = new char[maskInfo.Size];
		m_FileStream.read(pData, maskInfo.Size);

		// printf("w:%d h:%d\n",maskInfo.Width,maskInfo.Height );
		int align_width = (maskInfo.Width / 4 + (maskInfo.Width % 4 != 0)) * 4;	// ��4����Ŀ��
		char* pMaskDataDec = new char[align_width * maskInfo.Height / 4];		// 1���ֽ�4�����أ���Ҫ����4
		int dec_mask_size = DecompressMask(pData, pMaskDataDec);
		// printf("%d %d maskDataDecSize:%d\n",maskInfo.Size,dec_mask_size,(align_width * maskInfo.Height / 4 ));

		//���mask���ݵ��ļ�
		{
			//��mask����ת����TGAͼ��
			{

				// printf("mask width: %d  height : %d\n",maskInfo.width,maskInfo.height );
				// ��ȡmask����
				int pixel_num = maskInfo.Width * maskInfo.Height;
				maskInfo.Data = new uint32[pixel_num];
				uint32* &pOutMaskBmp = maskInfo.Data;

				memset(pOutMaskBmp, 0, sizeof(uint32) * pixel_num);

				for (int h = 0; h<maskInfo.Height; h++)
				{
					for (int w = 0; w<maskInfo.Width; w++)
					{

						int mask_index = (h * align_width + w) * 2;		// ��λ:λ
						BYTE mask_value = pMaskDataDec[mask_index / 8];	// ��λ���ֽ�
						mask_value = (mask_value >> (mask_index % 8));	// ��λ��λ
						if ((mask_value & 3) == 3) {
							int bmpIndex_y = (maskInfo.StartY+h)*m_MapWidth * 3;
							int bmpIndex_x = (maskInfo.StartX+w) * 3;
							int bmpIndex = bmpIndex_y + bmpIndex_x;
							uint8 r = m_MapPixelsRGB24[bmpIndex];
							uint8 g = m_MapPixelsRGB24[bmpIndex + 1];
							uint8 b = m_MapPixelsRGB24[bmpIndex + 2];
							pOutMaskBmp[h*maskInfo.Width + w] = ( 0x80 << 24 )| (b<< 16)| (g << 8 )| r ;
						}
						else {
							pOutMaskBmp[h*maskInfo.Width + w] = 0;
						}
					}
				}
				/*
				char maskFileName[50];
				sprintf(maskFileName, "mask_i%d.tga", index);
				SaveImageFile(maskFileName, maskInfo.Width, maskInfo.Height, 32, (char*)pOutMaskBmp);
				delete[] pOutMaskBmp;
				*/
			}
		}
	}

	void MAP::PrintCellMap()
	{
		int** cells;
		int** mat;
		int mat_row, mat_col;
		int row = m_RowCount;
		int col = m_ColCount;
		cells = new int*[row*col];
		for (int i = 0; i<row*col; i++) {
			cells[i] = new int[192];
		}

		mat_row = row * 12;
		mat_col = col * 16;

		printf("%d %d \n", mat_row, mat_col);

		mat = new int*[row * 12];
		for (int i = 0; i<row * 12; i++) {
			mat[i] = new int[16 * col];
		}

		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				ReadUnit(i*col + j);
				// printf("\nmat:%d\n", i*col+j );
				for (int k = 0; k<192; k++) {
					cells[i*col + j][k] = (m_MapUnits)[i*col + j].Cell[k];
					int cr = k / 16;
					int cl = k % 16;
					// printf("%d ", cells[i*col+j][k]);
					// if(cl==15)printf("\n");
				}
				int startMat_i = i * 12;
				int startMat_j = j * 16;
				for (int p = 0; p < 12; p++) {
					for (int q = 0; q<16; q++) {
						mat[startMat_i + p][startMat_j + q] = cells[i*col + j][p * 16 + q];
					}
				}
			}
		}

		for (int i = 0; i<mat_row; i++) {
			for (int j = 0; j<mat_col; j++) {
				printf("%d", mat[i][j]);
			}
			printf("\n");
		}

	}
}

/*

int main()
{
	NetEase::MAP xyqMap("1501.map");
	// printf("m_UnitSize: %d \n", netEaseMap.m_UnitSize );
	for (int i = 0; i<xyqMap.m_UnitSize; i++)
	{
		//printf("i:%d: %x\n",i, xyqMap.m_MaskIndecies[i] );
		xyqMap.ReadUnit(i);
		//xyqMap.ReadMask(i);

	}
	for (int i = 0; i<xyqMap.m_MaskSize; i++)
	{
		xyqMap.ReadMask(i);
		//char* filename,int width,int height,int pixelDepth,char* data
	}
	xyqMap.SaveImageFile("b.tga", xyqMap.m_ColCount * 320, xyqMap.m_RowCount * 240, 24, (char*)&xyqMap.m_MapPixelsRGB24[0]);
	printf("%d\n", xyqMap.m_MaskSize);


	return 0;
}
*/