#pragma once
#include<iostream>
#include"Windows.h"
using namespace std;

class PlayerInitialData
{
public:
	//玩家所站的xy轴位置
	float PlayerX;
	float PlayerY;
	int HP = 5;
	PlayerInitialData(float x, float y);
	void ChangeXY(float a, float b);
	//玩家视野的初始朝向角度，弧度制，通常0表示正右方，逆时针增加
	float PlayerA = 0.0f;
	void CheckA();
	void ChangeA(float A);
	//玩家视野的左右宽度
	float FOV = 3.14159 / 3.0;

	//修改视野宽度
	void ChangeFOV(float fov);

	void CheckHP(int MapWidth, wstring map);
};