#ifndef SPRITE2_H
#define SPRITE2_H 
#include "../../defines.h"
#include <vector>
/*
一个动画序列组
*/


class Sprite2
{

public:
	Sprite2();
	~Sprite2();

	int mGroupSize;		//方向数
	int mFrameSize;		//帧数
	int mWidth;			//宽度
	int mHeight;		//高度
	int mKeyX;			//关键帧X
	int mKeyY;			//关键帧Y

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