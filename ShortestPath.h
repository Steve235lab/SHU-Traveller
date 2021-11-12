#pragma once
#include "Landmark.h"
#include "Edge.h"


// ���������·������
// ��������ʱ��ʹ�� Floyd���·���㷨 ���������ά���� ShortestPath web[256][256]
// ÿ�����������������յ㾭���Ľ�� index 
class ShortestPath
{
public:
	int LMonPath[128] = {-1};	// ·���������index�б�
	double pathLen;				// ·���ܳ���
	ShortestPath();				// ����ռλ�Ŀն����캯��
	static void Floyd(Landmark* landmarks, Edge edges[256][256], ShortestPath web[256][256]);	// Floyd���·���㷨����ʵ�֣����ڳ����ʼ��ʱ����һ��
																		// ������һάLandmark�������飬��άEdge�������飬��άShortestPath��������
																		// ����ֵ��void
																		// ���н����Ϊ web �е�ÿ��ShortestPath����Ԫ�ظ�ֵ
	static void prn_pass(int i, int j);

};

