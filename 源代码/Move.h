#pragma once
#include<iostream>
#include<Windows.h>
#include<thread>
using namespace std;

class Move
{
public:
	//每一帧的时间
	float ElapsedTime=0;

	void KeyQ(float& PlayerA);

	void KeyE(float& PlayerA);

	void KeyW(float PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void KeyS(float PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void KeyA(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void KeyD(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	COORD g_lastMousePos = { 0, 0 };
	int GetMouseHorizontalDirection();

	void MiceL(float& PlayerA);
	void MiceR(float& PlayerA);

	//突进技能
	void Skill(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth,int MapHeight,wstring map);
	//技能使用次数
	int NumOfSkill=0;
	//定时刷新技能
	void RefreshSkill();
	atomic<bool> runing = true;

	//射击,每次循环开始记得初始化为0
	bool fire=0;
	bool spacePressedLast = 0;
	void IsFire();

	//颠倒移动
	void RKeyQ(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void RKeyE(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void RKeyW(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void RKeyS(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map);

	void RKeyA(float& PlayerA);

	void RKeyD(float& PlayerA);

};