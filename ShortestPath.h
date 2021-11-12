#pragma once
#include "Landmark.h"
#include "Edge.h"


// 两结点间最短路径对象
// 程序启动时将使用 Floyd最短路径算法 创建对象二维数组 ShortestPath web[256][256]
// 每个对象包含自起点至终点经过的结点 index 
class ShortestPath
{
public:
	int LMonPath[128] = {-1};	// 路径经过结点index列表
	double pathLen;				// 路径总长度
	ShortestPath();				// 用于占位的空对象构造函数
	static void Floyd(Landmark* landmarks, Edge edges[256][256], ShortestPath web[256][256]);	// Floyd最短路径算法函数实现，仅在程序初始化时运行一次
																		// 参数：一维Landmark对象数组，二维Edge对象数组，二维ShortestPath对象数组
																		// 返回值：void
																		// 运行结果：为 web 中的每个ShortestPath对象元素赋值
	static void prn_pass(int i, int j);

};

