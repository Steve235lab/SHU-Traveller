#pragma once
#include "Landmark.h"


// 首尾结点间的直线距离
// 程序启动时将创建二维对象数组 Edge edges[256][256]
class Edge
{
	double pixDist;			// 此边首尾结点间像素距离 单位：pixels
	double realDist;		// 此边首尾结点间真实距离 单位：m
	static double scale;	// 地图比例尺 scale = realDist / pixDist

public:
	Edge();								// 用于占位的空对象构造函数
	Edge(Landmark LM1, Landmark LM2, int existFlag);	// 通过首位结点构造对象
	double getPD();			// 返回像素距离
	double getRD();			// 返回真实距离
};


