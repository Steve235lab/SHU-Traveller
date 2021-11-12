#include "pch.h"
#include "ShortestPath.h"

extern int existFlag_ext[128][128];
int Path[128][128] = { -1 };
int A[128][128] = { 1000000 };
int ct = 1;

// ����ShortestPath�����ά����
ShortestPath web[256][256];


ShortestPath::ShortestPath()
{
	// ��Ч����ʶ
	this->pathLen = -1.0;
	int i;
	for (i = 0; i < 128; i++) {
		LMonPath[i] = -1;
	}
}


void ShortestPath::Floyd(Landmark* landmarks, Edge edges[256][256], ShortestPath web[256][256])
{
	int v;	// ��ʼ������
	int w;	// ��ĩ������
	int u;	// ;��������

	// ����landmarks����Ч���ĸ�����������landmarks����Ч����
	int l = 0;
	while (landmarks[l].getIndex() != -1) {
		l++;
	}


	// ���´����о�ʹ�����ؾ������
	// ����web����ʼ����
	// ���·������ pathLen = �������ֱ����ͨ·������ or �Թ̶�ֵ1000000��ʾ�Ĳ���ֱ�ӵ���
	// ;����� LMonPath Ϊ�����յ�
	// �Ը�����������ͨ������
	//double minLen;
	for (v = 0; v < l; ++v) {
		//minLen = 1000000;
		for (w = 0; w < l; ++w) {
			double t_len = edges[v][w].getPD();
			if (t_len < 1000000.0 && t_len >= 0) {
				web[v][w].pathLen = t_len;
			}
			else {
				web[v][w].pathLen = 1000000;
			}
			web[v][w].LMonPath[0] = v;
			web[v][w].LMonPath[1] = w;
			//if (web[v][w].pathLen !=0 && minLen > web[v][w].pathLen) {
			//	minLen = web[v][w].pathLen;
			//}
		}
		/*
		if (minLen == 1000000) {	// ��⵽�����㣬��Ϊ������Ѱ�Ҿ��������һ����ʵ����ͨ
			int x1 = landmarks[v].X();
			int y1 = landmarks[v].Y();
			int x2;
			int y2;
			double temp_pd;
			int temp_w;
			for (w = 0; w < l; ++w) {	// ���¼���ù����㵽��������ľ���
				x2 = landmarks[w].X();
				y2 = landmarks[w].Y();
				temp_pd = sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2);
				if (temp_pd != 0 && temp_pd < minLen) {		// �ҵ������һ��
					minLen = temp_pd;	// �������
					temp_w = w;			// ������������
				}
			}
			web[v][temp_w].pathLen = minLen;	// ʹ���µ������������ԭ����1000000
		}
		*/
	}
	for (u = 0; u < l; ++u) {
		for (v = 0; v < l; ++v) {
			for (w = 0; w < l; ++w) {
				if ((web[v][u].pathLen + web[u][w].pathLen) < web[v][w].pathLen) {	// ��v��u��w��һ��·������
					web[v][w].pathLen = web[v][u].pathLen + web[u][w].pathLen;		// �������·������
					// ����·����������
					int i;
					for (i = 0; i < 128; i++) {		// ����v - u�ζ����б�
						if (web[v][u].LMonPath[i] != -1) {
							web[v][w].LMonPath[i] = web[v][u].LMonPath[i];
						}
						else {
							break;
						}
					}
					int j, k = 0;
					for (j = i; j < 128; j++) {		// ����u - w�ζ����б� 
						if (web[u][w].LMonPath[k] != -1) {
							web[v][w].LMonPath[j] = web[u][w].LMonPath[k];
							k++;
						}
						else {
							break;
						}
					}
				}
			}
		}
	}
}




//void ShortestPath::prn_pass(int i, int j)
//{
//	if (Path[i][j] != -1) {
//		prn_pass(i, Path[i][j]);
//		web[i][j].LMonPath[ct] = Path[i][j];
//		ct++;
//		prn_pass(Path[i][j], j);
//	}
//}
//
//
//void ShortestPath::Floyd(Landmark* landmarks, Edge edges[256][256], ShortestPath web[256][256])
//{
//	
//	int i, j, k;
//	for (i = 0; i < 128; i++) {
//		for (j = 0; j < 128; j++) {
//			if (edges[i][j].getPD() < 1000000 && edges[i][j].getPD() > 0) {
//				A[i][j] = edges[i][j].getPD();
//			}
//		}
//	}
//
//	for (k = 0; k < 128; k++) {
//		for (i = 0; i < 128; i++) {
//			for (j = 0; j < 128; j++) {
//				if ((A[i][k] + A[k][j]) < A[i][j]) {
//					A[i][j] = A[i][k] + A[k][j];
//					Path[i][j] = j;
//				}
//			}
//		}
//	}
//
//	
//	for (i = 0; i < 128; i++) {
//		for (j = 0; j < 128; j++) {
//			if (i != j) {
//				ct = 1;
//				web[i][j].LMonPath[0] = i;
//				prn_pass(i, j);
//				web[i][j].LMonPath[ct] = j;
//			}
//			web[i][j].pathLen = A[i][j];
//		}
//	}
//	
//
//	/*
//	k = -1;	
//	for (i = 0; i < 128; i++) {
//		for (j = 0; j < 128; j++) {
//			ct = 1;
//			int i_t = i;
//			web[i][j].LMonPath[0] = i;
//			while (k != j) {
//				k = Path[i_t][j];
//				web[i][j].LMonPath[ct] = k;
//				i_t = k;
//				ct++;
//			}
//			web[i][j].LMonPath[ct] = j;
//		}
//	}
//	*/
//}



