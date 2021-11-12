#pragma once
#include "Landmark.h"


// ��β�����ֱ�߾���
// ��������ʱ��������ά�������� Edge edges[256][256]
class Edge
{
	double pixDist;			// �˱���β�������ؾ��� ��λ��pixels
	double realDist;		// �˱���β������ʵ���� ��λ��m
	static double scale;	// ��ͼ������ scale = realDist / pixDist

public:
	Edge();								// ����ռλ�Ŀն����캯��
	Edge(Landmark LM1, Landmark LM2, int existFlag);	// ͨ����λ��㹹�����
	double getPD();			// �������ؾ���
	double getRD();			// ������ʵ����
};


