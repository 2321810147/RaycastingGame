#pragma once
#include<iostream>
#include<Windows.h>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

class ScreenCanvas
{
public:
	ScreenCanvas(int ScreenWidth,int ScreenHeight);
	wchar_t* Canvas;

	//填充画布加载画面
	void CanvasFilling(wstring& map,int MapWidth,int MapHeight, float MaxMapLine,
	int ScreenWidth,int ScreenHeight,float PlayerX,float PlayerY,float PlayerA,float FOV);

	//加载小地图
	void MiniMap(wstring map, int MapWidth, int MapHeight, int ScreenWidth, int ScreenHeight, float PlayerX, float PlayerY);

	// 对应颜色缓冲区（Windows 控制台颜色值）
	WORD* ColorBuffer;
};