#include "pch.h"
#include "Edge.h"
#include <cmath>


Edge::Edge()
{
	// ��Ч�����ʶ
	this->pixDist = -1;
	this->realDist = -1;
}


// ʹ�����·�������õ���edges���ݲ���ȷ
/*
Edge::Edge(Landmark LM1, Landmark LM2)
{
	int x1 = LM1.X();
	int y1 = LM1.Y();
	int x2 = LM2.X();
	int y2 = LM2.Y();
	// �������ؾ���С��350ʱ�ж�Ϊ��ֱ����ͨ·���������������ֱ����ͨ·��
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
		// �ж��ڵ����������
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


// ȫ�ֳ�ʼ��������
double Edge::scale = 0.5;

// ������ά��������
Edge edges[256][256];