#pragma once
#include <iostream>
#include <string>

using namespace std;


// ѧУ�ڵĵر��
// �������Ҫ�ص㡢·�ڡ���·ת�䴦
// ��������ʱ����ȡ�����ļ����������б� Landmark landmarks[256]
class Landmark {
public:
	Landmark(string name, int x, int y, int LM_index);		// �����Ƶĵر����� ���캯����ͨ����ȡ�ⲿ�����ļ���������������
	Landmark();			// �ն����캯�����ڴ��������б�ʱ����ռλ
	Landmark(int x, int y, int LM_index);		// ��·�㣨�����ƣ� ���캯��
	int X();		// ���ظõ�x����
	int Y();		// ���ظõ�y����
	int getIndex();	// ���ض������
	string getName();		// ���ض�������
	string name;	// �Ƕ����Ψһ��ʶ�������ظ�
	int x, y;		// �ص����꣬���ǵ�����ͼ���š����󣬲��ʺ�ֱ��ʹ�����ص����꣬��ʹ�����񽻵�����
	int index;		// �ýڵ��Ψһ��ʶ��Ӧ�������ͬ
};
