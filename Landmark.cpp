#include "pch.h"
#include "Landmark.h"


Landmark::Landmark()
{
	this->index = -1;
	this->x = -1;
	this->y = -1;
}


Landmark::Landmark(string name, int x, int y, int LM_index)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->index = LM_index;
}


Landmark::Landmark(int x, int y, int LM_index)
{
	this->name = "RoadPoint";	//��·�ؼ����ʹ����ͬ������
	this->x = x;
	this->y = y;
	this->index = LM_index;
}


int Landmark::X()
{
	return x;
}


int Landmark::Y()
{
	return y;
}


string Landmark::getName()
{
	return name;
}


int Landmark::getIndex()
{
	return index;
}


// ����ն�������
Landmark landmarks[256];

