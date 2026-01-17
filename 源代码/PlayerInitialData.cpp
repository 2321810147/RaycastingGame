#include<iostream>
#include<Windows.h>
#include"PlayerInitialData.h"
using namespace std;

PlayerInitialData::PlayerInitialData(float x,float y)
{
	this->PlayerX = x;
	this->PlayerY = y;

}
void PlayerInitialData::ChangeXY(float a, float b)
{
	this->PlayerX = a;
	this->PlayerY = b;
}
void PlayerInitialData::ChangeA(float A)
{
	this->PlayerA = A;
}
void PlayerInitialData::ChangeFOV(float fov)
{
	this->FOV = 3.14159 / fov;

}
void PlayerInitialData::CheckA()
{
	if (this->PlayerA > 6.28318)
		this->PlayerA -= 6.28318;
	if (this->PlayerA < -6.28318)
		this->PlayerA += 6.28318;
}
void PlayerInitialData::CheckHP(int MapWidth, wstring map)
{
	int a = (int)PlayerY * MapWidth + (int)PlayerX;
	if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
	{
		this->HP -= 10;
	}
}
