#pragma once
#include<iostream>
#include<windows.h>
#include <thread>
#include <chrono>
#include <random>
#include<string>
#include <atomic>
#include<cmath>
#include <mutex>
using namespace std;
extern std::mutex mapMutex;  // 只声明，不定义
class Enemy
{
public:
	Enemy(int a, int b);
	int x, y;
	void Changexy(int a, int b,int h);
	void DeleEnemy(float PlayerA,float PlayerX,float PlayerY,float MaxMapLine, wstring& Map, int MapWidth, int& NumOfEnemy);
	virtual void FillEnemy(wstring& Map,int MapWidth);

	int HP=4;

	//敌人随机移动
	void StartAutoMove(std::wstring& Map, int MapWidth);
	void StopAutoMove();
	virtual void AutoMove(std::wstring& Map, int MapWidth);
	thread autoMoveThread;
	atomic<bool> running{ false };
	atomic<bool> alive{ true };
};

//小兵，E
class Enemy1 : public Enemy {
public:
	Enemy1(int a, int b);
	void AutoMove(std::wstring& Map, int MapWidth) override;
	void FillEnemy(wstring& Map, int MapWidth);
};

//大兵，N
class Enemy2 : public Enemy {
public:
	Enemy2(int a, int b);
	void AutoMove(std::wstring& Map, int MapWidth) override;
	void FillEnemy(wstring& Map, int MapWidth);
};

//精锐,Y
class Enemy3 : public Enemy {
public:
	Enemy3(int a, int b);
	void AutoMove(std::wstring& Map, int MapWidth) override;
	void FillEnemy(wstring& Map, int MapWidth);
};

//Boss,B
class Enemy4 : public Enemy {
public:
	Enemy4(int a, int b);
	void AutoMove(std::wstring& Map, int MapWidth) override;
	void FillEnemy(wstring& Map, int MapWidth);
};