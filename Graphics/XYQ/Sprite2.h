#ifndef SPRITE2_H
#define SPRITE2_H 
#include "../../defines.h"
#include <vector>
/*
һ������������
*/


class Sprite2
{

public:
	Sprite2();
	~Sprite2();

	int mGroupSize;		//������
	int mFrameSize;		//֡��
	int mWidth;			//���
	int mHeight;		//�߶�
	int mKeyX;			//�ؼ�֡X
	int mKeyY;			//�ؼ�֡Y

	struct Sequence
	{
		int key_x;
		int key_y;
		int width;
		int height;
		uint32 format;
		uint32* src;
	};

	Sequence** mFrames;
	void SaveImage(int index);
};
#endif