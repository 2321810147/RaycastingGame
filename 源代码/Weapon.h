#pragma once
#include<iostream>
#include<windows.h>
using namespace std;

class Weapon
{
public:
	void hand(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer);

	void orb(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer);

	void Attachline(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer);

};