#include "pch.h"
#include "Edge.h"
#include <cmath>


Edge::Edge()
{
	// 无效对象标识
	this->pixDist = -1;
	this->realDist = -1;
}


// 使用以下方法计算得到的edges数据不正确
/*
Edge::Edge(Landmark LM1, Landmark LM2)
{
	int x1 = LM1.X();
	int y1 = LM1.Y();
	int x2 = LM2.X();
	int y2 = LM2.Y();
	// 结点间像素距离小于350时判定为有直接连通路径，否则两点间无直接连通路径
	double temp_pd = sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2);
	if (temp_pd < 250) {
		this->pixDist = temp_pd;
	}
	else {
		this->pixDist = 1000000;
	}
	this->realDist = this->pixDist * this->scale;
}
*/


Edge::Edge(Landmark LM1, Landmark LM2, int existFlag)
{
	int x1 = LM1.X();
	int y1 = LM1.Y();
	int x2 = LM2.X();
	int y2 = LM2.Y();
	if (x1 == x2 && y1 == y2) {
		this->pixDist = 0;
	}
	else {
		// 判定节点间的连接情况
		if (existFlag == 1) {
			using namespace std;
			double temp_pd = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
			this->pixDist = temp_pd;
		}
		else {
			this->pixDist = 1000000;
		}
		this->realDist = this->pixDist * this->scale;
	}
}


double Edge::getPD()
{
	return this->pixDist;
}


double Edge::getRD()
{
	return this->realDist;
}


// 全局初始化比例尺
double Edge::scale = 0.5;

// 创建二维对象数组
Edge edges[256][256];