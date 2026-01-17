#pragma once
#include<iostream>
#include<windows.h>
#include <stdio.h>
#include<vector>
#include<cmath>
using namespace std;

//创建地图
class Map
{
public:
	//地图初始大小
	Map(int w, int h);

	int MapWidth;
	int MapHeight;

	//检查人的视野到墙的距离，地图最大为多少，就设置为根号2倍最大值
	//如果不是正方形地图就设置为地图对角线大小
	float MaxMapLine=16.0f;
	void ChangeMaxLine(int w,int h);

	wstring map;

};