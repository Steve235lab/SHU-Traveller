#pragma once
#include <iostream>
#include <string>

using namespace std;


// 学校内的地标点
// 需包含重要地点、路口、道路转弯处
// 程序启动时将读取数据文件创建对象列表 Landmark landmarks[256]
class Landmark {
public:
	Landmark(string name, int x, int y, int LM_index);		// 有名称的地标点对象 构造函数，通过读取外部数据文件来批量创建对象
	Landmark();			// 空对象构造函数，在创建对象列表时用来占位
	Landmark(int x, int y, int LM_index);		// 道路点（无名称） 构造函数
	int X();		// 返回该点x坐标
	int Y();		// 返回该点y坐标
	int getIndex();	// 返回对象序号
	string getName();		// 返回对象名称
	string name;	// 非对象的唯一标识，允许重复
	int x, y;		// 地点坐标，考虑到“地图缩放”需求，不适合直接使用像素点坐标，拟使用网格交点坐标
	int index;		// 该节点的唯一标识，应与序号相同
};
