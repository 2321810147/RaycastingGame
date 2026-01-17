#pragma once
#include<iostream>
#include<windows.h>
using namespace std;


class ScreenInitial
{
public:
	ScreenInitial(int w,int h);

	//屏幕尺寸
	int ScreenWidth;
	int ScreenHeight;

	//创建一个屏幕缓冲区
	//创建一个新的控制台屏幕缓冲区
	HANDLE hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, //表示请求对缓冲区的读写权限
		FILE_SHARE_WRITE,             //共享模式, 0表示缓冲区不能被共享
		NULL,						  //安全属性, NULL表示使用默认安全描述符，且返回的句柄不能被继承
		CONSOLE_TEXTMODE_BUFFER,	  //创建标志,创建一个常规的文本模式缓冲区
		NULL						  //屏幕缓冲区数据,NULL表示不使用
	);
	void SetConsoleBufferSize(int cols, int lines);

	BOOL SetConsoleWindowSize(int width, int height);

	CONSOLE_FONT_INFOEX GetCurrentConsoleFont();

	BOOL SetConsoleFontSize(int width, int height, const wchar_t* fontName);


};
